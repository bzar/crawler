#ifndef PROP_HH
#define PROP_HH

#include "ew/renderable.h"

#include <vector>

class GameWorld;

class Level : public ew::Renderable
{
public:
  struct Tile
  {
    int x;
    int y;
    bool blocking;
  };

  static int const TILE_SIZE = 32;

  static void init();
  static void term();

  Level(GameWorld* world);
  ~Level();

  static ew::UID const ID;
  ew::UID getEntityId() const { return ID; }

  void render(ew::RenderContext* context);

  std::vector<Tile> getIntersectingTiles(int x, int y, int w, int h);

private:
  std::vector<Tile> tiles;
};

#endif
