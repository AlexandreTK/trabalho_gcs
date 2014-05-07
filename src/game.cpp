#include "game.h"
#include <iostream>

using std::cout;
using std::endl;

/*
 * Constructor
 */
Game::Game()
{
  this->level = 0;
}

/*
 * Destructor
 */
Game::~Game()
{
}

/*
 * Initialize game
 */
int Game::init()
{
  cout << "Initialization" << endl;

  return 1;
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
}

/*
 * Draw the textures of the game
 */
void Game::draw()
{
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
