#include "PauseState.h"
#include "StateParser.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "Game.h"

const string PauseState::pauseID = "PAUSE";

void PauseState::pauseToMain()
{
/*  TheGame::Instance()->getStateMachine()->changeState(new MenuState()); */
}

void PauseState::resumePlay()
{
/*
  TheGame::Instance()->getStateMachine()->popState(); */
}

void PauseState::update()
{
  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->update();
  }
}

void PauseState::render()
{
  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    gameObjects[i]->draw();
  }
}

bool PauseState::onEnter()
{
  StateParser stateParser;
  stateParser.parseState("test.xml", pauseID, &gameObjects, &m_textureIDList);


  m_callbacks.push_back(0);
  m_callbacks.push_back(pauseToMain);
  m_callbacks.push_back(resumePlay);

  setCallbacks(m_callbacks);

  return true;
}

bool PauseState::onExit()
{
  for(unsigned int i = 0; i < m_textureIDList.size(); i++)
  {
    TheTextureManager::Instance()->clearFromTexture(m_textureIDList[i]);
  }
  return true;
}

void PauseState::setCallbacks(const vector<Callback>& callbacks)
{
  for(unsigned int i = 0; i < gameObjects.size(); i++)
  {
    if(dynamic_cast<MenuButton*>(gameObjects[i]))
    {
      MenuButton * button = dynamic_cast<MenuButton *>(gameObjects[i]);
      button->setCallback(callbacks[button->getCallbackID()]);
    }
  }
}
