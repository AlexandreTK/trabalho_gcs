#include "MenuState.h"
#include <iostream>

using std::cout;
using std::endl;

const string MenuState::menuID = "MENU";

void MenuState::update()
{
  /*
   * Nothing to do for now
   */
}

void MenuState::render()
{
  /*
   * Nothing to do for now
   */
}

bool MenuState::onEnter()
{
  cout << "Entering Menu State..." << endl;
  
  return true;
}


bool MenuState::onExit()
{
  cout << "Leaving Menu State..." << endl;

  return true;
}
