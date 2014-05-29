#include "MenuState.h"
#include "PlayState.h"
#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

const string MenuState::menuID = "MENU";

void MenuState::menuToPlay()
{
  cout << "ENTER pressed" << endl;
/*  TheGame::Instance()->getStateMachine()->changeState(new PlayState()); */
}

void MenuState::update()
{
  for(unsigned int i = 0; i < this->gameObjects.size(); i++)
  {
    this->gameObjects[i]->update();
  }
}

void MenuState::render()
{
  for(unsigned int i = 0; i < this->gameObjects.size(); i++)
  {
    this->gameObjects[i]->draw();
  }
}

bool MenuState::onEnter()
{
  cout << "Entering Menu State..." << endl;
  
  if(!TheTextureManager::Instance()->load("data/images/katw_logo-game.png", "gamemenu", TheGame::Instance()->getRenderer()))
  {
    return false;
  }

  return true;
}


bool MenuState::onExit()
{
  cout << "Leaving Menu State..." << endl;

  return true;
}
