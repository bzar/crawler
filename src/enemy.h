#ifndef ENEMY_HH
#define ENEMY_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "ew/updatable.h"
#include "ew/collidable.h"

#include "util/vec2d.h"
#include "util/shape.h"

class Enemy : public ew::Renderable, public ew::Updatable, public ew::Collidable
{
public:
  static void init();
  static void term();

  Enemy(GameWorld* world, Vec2D const& position, Vec2D const& velocity, int const life);
  ~Enemy();

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void update(float const delta);
  void collide(ew::Collidable const* other);

  Vec2D getPosition() const;
  virtual Shape const* getShape() const = 0;
  bool stunned() const;
  bool knockedBack() const;
  bool alive() const;

protected:
  GameWorld* world;
  Vec2D position;
  Vec2D velocity;
  int life;
  float stunTimer;
  float knockbackTimer;
};
#endif
