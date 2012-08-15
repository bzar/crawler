#include "gamephase.h"
#include "SDL/SDL.h"

GamePhase::GamePhase(GameWorld* world, ew::Engine* engine) :
  world(world), engine(engine)
{

}

void GamePhase::execute(float const delta)
{
  if(engine->getControlContext()->keyDown(SDLK_ESCAPE))
  {
    engine->quit();
  }
}
