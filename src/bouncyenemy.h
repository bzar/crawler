#ifndef BOUNCYENEMY_HH
#define BOUNCYENEMY_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "ew/updatable.h"
#include "ew/collidable.h"
#include "ew/tilecollidable.h"

#include "util/vec2d.h"

class BouncyEnemy : public ew::Renderable, public ew::Updatable, public ew::Collidable, public ew::TileCollidable
{
public:
  static void init();
  static void term();

  BouncyEnemy(GameWorld* world, Vec2D const& position, Vec2D const& velocity);
  ~BouncyEnemy();

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void render(ew::RenderContext* context);
  void update(float const delta);
  void collide(ew::Collidable const* other);

  ew::TileCollidableWorld::TileCollideRect getTileCollideRect();
  void moveHorizontally(float const delta);
  void moveVertically(float const delta);
  void tileCollisionTop(float const y);
  void tileCollisionBottom(float const y);
  void tileCollisionLeft(float const x);
  void tileCollisionRight(float const x);

private:
  Vec2D position;
  Vec2D velocity;
};
#endif
