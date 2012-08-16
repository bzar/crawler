#include "exploryenemy.h"
#include "ew/integration/sdlrendercontext.h"
#include "util/util.h"

void ExploryEnemy::init() {}
void ExploryEnemy::term() {}

ExploryEnemy::ExploryEnemy(GameWorld* world, Vec2D const& position) :
  Entity(world), Enemy(world, position, {0, 0}, 3), TileCollidable(world),
  shape(position, 16, 16)
{

}

ExploryEnemy::~ExploryEnemy()
{

}



void ExploryEnemy::render(ew::RenderContext* context)
{
  SDLRenderContext* ctx = static_cast<SDLRenderContext*>(context);
  Sint16 x = position.x - 8;
  Sint16 y = position.y - 8;
  SDL_Rect rect = {x, y, 16, 16};
  SDL_FillRect(ctx->getScreen(), &rect, SDL_MapRGB(ctx->getScreen()->format, 0xEF, 0x82, 0xCC ));
}

void ExploryEnemy::update(float const delta)
{
  shape.center = position;

  if(!stunned() && !knockedBack())
  {
    if(velocity.x == 0 && velocity.y == 0)
    {
      if(randInt(0, 200) == 0)
      {
        velocity = {randFloat(-50, 50), randFloat(-50, 50)};
      }
    }
    else if(randInt(0, 500) == 0)
    {
      velocity = {0, 0};
    }
  }

  Enemy::update(delta);
}

ew::TileCollidableWorld::TileCollideRect ExploryEnemy::getTileCollideRect()
{
  return {position.x - 8, position.y - 8, 16, 16};
}

void ExploryEnemy::moveHorizontally(float const delta)
{
  position.x += velocity.x * delta;
}

void ExploryEnemy::moveVertically(float const delta)
{
  position.y += velocity.y * delta;
}

void ExploryEnemy::tileCollisionTop(float const y)
{
  if(randInt(1, 4))
  {
    velocity.y *= randFloat(-0.5, 0);
    position.y = y + 8;
  }
  else
  {
    velocity = {0, 0};
  }
}

void ExploryEnemy::tileCollisionBottom(float const y)
{
  if(randInt(1, 4))
  {
    velocity.y *= randFloat(-0.5, 0);
    position.y = y - 8;
  }
  else
  {
    velocity = {0, 0};
  }
}

void ExploryEnemy::tileCollisionLeft(float const x)
{
  if(randInt(1, 4))
  {
    velocity.x *= randFloat(-0.5, 0);
    position.x = x + 8;
  }
  else
  {
    velocity = {0, 0};
  }
}

void ExploryEnemy::tileCollisionRight(float const x)
{
  if(randInt(1, 4))
  {
    velocity.x *= randFloat(-0.5, 0);
    position.x = x - 8;
  }
  else
  {
    velocity = {0, 0};
  }
}

RectShape const* ExploryEnemy::getShape() const
{
  return &shape;
}
