#include "level.h"
#include "gameworld.h"
#include "bouncyenemy.h"
#include "exploryenemy.h"

#include "SDL/SDL_image.h"

SDL_Surface* Level::image = nullptr;

void Level::init()
{
  SDL_Surface* loadedImage = IMG_Load("img/walls.png");

  if(loadedImage)
  {
    image = SDL_DisplayFormat(loadedImage);
    SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(image->format, 0xFF, 0x00, 0xFF));
  }
  SDL_FreeSurface(loadedImage);
}

void Level::term()
{
  SDL_FreeSurface(image);
}

ew::UID const Level::FrontLayer::ID = ew::getUID();
ew::UID const Level::BackLayer::ID = ew::getUID();

Level::Level(GameWorld* world) :
  world(world), map(), tiles(),
  frontLayer(new FrontLayer(this)), backLayer(new BackLayer(this))
{
  map = {
    "################################################",
    "#.....................................#........#",
    "#.....................................#........#",
    "#..#######################................b....#",
    "#..#.....................#.....................#",
    "#..#..................................#........#",
    "#..#.........e........................##########",
    "#..#.....................#.....................#",
    "#..#.....................#.....................#",
    "#..#######..##############.......#.........#...#",
    "#..............................................#",
    "#.....................................e........#",
    "#..............................................#",
    "#..################..####......................#",
    "#..#....................#........#.........#...#",
    "#..#....................#......................#",
    "#..#........b...........#......................#",
    "#..#....................#......................#",
    "#..##..##################............###...##..#",
    "#....................................#......#..#",
    "#............e.......................#......#..#",
    "#...##################################......#..#",
    "#...#.......................................#..#",
    "#...#........b..............................#..#",
    "#...################....#####################..#",
    "#..............................................#",
    "#....................................e.........#",
    "################################################"
  };

  for(int y = map.size() - 1; y >= 0; --y)
  {
    for(int x = 0; x < map.at(y).length(); ++x)
    {
      tiles.push_back({x, y, map[y][x] == '#' ? true : false});

      if(map[y][x] == 'b')
      {
        new BouncyEnemy(world, {((x+1) + 0.5f) * TILE_SIZE, ((y+1) + 0.5f) * TILE_SIZE});
      }
      else if(map[y][x] == 'e')
      {
        new ExploryEnemy(world, {((x+1) + 0.5f) * TILE_SIZE, ((y+1) + 0.5f) * TILE_SIZE});
      }
    }
  }

}

Level::~Level()
{

}

std::vector<Level::Tile> Level::getIntersectingTiles(int x, int y, int w, int h)
{
  std::vector<Tile> result;

  for(Tile& tile : tiles)
  {
    if(!tile.blocking)
      continue;
    if(x >= (tile.x + 1) * TILE_SIZE + TILE_SIZE)
      continue;
    if((tile.x + 1) * TILE_SIZE >= x + w )
      continue;
    if(y >= (tile.y + 1) * TILE_SIZE + TILE_SIZE)
      continue;
    if((tile.y + 1) * TILE_SIZE >= y + h )
      continue;
    result.push_back({(tile.x + 1) * TILE_SIZE, (tile.y + 1) * TILE_SIZE, tile.blocking});
  }

  return result;
}

void Level::renderTile(SDL_Surface* screen, int tx, int ty, int nx, int ny, int x, int y)
{
  Sint16 rx = tx * TILE_SIZE;
  Sint16 ry = ty * TILE_SIZE;
  Sint16 rw = nx * TILE_SIZE;
  Sint16 rh = ny * TILE_SIZE;
  SDL_Rect tile = {rx, ry, rw, rh};

  Sint16 dx = x * TILE_SIZE;
  Sint16 dy = y * TILE_SIZE;
  SDL_Rect offset = {dx, dy, TILE_SIZE, TILE_SIZE};

  SDL_BlitSurface(image, &tile, screen, &offset );
}

Level::FrontLayer::FrontLayer(Level* level) :
  Entity(level->world), Renderable(level->world, 0, 1), level(level)
{
}

Level::BackLayer::BackLayer(Level* level) :
  Entity(level->world), Renderable(level->world, 0, -1), level(level)
{
}

void Level::FrontLayer::render(ew::RenderContext* context)
{
  SDLRenderContext* ctx = static_cast<SDLRenderContext*>(context);
  for(Tile& tile : level->tiles)
  {
    if(tile.x == 0 || tile.y == 0 || tile.x == level->map.at(tile.y).length() - 1 || tile.y == level->map.size() - 1)
      continue;

    if(tile.blocking)
    {
      level->renderTile(ctx->getScreen(), 5, 4, 1, 1, tile.x + 1, tile.y);
    }
  }
}

void Level::BackLayer::render(ew::RenderContext* context)
{
  SDLRenderContext* ctx = static_cast<SDLRenderContext*>(context);
  for(Tile& tile : level->tiles)
  {
    if(tile.x == 0 && tile.y == 0)
    {
      level->renderTile(ctx->getScreen(), 0, 0, 2, 2, tile.x, tile.y);
    }
    else if(tile.x == 0 && tile.y == level->map.size() - 1)
    {
      level->renderTile(ctx->getScreen(), 0, 11, 2, 2, tile.x, tile.y + 1);
    }
    else if(tile.x == level->map.at(tile.y).length() - 1 && tile.y == 0)
    {
      level->renderTile(ctx->getScreen(), 11, 0, 2, 2, tile.x + 1, tile.y);
    }
    else if(tile.x == level->map.at(tile.y).length() - 1 && tile.y == level->map.size() - 1)
    {
      level->renderTile(ctx->getScreen(), 11, 11, 2, 2, tile.x + 1, tile.y + 1);
    }
    else if(tile.x == 0 || tile.x == level->map.at(tile.y).length() - 1)
    {
      int tx = tile.x == 0 ? 0 : 11;
      int ty = 0;
      if(tile.y < level->map.size()/2 - 2)
      {
        ty = 3 - tile.y%2;
      }
      else if(tile.y <= level->map.size()/2 + 2)
      {
        ty = 4 + (tile.y - (level->map.size()/2 - 2));
      }
      else
      {
        ty = 9 + tile.y%2;
      }
      level->renderTile(ctx->getScreen(), tx, ty, 2, 1, tile.x + (tile.x ? 1 : 0), tile.y + (tile.y ? 1 : 0));
    }
    else if(tile.y == 0 || tile.y == level->map.size() - 1)
    {
      int tx = 0;
      int ty = tile.y == 0 ? 0 : 11;
      if(tile.x < level->map.at(tile.y).size()/2 - 2)
      {
        tx = 3 - tile.x%2;
      }
      else if(tile.x <= level->map.at(tile.y).size()/2 + 2)
      {
        tx = 4 + (tile.x - (level->map.at(tile.y).size()/2 - 2));
      }
      else
      {
        tx = 9 + tile.x%2;
      }
      level->renderTile(ctx->getScreen(), tx, ty, 1, 2, tile.x + (tile.x ? 1 : 0), tile.y + (tile.y ? 1 : 0));
    }
    else if(tile.blocking)
    {
      level->renderTile(ctx->getScreen(), 5, 5, 1, 1, tile.x + 1, tile.y + 1);
    }
    else
    {
      level->renderTile(ctx->getScreen(), 5, 7, 1, 1, tile.x + 1, tile.y + 1);
    }
  }
}
