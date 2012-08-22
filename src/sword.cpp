#include "sword.h"
#include "player.h"
#include "ew/integration/sdlrendercontext.h"
#include "SDL/SDL_image.h"
#include <fstream>

ew::UID const Sword::ID = ew::getUID();
float const Sword::SLASH_DURATION = 0.15;
Sprite Sword::sprite = Sprite();
int Sword::animationIds[NUM_ANIMATION_DIRECTIONS] = {-1};
SDL_Surface* Sword::image = nullptr;

void Sword::init()
{
  std::ifstream f("sprite/sword.qmlon");
  auto spriteDoc = qmlon::readValue(f);
  SpriteSheet sheet = SpriteSheet::create(spriteDoc);
  sprite = sheet.getSprite("sword");

  animationIds[UP] = sprite.getAnimationId("slash-up");
  animationIds[DOWN] = sprite.getAnimationId("slash-down");
  animationIds[LEFT] = sprite.getAnimationId("slash-left");
  animationIds[RIGHT] = sprite.getAnimationId("slash-right");

  SDL_Surface* loadedImage = IMG_Load(sheet.getImage().data());

  if(loadedImage)
  {
    image = SDL_DisplayFormat(loadedImage);
    SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(image->format, 0xFF, 0x00, 0xFF));
  }
  SDL_FreeSurface(loadedImage);
}

void Sword::term()
{
  SDL_FreeSurface(image);
}


Sword::Sword(GameWorld* world, Player* player) :
  Entity(world), Renderable(world, 1), Updatable(world), Collidable(world),
  world(world), player(player), slashTime(0), shape(getPosition(), 0, 0),
  frameTimer(0)
{

}

Sword::~Sword()
{

}



void Sword::render(ew::RenderContext* context)
{
  if(slashing())
  {
    SDLRenderContext* ctx = static_cast<SDLRenderContext*>(context);

    AnimationDirection d = UP;

    if(player->getFacing().y == 1)
    {
      d = DOWN;
    }
    else if(player->getFacing().y == -1)
    {
      d = UP;
    }
    else if(player->getFacing().x == 1)
    {
      d = RIGHT;
    }
    else if(player->getFacing().x == -1)
    {
      d = LEFT;
    }


    Frame const& f = sprite.getAnimation(animationIds[d]).getFrame(frameTimer);

    Sint16 x = f.getPosition().x;
    Sint16 y = f.getPosition().y;
    Uint16 w = f.getSize().width;
    Uint16 h = f.getSize().height;

    SDL_Rect rect = {x, y, w, h};

    Sint16 dx = player->getPosition().x - f.getHotspot().x;
    Sint16 dy = player->getPosition().y - f.getHotspot().y;
    SDL_Rect offset = {dx, dy, 0, 0};

    SDL_BlitSurface(image, &rect, ctx->getScreen(), &offset );
  }
}

void Sword::update(float const delta)
{
  if(slashing())
  {
    frameTimer += delta;
    slashTime -= delta;
    shape.center = player->getPosition() + player->getFacing().scale(8);
    if(player->getFacing().x != 0)
    {
      shape.width = 16;
      shape.height = 24;
    }
    else
    {
      shape.width = 24;
      shape.height = 16;
    }
  }
}

void Sword::collide(ew::Collidable const* other)
{

}


void Sword::slash()
{
  frameTimer = 0;
  slashTime = SLASH_DURATION;
}

bool Sword::slashing() const
{
  return slashTime > 0;
}

Vec2D Sword::getPosition() const
{
  return shape.center;
}

RectShape const* Sword::getShape() const
{
  return &shape;
}

Player* Sword::getPlayer() const
{
  return player;
}