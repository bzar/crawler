#include "player.h"
#include "enemy.h"

#include "SDL/SDL_image.h"
#include <fstream>

ew::UID const Player::ID = ew::getUID();
Sprite Player::sprite = Sprite();
int Player::animationIds[NUM_ANIMATION_TYPES][NUM_ANIMATION_DIRECTIONS] = { {-1} };
SDL_Surface* Player::image = nullptr;

void Player::init()
{
  std::ifstream f("sprite/player.qmlon");
  auto spriteDoc = qmlon::readValue(f);
  SpriteSheet sheet = SpriteSheet::create(spriteDoc);
  sprite = sheet.getSprite("player");

  animationIds[STAND][UP] = sprite.getAnimationId("stand-up");
  animationIds[STAND][DOWN] = sprite.getAnimationId("stand-down");
  animationIds[STAND][LEFT] = sprite.getAnimationId("stand-left");
  animationIds[STAND][RIGHT] = sprite.getAnimationId("stand-right");

  animationIds[WALK][UP] = sprite.getAnimationId("walk-up");
  animationIds[WALK][DOWN] = sprite.getAnimationId("walk-down");
  animationIds[WALK][LEFT] = sprite.getAnimationId("walk-left");
  animationIds[WALK][RIGHT] = sprite.getAnimationId("walk-right");

  animationIds[SLASH][UP] = sprite.getAnimationId("slash-up");
  animationIds[SLASH][DOWN] = sprite.getAnimationId("slash-down");
  animationIds[SLASH][LEFT] = sprite.getAnimationId("slash-left");
  animationIds[SLASH][RIGHT] = sprite.getAnimationId("slash-right");

  SDL_Surface* loadedImage = IMG_Load(sheet.getImage().data());

  if(loadedImage)
  {
    image = SDL_DisplayFormat(loadedImage);
    SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(image->format, 0xFF, 0x00, 0xFF));
  }
  SDL_FreeSurface(loadedImage);

}

void Player::term()
{
  SDL_FreeSurface(image);
}

Player::Player(GameWorld* world, Vec2D const& position) :
  Entity(world), Renderable(world), Updatable(world), Collidable(world),
  Controllable(world), TileCollidable(world),
  position(position), velocity(), facing(0, 1), shape(position, 10, 6),
  sword(new Sword(world, this)), knockbackTimer(0), frameTimer(0)
{
}

Player::~Player()
{

}



void Player::render(ew::RenderContext* context)
{
  SDLRenderContext* ctx = static_cast<SDLRenderContext*>(context);

  AnimationDirection d = UP;

  if(facing.y == 1)
  {
    d = DOWN;
  }
  else if(facing.y == -1)
  {
    d = UP;
  }
  else if(facing.x == 1)
  {
    d = RIGHT;
  }
  else if(facing.x == -1)
  {
    d = LEFT;
  }

  AnimationType t = STAND;

  if(sword->slashing())
  {
    t = SLASH;
  }
  else if(velocity != Vec2D(0, 0))
  {
    t = WALK;
  }
  else
  {
    t = STAND;
  }

  Frame const& f = sprite.getAnimation(animationIds[t][d]).getFrame(frameTimer);

  Sint16 x = f.getPosition().x;
  Sint16 y = f.getPosition().y;
  Uint16 w = f.getSize().width;
  Uint16 h = f.getSize().height;

  SDL_Rect rect = {x, y, w, h};

  Sint16 dx = position.x - f.getHotspot().x;
  Sint16 dy = position.y - f.getHotspot().y;
  SDL_Rect offset = {dx, dy, 0, 0};

  SDL_BlitSurface(image, &rect, ctx->getScreen(), &offset );
}

void Player::update(float const delta)
{
  shape.center = position;
  if(knockedBack())
  {
    knockbackTimer -= delta;
  }
  frameTimer += delta;
}

void Player::collide(ew::Collidable const* other)
{
  if(other->getEntityId() == Enemy::ID) {
    Enemy const* enemy = static_cast<Enemy const*>(other);
    if(enemy->getShape()->collidesWith(&shape))
    {
      velocity = (position - enemy->getPosition()).uniti().scalei(200);
      knockbackTimer = 0.2;
    }
    return;
  }

}

void Player::control(ew::ControlContext* context)
{
  if(!knockedBack())
  {
    velocity = {0, 0};

    if(!sword->slashing())
    {
      if(context->keyDown(SDLK_UP))
      {
        velocity.y -= 100;
      }
      if(context->keyDown(SDLK_DOWN))
      {
        velocity.y += 100;
      }
      if(context->keyDown(SDLK_LEFT))
      {
        velocity.x -= 100;
      }
      if(context->keyDown(SDLK_RIGHT))
      {
        velocity.x += 100;
      }

      if(facing.x * velocity.x <= 0 && facing.y * velocity.y <= 0 && velocity != Vec2D(0, 0))
      {
        facing = velocity.x != 0 ? Vec2D(velocity.x/100, 0) : Vec2D(0, velocity.y/100);
      }
    }
  }

  if(context->keyPush(SDLK_SPACE))
  {
    sword->slash();
    frameTimer = 0;
  }
}

ew::TileCollidableWorld::TileCollideRect Player::getTileCollideRect()
{
  return {position.x - 8, position.y - 8, 16, 16};
}

void Player::moveHorizontally(float const delta)
{
  position.x += velocity.x * delta;
}

void Player::moveVertically(float const delta)
{
  position.y += velocity.y * delta;
}

void Player::tileCollisionTop(float const y)
{
  position.y = y + 8;
}

void Player::tileCollisionBottom(float const y)
{
  position.y = y - 8;
}

void Player::tileCollisionLeft(float const x)
{
  position.x = x + 8;
}

void Player::tileCollisionRight(float const x)
{
  position.x = x - 8;
}


Vec2D Player::getPosition() const
{
  return position;
}

Vec2D Player::getFacing() const
{
  return facing;
}

RectShape const* Player::getShape() const
{
  return &shape;
}

bool Player::knockedBack() const
{
  return knockbackTimer > 0;
}
