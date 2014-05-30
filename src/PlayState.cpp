#include "PlayState.h"
#include "StateParser.h"
#include "Player.h"
#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include "LevelParser.h"

using std::cout;
using std::endl;

const string PlayState::playID = "PLAY";

void PlayState::update()
{
  pLevel->update();
  
  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->update();
  }
}

void PlayState::render()
{
  pLevel->render();

  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->draw();
  }
}

bool PlayState::onEnter()
{
  LevelParser levelParser;
  pLevel = levelParser.parseLevel("data/levels/lvl1.tmx");

  StateParser stateParser;
  stateParser.parseState("test.xml", playID, &gameObjects, &m_textureIDList);

  cout << "Entering Play State..." << endl;

  return true;
}


bool PlayState::onExit()
{
  for(unsigned int i = 0; i < m_textureIDList.size(); i++)
  {
    TheTextureManager::Instance()->clearFromTexture(m_textureIDList[i]);
  }
  cout << "Leaving Play State..." << endl;

  return true;
}
