#ifndef BOUNCYENEMY_HH
#define BOUNCYENEMY_HH

#include "gameworld.h"
#include "enemy.h"
#include "ew/tilecollidable.h"

#include "util/vec2d.h"
#include "util/rectshape.h"

class BouncyEnemy : public Enemy, public ew::TileCollidable
{
public:
  static void init();
  static void term();

  BouncyEnemy(GameWorld* world, Vec2D const& position, Vec2D const& velocity = Vec2D(0, 0));
  ~BouncyEnemy();

  void render(ew::RenderContext* context);
  void update(float const delta);

  ew::TileCollidableWorld::TileCollideRect getTileCollideRect();
  void moveHorizontally(float const delta);
  void moveVertically(float const delta);
  void tileCollisionTop(float const y);
  void tileCollisionBottom(float const y);
  void tileCollisionLeft(float const x);
  void tileCollisionRight(float const x);

  virtual RectShape const* getShape() const;

private:
  RectShape shape;
};
#endif
