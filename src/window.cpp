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

Texture characterTexture;
Texture bgTexture;
SDL_Window * window;
SDL_Renderer * renderer;

bool loadMedia()
{
  /*
   * Try to load characteracter sprite file
   */
  if(!characterTexture.loadFromFile("data/images/mage.png", renderer))
  {
    cout << "Failed to load characteracter sprite!" << endl;
    return false;
  }

  characterTexture.setWidth(64);
  characterTexture.setHeight(64);

  /*
   * Try to load background file
   */
  if(!bgTexture.loadFromFile("data/images/bg.png", renderer))
  {
    cout << "Failed to load background" << endl;
    return false;
  }

  bgTexture.setWidth(3468);
  bgTexture.setHeight(769);
  return true;
}

void close()
{
  characterTexture.free();
  bgTexture.free();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = NULL;
  window = NULL;

  IMG_Quit();
  SDL_Quit();
}

bool initialize()
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
  if(!initialize())
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
  Character character;

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
  SDL_Rect camera = {0, 0, currentMode.w, currentMode.h};

  character.setWidth(64);
  character.setHeight(64);

  /*
   * Centers the camera at the characteracter
   */
  camera.x = (character.getPosX() + character.getWidth()/2) - currentMode.w/8;
  camera.y = (character.getPosY() + character.getHeight()/2) - currentMode.h/8;
   
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

  character.setPosX(200);
  character.setPosY(600);
  characterTexture.render(character.getPosX() - camera.x, character.getPosY() - camera.y, NULL, renderer);

  /*
   * Update screen
   */
  SDL_RenderPresent(renderer);

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
      switch(e.type)
      {
        case SDL_QUIT:
          quit = true;
          break;
        case SDLK_ESCAPE:
          quit = true;
          break;
      }
    }
  }
  
  return true;
}
