#ifndef PLAYER_HH
#define PLAYER_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "ew/updatable.h"
#include "ew/collidable.h"
#include "ew/controllable.h"
#include "ew/tilecollidable.h"

#include "util/vec2d.h"

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
  void setTileX(float const x);
  void setTileY(float const y);

private:
  Vec2D position;
  Vec2D velocity;
};
#endif
