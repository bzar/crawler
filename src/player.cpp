#include "player.h"
#include "ew/integration/sdlrendercontext.h"

ew::UID const Player::ID = ew::getUID();

void Player::init() {}
void Player::term() {}

Player::Player(GameWorld* world, Vec2D const& position) :
  Entity(world), Renderable(world), Updatable(world), Collidable(world),
  Controllable(world), TileCollidable(world),
  position(position), velocity()
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
  SDL_FillRect(ctx->getScreen(), &rect, SDL_MapRGB(ctx->getScreen()->format, 0xEF, 0x00, 0x00 ));
}

void Player::update(float const delta)
{
}

void Player::collide(ew::Collidable const* other)
{

}

void Player::control(ew::ControlContext* context)
{
  velocity = {0, 0};
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
