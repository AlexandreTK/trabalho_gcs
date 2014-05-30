#include "MainMenuState.h"
#include "TextureManager.h"
#include "StateParser.h"
#include "MenuButton.h"
#include <iostream>

using std::cout;
using std::endl;

bool MainMenuState::onEnter()
{
  StateParser stateParser;
  stateParser.parseState("test.xml", menuID, &gameObjects, &m_textureIDList);

  callbacks.push_back(0);
  callbacks.push_back(menuToPlay);
  callbacks.push_back(exitFromMenu);

  setCallbacks(callbacks);

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

void MainMenuState::onEnter()
{
  for(unsigned int i = 0; i < m_textureIDList.size(); i++)
  {
    TheTextureManager::Instance()->clearFromTexture(m_textureIDList[i]);
  }
}
