#include "sword.h"
#include "player.h"
#include "ew/integration/sdlrendercontext.h"

ew::UID const Sword::ID = ew::getUID();
float const Sword::SLASH_DURATION = 0.15;

void Sword::init()
{

}

void Sword::term()
{

}


Sword::Sword(GameWorld* world, Player* player) :
  Entity(world), Renderable(world), Updatable(world), Collidable(world),
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

    Sint16 x = shape.center.x - shape.width/2;
    Sint16 y = shape.center.y - shape.height/2;
    Uint16 w = shape.width;
    Uint16 h = shape.height;
    SDL_Rect rect = {x, y, w, h};
    SDL_FillRect(ctx->getScreen(), &rect, SDL_MapRGB(ctx->getScreen()->format, 0x80, 0x00, 0x00));
  }
}

void Sword::update(float const delta)
{
  if(slashing())
  {
    slashTime -= delta;
    shape.center = player->getPosition() + player->getFacing().scale(16);
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