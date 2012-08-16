#ifndef EXPLORYENEMY_HH
#define EXPLORYENEMY_HH

#include "gameworld.h"
#include "enemy.h"
#include "ew/tilecollidable.h"

#include "util/vec2d.h"
#include "util/rectshape.h"

class ExploryEnemy : public Enemy, public ew::TileCollidable
{
public:
  static void init();
  static void term();

  ExploryEnemy(GameWorld* world, Vec2D const& position);
  ~ExploryEnemy();

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
