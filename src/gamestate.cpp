#include "gamestate.h"
#include "level.h"
#include "player.h"

void GameState::init()
{
  Level::init();
  Player::init();
  Sword::init();
}

void GameState::term()
{
  Level::term();
  Player::term();
  Sword::term();
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
