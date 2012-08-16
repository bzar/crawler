#ifndef PLAYER_HH
#define PLAYER_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "ew/updatable.h"
#include "ew/collidable.h"
#include "ew/controllable.h"
#include "ew/tilecollidable.h"

#include "util/vec2d.h"
#include "sword.h"

#include "util/rectshape.h"

class Player : public ew::Renderable, public ew::Updatable, public ew::Collidable, public ew::Controllable, public ew::TileCollidable
{
public:
  static void init();
  static void term();

  Player(GameWorld* world, Vec2D const& position);
  ~Player();

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void render(ew::RenderContext* context);
  void update(float const delta);
  void collide(ew::Collidable const* other);
  void control(ew::ControlContext* context);

  ew::TileCollidableWorld::TileCollideRect getTileCollideRect();
  void moveHorizontally(float const delta);
  void moveVertically(float const delta);
  void tileCollisionTop(float const y);
  void tileCollisionBottom(float const y);
  void tileCollisionLeft(float const x);
  void tileCollisionRight(float const x);

  Vec2D getPosition() const;
  Vec2D getFacing() const;
  RectShape const* getShape() const;

  bool knockedBack() const;

private:
  Vec2D position;
  Vec2D velocity;
  Vec2D facing;
  RectShape shape;

  Sword* sword;

  float knockbackTimer;
};
#endif
