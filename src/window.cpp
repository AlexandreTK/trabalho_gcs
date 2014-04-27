#include <iostream>
#include "window.h"
#include <SDL.h>

using std::cout;
using std::endl;

bool loadMedia();
void close();

Texture charTexture;
Texture bgTexture;
SDL_Window * window;
SDL_Renderer * renderer;

bool loadMedia()
{
  /*
   * Try to load character sprite file
   */
  if(!charTexture.loadFromFile())
  {
    cout << "Failed to load character sprite!" << endl;
    return false;
  }

  /*
   * Try to load background file
   */
  if(!bgTexture.loadFromFile())
  {
    cout << "Failed to load background" << endl;
    return false;
  }

  return true;
}

void close()
{
  charTexture.free();
  bgTexture.free();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  IMG_Quit();
  SDL_Quit();
}

bool init()
{
  /*
   * Initializing SDL
   */
  if(SDL_INIT(SDL_INIT_VIDEO) < 0)
  {
    cout << "SDL could not initialize video: " << SDL_GetError() << endl;
    return false;
  }
  /*
   * Linear texture filtering
   */
  if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
  {
    cout << "Warning: Linear texture filtering not enabled" << endl;
  }

  /*
   * Create window
   */
  window = SDL_CreateWindow("Kays Against The World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
  if(!window)
  {
    cout << "Failed to create window: " << SDL_GetError() << endl;
    return false;
  }
  /*
   * Create vsynced renderer for window
   */
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENT_VSYNC);
  if(!renderer)
  {
    cout << "Failed to create renderer: " << SDL_GetError() << endl;
    return false;
  }
  
  /*
   * Initialize renderer color
   */
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  /*
   * Initialize IMG loading
   */
  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags))
  {
    cout << "Failed to initialize SDL_image: " << SDL_GetError() << endl;
    return false;
  }

  return true;
}

int Window::OpenWindow()
{

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
    cout << "Failed to create window: " << SDL_GetError() << endl;
  }

  atexit( SDL_Quit );
  SDL_Delay( 5000 );
  
  return 0;
}
