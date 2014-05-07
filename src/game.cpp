#include "game.h"
#include <iostream>

using std::cout;
using std::endl;

Game::Game()
{
  this->level = 0;
}

int Game::init()
{
  cout << "Initialization" << endl;

  return 1;
}

bool Game::levelFinished()
{
  cout << "Is the level over?" << endl;

  return true;
}

int Game::nextLevel()
{
  cout << "Next level?" << endl;

  return 0;
}

void Game::shutdown()
{
  cout << "Shutdown" << endl;
}

void Game::updateTimeStep()
{
}

void Game::input()
{
}

void Game::ia()
{
}

void Game::physics()
{
}

void Game::update()
{
}

void Game::draw()
{
}

void Game::setLevel(int inputLevel)
{
  this->level = inputLevel;
}

int Game::getLevel()
{
  return this->level;
}
