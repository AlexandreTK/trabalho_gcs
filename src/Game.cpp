#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

/*
 * Constructor
 */
Game::Game()
{
  this->level = 1;
  this->running = true;
  atexit(SDL_Quit);
}

/*
 * Destructor
 */
Game::~Game()
{
  this->level = 0;
  this->running = false;

  cout << "Cleaning game..." << endl;

  /*
   * Deallocate window and renderer
   */
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);

  this->window = NULL;
  this->renderer = NULL;

  this->shutdown();
}

/*
 * Initialize game
 */
bool Game::init(const char * title, int x, int y, int w, int h, int flags)
{
  cout << "Initialization" << endl;

  /*
   * Initialize SDL video module
   */
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    cout << "SDL initialization failed: " <<  SDL_GetError() << endl;
    return false;
  }

  cout << "SDL initialization successful." << endl;

  /*
   * Create SDL window
   */
  this->window = SDL_CreateWindow(title, x, y, w, h, flags);

  /*
   * Check if window was successfully created
   * If it returns 0, then it failed
   */
  if(window == 0)
  {
    cout << "Window creation failed: " << SDL_GetError() << endl;
    return false;
  }

  cout << "Window creation successful." << endl;

  /*
   * Create SDL renderer from window
   */
  this->renderer = SDL_CreateRenderer(window, -1, 0);

  /*
   * Check if renderer was successfully created
   * If it returns 0, then it failed
   */
  if(renderer == 0)
  {
    cout << "Renderer creation failed: " << SDL_GetError() << endl;
    return false;
  }

  cout << "Renderer creation successful." << endl;

  cout << "Loading sprites..." << endl;
  /*
   * Load sprites used in the game
   */
  textureManager.load("data/images/katw_logo-cloud.png", "logo-cloud", this->renderer);
  textureManager.load("data/images/katw_logo-library.png", "logo-library", this->renderer);
  textureManager.load("data/images/katw_logo-tools.png", "logo-tools", this->renderer);

  textureManager.load("data/images/katw_rock-ground.png", "floor", this->renderer);
  textureManager.load("data/images/katw_kays.png", "kays", this->renderer);
  textureManager.load("data/images/katw_red-mage.png", "red-mage", this->renderer);
  textureManager.load("data/images/katw_blue-mage.png", "blue-mage", this->renderer);
  textureManager.load("data/images/katw_skeleton.png", "skeleton", this->renderer);
  textureManager.load("data/images/katw_necromancer.png", "necromancer", this->renderer);
  textureManager.load("data/images/katw_bg.png", "background", this->renderer);

 
  return true;
}

/*
 * Check whether the level has finished or not
 */
bool Game::levelFinished()
{
  cout << "Is the level over?" << endl;

  return true;
}

/*
 * Go to the next level
 */
int Game::nextLevel()
{
  cout << "Next level?" << endl;

  return 0;
}

/*
 * Shutdown the game
 */
void Game::shutdown()
{
  cout << "Shutdown" << endl;
}

/*
 * Update the time run since the game's beginning
 */
void Game::updateTimeStep()
{
}

/*
 * Loads the input 
 */
void Game::input()
{
}

/*
 * Loads the IA of the game
 */
void Game::ia()
{
}

/*
 * Loads the physics
 */
void Game::physics()
{
}

/*
 * Update the screen of the game
 */
void Game::update()
{ 
 /*
  * Clear renderer to draw
  * the rest of the animation
  * spritesheets
  */
  SDL_RenderClear(renderer);
}

void Game::drawLogos()
{
 /*
   * Display logo screen
   */
  this->update();
  textureManager.draw("logo-cloud", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);
  this->update();
  textureManager.draw("logo-library", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);
  this->update();
  textureManager.draw("logo-tools", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);
}

/*
 * Draw the textures of the game
 */
void Game::draw()
{
  /*
   * Draw images to renderer
   */
  this->textureManager.draw("background", 0, 0, 800, 600, this->renderer);

  this->textureManager.draw("floor", 0, 600-119, 800, 119, this->renderer);

  this->textureManager.draw("kays", 10, 600-119-64, 64, 64, this->renderer);
  
  this->textureManager.draw("blue-mage", 100, 600-119-64, 64, 64, this->renderer, SDL_FLIP_HORIZONTAL);

  this->textureManager.draw("red-mage", 650, 600-119-64, 64, 64, this->renderer, SDL_FLIP_HORIZONTAL);

  this->textureManager.draw("skeleton", 500, 600-119-64, 64, 64, this->renderer, SDL_FLIP_HORIZONTAL);

  this->textureManager.draw("necromancer", 700, 600-119-75, 64, 75, this->renderer, SDL_FLIP_HORIZONTAL);

  /*
   * Draw to the screen
   */
  SDL_RenderPresent(this->renderer);
}

/*
 * Set the level of the game
 */
void Game::setLevel(int inputLevel)
{
  this->level = inputLevel;
}

/*
 * Get current level
 */
int Game::getLevel()
{
  return this->level;
}

/*
 * Get game status
 * Check if it's running or not
 */
bool Game::getRunning()
{
  return this->running;
}

/*
 * Handle events
 */
void Game::event()
{
  SDL_Event event;

  /*
   * Check if any event happened
   */
  if(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        cout << "Stoping running." << endl;
        this->running = false;
        break;

      default:
        break;
    }
  }
}
