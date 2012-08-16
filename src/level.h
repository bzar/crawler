#ifndef PROP_HH
#define PROP_HH

#include "ew/renderable.h"
#include "ew/integration/sdlrendercontext.h"

#include <vector>
#include <string>

class GameWorld;

class Level
{
public:
  struct Tile
  {
    int x;
    int y;
    bool blocking;
  };

  static int const TILE_SIZE = 16;

  static void init();
  static void term();

  Level(GameWorld* world);
  ~Level();

  std::vector<Tile> getIntersectingTiles(int x, int y, int w, int h);

private:
  static SDL_Surface* image;

  class FrontLayer : public ew::Renderable
  {
  public:
    FrontLayer(Level* level);
    static ew::UID const ID;
    ew::UID getEntityId() const { return ID; }
    void render(ew::RenderContext* context);
  private:
    Level* level;
  };

  class BackLayer : public ew::Renderable
  {
  public:
    BackLayer(Level* level);
    static ew::UID const ID;
    ew::UID getEntityId() const { return ID; }
    void render(ew::RenderContext* context);
  private:
    Level* level;
  };

  friend class FrontLayer;
  friend class BackLayer;

  void renderTile(SDL_Surface* screen, int tx, int ty, int nx, int ny, int x, int y);

  GameWorld* world;
  std::vector<std::string> map;
  std::vector<Tile> tiles;
  FrontLayer* frontLayer;
  BackLayer* backLayer;
};

#endif
