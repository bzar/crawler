#ifndef GAMEWORLD_HH
#define GAMEWORLD_HH

#include "ew/renderableworld.h"
#include "ew/updatableworld.h"
#include "ew/collidableworld.h"
#include "ew/controllableworld.h"
#include "ew/tilecollidableworld.h"

#include "level.h"

class GameWorld : public ew::RenderableWorld, public ew::UpdatableWorld,
                  public ew::CollidableWorld, public ew::ControllableWorld,
                  public ew::TileCollidableWorld
{
public:
  GameWorld();
  std::vector<TileCollideRect> getCollidingTiles(TileCollideRect const& rect);

private:
  Level* level;
};

#endif
