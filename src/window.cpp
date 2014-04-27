#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "window.h"
#include "texture.h"
#include "character.h"

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
  if(!charTexture.loadFromFile("data/images/mage.png", renderer))
  {
    cout << "Failed to load character sprite!" << endl;
    return false;
  }

  /*
   * Try to load background file
   */
  if(!bgTexture.loadFromFile("data/images/bg.png", renderer))
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
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
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
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

bool Window::openWindow()
{
  /*
   * Start up SDL and create window and render
   */
  if(!init())
  {
    cout << "Failed to initialize" << endl;
    return false;
  }
  /*
   * Try to load media
   */
  if(!loadMedia())
  {
    cout << "Failed to load media" << endl;
    return false;
  }

  /*
   * Loop flag
   */
  bool quit = false;

  /*
   * Event handler
   */
  SDL_Event e;

  /*
   * Character sprite
   */
  Character char;

  /*
   * Current display mode
   */
  SDL_DisplayMode currentMode;

  if(SDL_GetCurrentDisplayMode(0, &currentMode) != 0)
  {
    cout << "Failed to get current display mode: " << SDL_GetError() << endl;
    return false;
  }

  /*
   * Camera area
   */
  SDL_Rect camera = {0, 0, current.w, current.h};

  /*
   * While application is running
   */
  while(!quit)
  {
    /*
     * Handle events on queue
     */
    while(SDL_PollEvent(&e) != 0)
    {
      /*
       * User wants to quit
       */
      if(e.type == SDL_Quit)
      {
        quit = true;
      }

    }

    /*
     * Centers the camera at the character
     */
    camera.x = (char.getPosX() + char.getWidth/2) - currentMode.w/2;
    camera.y = (char.getPosY() + char.getHeight/2) - currentMode.h/2;
    
    /*
     * Clear screen
     */
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    /*
     * Render background
     */
    bgTexture.render(0, 0, &camera, renderer);

    /*
     * Render character
     */

    charTexture.render(char.getPosX() - camera.x, char.getPosY() - camera.y, renderer)

    /*
     * Update screen
     */
    SDL_RenderPresent(renderer)
  }
}
