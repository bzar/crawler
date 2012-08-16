#include "player.h"
#include "ew/integration/sdlrendercontext.h"
#include "enemy.h"

ew::UID const Player::ID = ew::getUID();

void Player::init() {}
void Player::term() {}

Player::Player(GameWorld* world, Vec2D const& position) :
  Entity(world), Renderable(world), Updatable(world), Collidable(world),
  Controllable(world), TileCollidable(world),
  position(position), velocity(), facing(0, 1), shape(position, 16, 16),
  sword(new Sword(world, this)), knockbackTimer(0)
{

}

Player::~Player()
{

}



void Player::render(ew::RenderContext* context)
{
  SDLRenderContext* ctx = static_cast<SDLRenderContext*>(context);
  Sint16 x = position.x - 8;
  Sint16 y = position.y - 8;
  SDL_Rect rect = {x, y, 16, 16};
  SDL_FillRect(ctx->getScreen(), &rect, SDL_MapRGB(ctx->getScreen()->format, 0xEF, 0x00, 0x00));

  Vec2D facingPos = position + facing.scale(8);
  Sint16 fx = facingPos.x - 2;
  Sint16 fy = facingPos.y - 2;
  SDL_Rect frect = {fx, fy, 4, 4};
  SDL_FillRect(ctx->getScreen(), &frect, SDL_MapRGB(ctx->getScreen()->format, 0x00, 0x00, 0xEF));
}

void Player::update(float const delta)
{
  shape.center = position;
  if(knockedBack())
  {
    knockbackTimer -= delta;
  }
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
