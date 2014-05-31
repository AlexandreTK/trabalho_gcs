#include "MainMenuState.h"
#include "TextureManager.h"
#include "StateParser.h"
#include "MenuButton.h"
#include <iostream>

using std::cout;
using std::endl;

bool MainMenuState::onEnter()
{
  for(unsigned int i = 0; i < m_textureIDList.size(); i++)
  {
    TheTextureManager::Instance()->clearFromTexture(m_textureIDList[i]);
  }

  StateParser stateParser;
  stateParser.parseState("test.xml", getStateID(), &gameObjects, &m_textureIDList);

  m_callbacks.push_back(0);
  m_callbacks.push_back(menuToPlay);
  m_callbacks.push_back(exitFromMenu);

  setCallbacks(m_callbacks);

  cout << "entering MenuState" << endl;
  return true;
}

void MainMenuState::setCallbacks(const vector<Callback>& callbacks)
{
  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    if(dynamic_cast<MenuButton*>(gameObjects[i]))
    {
      MenuButton * button = dynamic_cast<MenuButton*>(gameObjects[i]);
      button->setCallback(callbacks[button->getCallbackID()]);
    }
  }
}

void MainMenuState::menuToPlay()
{

}

void MainMenuState::exitFromMenu()
{

}
