#include "SDL/SDL.h"

#include "ew/engine.h"
#include "ew/integration/sdlcontrolcontext.h"
#include "ew/integration/sdltimecontext.h"
#include "ew/integration/sdlrendercontext.h"
#include "gamestate.h"

#include <cstdlib>
#include <random>

int const WIDTH = 800;
int const HEIGHT = 480;

int gameloop(SDL_Surface* screen);

int main(int argc, char** argv)
{
  SDL_Init( SDL_INIT_EVERYTHING );
  SDL_Surface* screen = SDL_SetVideoMode( WIDTH, HEIGHT, 24, SDL_SWSURFACE );

  int retval = gameloop(screen);

  SDL_Quit();

  return retval;
}

int gameloop(SDL_Surface* screen)
{
  SDLControlContext controlContext;
  SDLRenderContext renderContext(screen);
  SDLTimeContext timeContext;
  ew::Engine engine(&controlContext, &renderContext, &timeContext);

  GameState::init();
  GameState game(&engine);
  engine.addState(0, &game);
  engine.setState(0);

  engine.run();

  GameState::term();

  return EXIT_SUCCESS;
}
