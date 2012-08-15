#include "gameworld.h"
#include "player.h"

GameWorld::GameWorld() :
  ew::RenderableWorld(), ew::UpdatableWorld(),
  ew::CollidableWorld(), ew::ControllableWorld(),
  ew::TileCollidableWorld(),
  level(new Level(this))
{
  new Player(this, {110, 110});
}


std::vector<ew::TileCollidableWorld::TileCollideRect> GameWorld::getCollidingTiles(TileCollideRect const& rect)
{
  auto tiles = level->getIntersectingTiles(rect.x, rect.y, rect.w, rect.h);

  std::vector<TileCollideRect> result;
  for(auto tile : tiles)
  {
    float x = tile.x;
    float y = tile.y;
    float w = Level::TILE_SIZE;
    float h = Level::TILE_SIZE;
    result.push_back({x, y, w, h});
  }
  return result;
}
