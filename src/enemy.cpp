#include "enemy.h"
#include "sword.h"
#include "player.h"

ew::UID const Enemy::ID = ew::getUID();

void Enemy::init()
{

}

void Enemy::term()
{

}

Enemy::Enemy(GameWorld* world, Vec2D const& position, Vec2D const& velocity, int const life) :
  Entity(world), Renderable(world), Updatable(world), Collidable(world), world(world),
  position(position), velocity(velocity), life(life), stunTimer(0), knockbackTimer(0)
{

}

Enemy::~Enemy()
{

}

void Enemy::update(float const delta)
{
  if(stunned())
  {
    stunTimer -= delta;
  }

  if(knockedBack())
  {
    knockbackTimer -= delta;
    if(!knockedBack())
    {
      velocity = {0, 0};
    }
  }

  if(!alive() && !stunned() && !knockedBack())
  {
    world->removeEntity(this);
  }

}

void Enemy::collide(ew::Collidable const* other)
{
  if(knockedBack() || !alive())
    return;

  if(other->getEntityId() == Sword::ID) {
    Sword const* sword = static_cast<Sword const*>(other);
    if(sword->slashing() && getShape()->collidesWith(sword->getShape()))
    {
      life -= 1;
      velocity = (position - sword->getPlayer()->getPosition()).uniti().scalei(200);
      stunTimer = 0.5;
      knockbackTimer = 0.2;
    }
    return;
  }
}

Vec2D Enemy::getPosition() const
{
  return position;
}

bool Enemy::stunned() const
{
  return stunTimer > 0;
}

bool Enemy::knockedBack() const
{
  return knockbackTimer > 0;
}

bool Enemy::alive() const
{
  return life > 0;
}
