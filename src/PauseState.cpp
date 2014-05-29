#include "PauseState.h"
#include "MenuState.h"
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
  return true;
}

bool PauseState::onExit()
{
  return true;
}
