#include "PlayState.h"
#include <iostream>

using std::cout;
using std::endl;

const string PlayState::playID = "PLAY";

void PlayState::update()
{
  /*
   * Nothing to do for now
   */
}

void PlayState::render()
{
  /*
   * Nothing to do for now
   */
}

bool PlayState::onEnter()
{
  cout << "Entering Play State..." << endl;
  
  return true;
}


bool PlayState::onExit()
{
  cout << "Leaving Play State..." << endl;

  return true;
}
