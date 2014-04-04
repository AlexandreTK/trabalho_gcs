#include <iostream>
#include "window.h"
#include <SDL2/SDL.h>

using std::cout;
using std::endl;


int Window::OpenWindow()
{
  /*
   * Creating the window and renderer
   * to be used in the game.
  */
  SDL_Window * window;
  SDL_Renderer * renderer;

  /*
   * The flag that tells
   * the mode the window
   * and renderer will be
   * created
  */
  Uint32 flags;

  /*
   * Initializing the variables
   * there are going to be used
  */
  window = NULL;
  renderer = NULL;
  flags = SDL_WINDOW_FULLSCREEN_DESKTOP;

  /*
   * Creating the window and renderer
  */
  if( SDL_CreateWindowAndRenderer(0, 0, flags, &window, &renderer) < 0 )
  {
    cout << "Erro: " << SDL_GetError() << endl;
  }

  atexit( SDL_Quit );
  SDL_Delay( 5000 );
  
  return 0;
}
