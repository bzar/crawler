#include "ew/integration/sdlrendercontext.h"
#include "gameworld.h"
#include "level.h"

void Level::init()
{

}

void Level::term()
{

}

ew::UID const Level::ID = ew::getUID();

Level::Level(GameWorld* world) :
  ew::Entity(world), ew::Renderable(world, 0, -1), tiles()
{
  char TEST_LEVEL[15][26] = {
    "#########################",
    "#....#..................#",
    "#....#.........########.#",
    "#....#................#.#",
    "##.###.####....#......#.#",
    "#......#..#....#......#.#",
    "#...####..#....##.#####.#",
    "#...#.....#.............#",
    "#.###...................#",
    "#.#.#..........##.#####.#",
    "#.........#....#......#.#",
    "#.#.#.....#....#......#.#",
    "#.#########....####.###.#",
    "#.......................#",
    "#########################"
  };

  for(int y = 0; y < 15; ++y)
  {
    for(int x = 0; x < 25; ++x)
    {
      tiles.push_back({x * TILE_SIZE, y * TILE_SIZE, TEST_LEVEL[y][x] == '#' ? true : false});
    }
  }
}

Level::~Level()
{

}

void Level::render(ew::RenderContext* context)
{
  for(Tile& tile : tiles)
  {
    SDLRenderContext* ctx = static_cast<SDLRenderContext*>(context);
    Sint16 x = tile.x;
    Sint16 y = tile.y;
    SDL_Rect rect = {x, y, TILE_SIZE, TILE_SIZE};
    Uint32 color = SDL_MapRGB(ctx->getScreen()->format, tile.blocking ? 0x0F : 0xEE, tile.blocking ? 0x0F : 0xEE, tile.blocking ? 0x0F : 0xEE);
    SDL_FillRect(ctx->getScreen(), &rect, color);
  }
}

std::vector<Level::Tile> Level::getIntersectingTiles(int x, int y, int w, int h)
{
  std::vector<Tile> result;

  for(Tile& tile : tiles)
  {
    if(!tile.blocking)
      continue;
    if(x >= tile.x + TILE_SIZE)
      continue;
    if(tile.x >= x + w )
      continue;
    if(y >= tile.y + TILE_SIZE)
      continue;
    if(tile.y >= y + h )
      continue;
    result.push_back(tile);
  }

  return result;
}