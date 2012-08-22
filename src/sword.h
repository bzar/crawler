#ifndef SWORD_HH
#define SWORD_HH

#include "gameworld.h"
#include "ew/renderable.h"
#include "ew/updatable.h"
#include "ew/collidable.h"
#include "ew/integration/sdlrendercontext.h"

#include "util/vec2d.h"
#include "util/rectshape.h"
#include "spritesheet.h"

class Player;

class Sword : public ew::Renderable, public ew::Updatable, public ew::Collidable
{
public:
  static float const SLASH_DURATION;

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
  enum AnimationDirection { UP, DOWN, LEFT, RIGHT, NUM_ANIMATION_DIRECTIONS };
  static int animationIds[NUM_ANIMATION_DIRECTIONS];
  static Sprite sprite;

  static SDL_Surface* image;

  GameWorld* world;
  Player* player;
  float slashTime;
  RectShape shape;

  float frameTimer;
};
#endif
