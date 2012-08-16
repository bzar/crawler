#include "bouncyenemy.h"
#include "ew/integration/sdlrendercontext.h"
#include "util/util.h"

void BouncyEnemy::init() {}
void BouncyEnemy::term() {}

BouncyEnemy::BouncyEnemy(GameWorld* world, Vec2D const& position, Vec2D const& velocity) :
  Entity(world), Enemy(world, position, velocity, 2), TileCollidable(world),
  shape(position, 16, 16)
{

}

BouncyEnemy::~BouncyEnemy()
{

}



void BouncyEnemy::render(ew::RenderContext* context)
{
  SDLRenderContext* ctx = static_cast<SDLRenderContext*>(context);
  Sint16 x = position.x - 8;
  Sint16 y = position.y - 8;
  SDL_Rect rect = {x, y, 16, 16};
  SDL_FillRect(ctx->getScreen(), &rect, SDL_MapRGB(ctx->getScreen()->format, 0xEF, 0x00, 0xEF ));
}

void BouncyEnemy::update(float const delta)
{
  if(velocity == Vec2D(0, 0) && !stunned())
  {
    velocity = {0, 150};
    velocity.rotatei(randFloat(0, 1));
  }
  shape.center = position;
  Enemy::update(delta);
}

ew::TileCollidableWorld::TileCollideRect BouncyEnemy::getTileCollideRect()
{
  return {position.x - 8, position.y - 8, 16, 16};
}

void BouncyEnemy::moveHorizontally(float const delta)
{
  position.x += velocity.x * delta;
}

void BouncyEnemy::moveVertically(float const delta)
{
  position.y += velocity.y * delta;
}

void BouncyEnemy::tileCollisionTop(float const y)
{
  velocity.y = -velocity.y;
  position.y = y + 8;
}

void BouncyEnemy::tileCollisionBottom(float const y)
{
  velocity.y = -velocity.y;
  position.y = y - 8;
}

void BouncyEnemy::tileCollisionLeft(float const x)
{
  velocity.x = -velocity.x;
  position.x = x + 8;
}

void BouncyEnemy::tileCollisionRight(float const x)
{
  velocity.x = -velocity.x;
  position.x = x - 8;
}

RectShape const* BouncyEnemy::getShape() const
{
  return &shape;
}
