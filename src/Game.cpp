#include "Game.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "MenuState.h"
#include "PlayState.h"

using std::cout;
using std::endl;

Game * Game::instance = NULL;

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
  TheInputHandler::Instance()->clean();

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
   TheInputHandler::Instance()->initializeJoysticks();
  cout << "Loading sprites..." << endl;
  /*
   * Load sprites used in the game
   */
  TheTextureManager::Instance()->load("data/images/katw_rock-ground.png", "floor", this->renderer);
  TheTextureManager::Instance()->load("data/images/katw_red-mage.png", "red-mage", this->renderer);
  TheTextureManager::Instance()->load("data/images/katw_blue-mage.png", "blue-mage", this->renderer);
  TheTextureManager::Instance()->load("data/images/katw_skeleton.png", "skeleton", this->renderer);
  TheTextureManager::Instance()->load("data/images/katw_necromancer.png", "necromancer", this->renderer);
  TheTextureManager::Instance()->load("data/images/katw_bg.png", "background", this->renderer);

  /*
  TheTextureManager::Instance()->draw("kays", 10, 600-119-64, 64, 64, this->renderer);
  
  TheTextureManager::Instance()->draw("blue-mage", 100, 600-119-64, 64, 64, this->renderer, SDL_FLIP_HORIZONTAL);
  */
  if(!TheTextureManager::Instance()->load("data/images/katw_kays_a.png", "kays", TheGame::Instance()->getRenderer()))
  {
    return false;
  }

  GameObject * player = new Player();
  player->load(new LoaderParams(10, 600-119-64, 64, 64, "kays", 8));

  gameObjects.push_back(player);
 
  GameObject * enemy = new Enemy();
  
  enemy->load(new LoaderParams(700, 600-119-64, 64, 64, "blue-mage", 1));

  gameObjects.push_back(enemy);

  /*
   * Initializes the game state machine
   */



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

  SDL_Event event;
  /*
   * Check if any event happened
   */
  while(SDL_PollEvent(&event))
  {
    TheInputHandler::Instance()->handle(event);    

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
      /*gameStateMachine->changeState(new PlayState()); */
    }
  }
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

/* * Update the screen of the game */
void Game::update()
{

  /*gameStateMachine->update();*/
  for(vector<GameObject *>::size_type i = 0; i != gameObjects.size(); i++)
  {
    gameObjects[i]->update();
  }
 
}

void Game::drawLogos()
{
  TheTextureManager::Instance()->load("data/images/katw_logo-cloud.png", "logo-cloud", this->renderer);
  TheTextureManager::Instance()->load("data/images/katw_logo-library.png", "logo-library", this->renderer);
  TheTextureManager::Instance()->load("data/images/katw_logo-tools.png", "logo-tools", this->renderer);
  TheTextureManager::Instance()->load("data/images/katw_logo-game.png", "logo-game", this->renderer);

  /*
   *  Display logo screen
   */
  SDL_RenderClear(this->renderer);
  TheTextureManager::Instance()->draw("logo-cloud", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);

  SDL_RenderClear(this->renderer);
  TheTextureManager::Instance()->draw("logo-library", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);

  SDL_RenderClear(this->renderer);
  TheTextureManager::Instance()->draw("logo-tools", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(2000);

}

void Game::drawCredits()
{
  TheTextureManager::Instance()->load("data/images/katw_credits.png", "credits", this->renderer);

  SDL_RenderClear(this->renderer);
  TheTextureManager::Instance()->draw("credits", 0, 0, 800, 600, this->renderer);
  SDL_RenderPresent(this->renderer);
  SDL_Delay(5000);
}

void Game::drawMenu()
{
  SDL_Event event;
  bool menuOn = true;
  /*
   * Check if any event happened
   */
  while(menuOn)
  {
    while(SDL_PollEvent(&event))
    {
      SDL_RenderClear(this->renderer);
      TheTextureManager::Instance()->draw("logo-game", 0, 0, 800, 600, this->renderer);
      SDL_RenderPresent(this->renderer);


      TheInputHandler::Instance()->handle(event);    

      if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
      {
        menuOn = false;
      }
    }
  }
}

/*
 * Draw the textures of the game
 */
void Game::draw()
{
  SDL_RenderClear(this->renderer);

  /*gameStateMachine->render();*/

  /*
   * Draw images to renderer
   */
  TheTextureManager::Instance()->draw("background", 0, 0, 800, 608, this->renderer);

  TheTextureManager::Instance()->draw("floor", 0, 0, 800, 608, this->renderer);

  TheTextureManager::Instance()->draw("red-mage", 650, 600-119-64, 64, 64, this->renderer, SDL_FLIP_HORIZONTAL);

  TheTextureManager::Instance()->draw("skeleton", 500, 600-119-64, 64, 64, this->renderer, SDL_FLIP_HORIZONTAL);

  TheTextureManager::Instance()->draw("necromancer", 700, 600-119-75, 64, 75, this->renderer, SDL_FLIP_HORIZONTAL);

  for(vector<GameObject *>::size_type i = 0; i != gameObjects.size(); i++)
  {
    gameObjects[i]->draw();
  }
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


}

void Game::finishGame()
{
  running = false;
}

bool Game::checkCollision(SDLGameObject * p1, SDLGameObject * p2)
{
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = p1->getPosition().getX();
  rightA = p1->getPosition().getX() + p1->getWidth();
  topA = p1->getPosition().getY();
  bottomA = p1->getPosition().getY() + p1->getHeight();

  leftB = p2->getPosition().getX();
  rightB = p2->getPosition().getX() + p2->getWidth();
  topB = p2->getPosition().getY();
  bottomB = p2->getPosition().getY() + p2->getWidth();

  if(bottomA <= topB) { return false; }
  if(topA >= bottomB) { return false; }
  if(rightA <= leftB) { return false; }
  if(leftA >= rightB) { return false; }

  return true;
}
