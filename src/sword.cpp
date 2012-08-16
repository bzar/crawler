#include "sword.h"
#include "player.h"
#include "ew/integration/sdlrendercontext.h"
#include "SDL/SDL_image.h"

ew::UID const Sword::ID = ew::getUID();
float const Sword::SLASH_DURATION = 0.15;
SDL_Surface* Sword::image = nullptr;

void Sword::init()
{
  SDL_Surface* loadedImage = IMG_Load("img/sword.png");

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
  world(world), player(player), slashTime(0), shape(getPosition(), 0, 0)
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

    /*Sint16 x = shape.center.x - shape.width/2;
    Sint16 y = shape.center.y - shape.height/2;
    Uint16 w = shape.width;
    Uint16 h = shape.height;
    SDL_Rect rect = {x, y, w, h};*/
    //SDL_FillRect(ctx->getScreen(), &rect, SDL_MapRGB(ctx->getScreen()->format, 0x80, 0x00, 0x00));

    SDL_Rect rect = {32, 32, 32, 32};

    Vec2D facing = player->getFacing();

    Vec2D position = player->getPosition();
    Sint16 dx = position.x;
    Sint16 dy = position.y;

    if(facing.y == 1)
    {
      dx -= 16;
      dy -= 16;
      rect.y *= 0;
    }
    else if(facing.y == -1)
    {
      dx -= 16;
      dy -= 24;
      rect.y *= 1;
    }
    else if(facing.x == 1)
    {
      dx -= 10;
      dy -= 20;
      rect.y *= 2;
    }
    else if(facing.x == -1)
    {
      dx -= 20;
      dy -= 20;
      rect.y *= 3;
    }

    rect.x *= static_cast<int>(3 * (1 - slashTime / SLASH_DURATION));

    SDL_Rect offset = {dx, dy, 32, 32};

    SDL_BlitSurface(image, &rect, ctx->getScreen(), &offset );
 }
}

void Sword::update(float const delta)
{
  if(slashing())
  {
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