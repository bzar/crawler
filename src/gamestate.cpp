#include "gamestate.h"

void GameState::init()
{
}

void GameState::term()
{
}

GameState::GameState(ew::Engine* engine) :
  ew::State(engine, &world), world(),
  game(&world, engine), update(&world), collide(&world),
  render(&world, engine->getRenderContext()),
  control(&world, engine->getControlContext()),
  tileCollide(&world)
{
  setPhases({&control, &update, &tileCollide, &collide, &render, &game});
}
