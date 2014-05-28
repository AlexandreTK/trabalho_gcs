#include "PlayState.h"
#include "Player.h"
#include "Game.h"
#include "TextureManager.h"
#include <iostream>

using std::cout;
using std::endl;

const string PlayState::playID = "PLAY";

void PlayState::update()
{
  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->update();
  }
}

void PlayState::render()
{
  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->draw();
  }
}

bool PlayState::onEnter()
{
  if(!TheTextureManager::Instance()->load("data/images/katw_kays_a.png", "kays", TheGame::Instance()->getRenderer()))
  {
    return false;
  }

  GameObject * player = new Player(new LoaderParams(10, 600-119-64, 64, 64, "kays"));

  gameObjects.push_back(player);
  
  cout << "Entering Play State..." << endl;

  return true;
}


bool PlayState::onExit()
{
  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->clean();
  }

  gameObjects.clear();

  TheTextureManager::Instance()->clearFromTexture("kays");

  cout << "Leaving Play State..." << endl;

  return true;
}
