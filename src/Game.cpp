#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

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

  /*
   *Creates the Joystick instance.
   */
   
  cout << "Loading sprites..." << endl;
  /*
   * Load sprites used in the game
   */

  TextureManager::Instance()->load("data/images/katw_rock-ground.png", "floor", this->renderer);
  TextureManager::Instance()->load("data/images/katw_kays.png", "kays", this->renderer);
  TextureManager::Instance()->load("data/images/katw_blue-mage.png", "blue-mage", this->renderer);
  TextureManager::Instance()->load("data/images/katw_bg.png", "background", this->renderer);


  player = new Player();
  enemy = new Enemy();

  player->load(10, 600-119-64, 64, 64, "kays");
  enemy->load(600, 600-119-64, 64, 64, "blue-mage");

  gameObjects.push_back(player);
  gameObjects.push_back(enemy);
 
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
  for(vector<GameObject *>::size_type i = 0; i != gameObjects.size(); i++)
  {
    gameObjects[i]->update();
  }
}

void Game::drawLogos()
{
  TextureManager::Instance()->load("data/images/katw_logo-cloud.png", "logo-cloud", this->renderer);
  TextureManager::Instance()->load("data/images/katw_logo-library.png", "logo-library", this->renderer);
  TextureManager::Instance()->load("data/images/katw_logo-tools.png", "logo-tools", this->renderer);
  TextureManager::Instance()->load("data/images/katw_logo-game.png", "logo-game", this->renderer);

  /*
   *  Display logo screen
   */
  SDL_RenderClear(this->renderer);
  TextureManager::Instance()->draw("logo-cloud", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);

  SDL_RenderClear(this->renderer);
  TextureManager::Instance()->draw("logo-library", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);

  SDL_RenderClear(this->renderer);
  TextureManager::Instance()->draw("logo-tools", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);

  SDL_RenderClear(this->renderer);
  TextureManager::Instance()->draw("logo-game", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(3000);
}

/*
 * Draw the textures of the game
 */
void Game::draw()
{
  SDL_RenderClear(this->renderer);
  /*
   * Draw images to renderer
   */
  for(vector<GameObject *>::size_type i = 0; i != gameObjects.size(); i++)
  {
    gameObjects[i]->draw(this->renderer);
  }

  TextureManager::Instance()->draw("background", 0, 0, 800, 600, this->renderer);

  TextureManager::Instance()->draw("floor", 0, 600-119, 800, 119, this->renderer);
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
    switch(event.key.keysym.sym)
    {
      case SDLK_ESCAPE:
        event.type = SDL_QUIT;
        cout << "Stopping application." << endl;
        this->running = false;
        break;

      default:
        break;
    }
  }
}
