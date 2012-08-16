#ifndef SWORD_HH
#define SWORD_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "ew/updatable.h"
#include "ew/collidable.h"

#include "util/vec2d.h"
#include "util/rectshape.h"

class Player;

class Sword : public ew::Renderable, public ew::Updatable, public ew::Collidable
{
public:
  static void init();
  static void term();

  Sword(GameWorld* world, Player* player);
  ~Sword();

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void render(ew::RenderContext* context);
  void update(float const delta);
  void collide(ew::Collidable const* other);

  void slash();
  bool slashing() const;

  Vec2D getPosition() const;
  RectShape const* getShape() const;
  Player* getPlayer() const;

private:
  static float const SLASH_DURATION;
  GameWorld* world;
  Player* player;
  float slashTime;
  RectShape shape;
};
#endif
