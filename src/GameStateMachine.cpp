#include "GameStateMachine.h"

void GameStateMachine::update()
{
  if(!gameStates.empty())
  {
    gameStates.back()->update();
  }
}

void GameStateMachine::render()
{
  if(!gameStates.empty())
  {
    gameStates.back()->render();
  }
}


/*
 * Push the current game state into the stack
 */

void GameStateMachine::pushState(GameState * state)
{
  gameStates.push_back(state);
  gameStates.back()->onEnter();
}

/*
 * Pop the last game state from the game state stack
 */

void GameStateMachine::popState()
{
  /*
   * Check whether the stack is empty or not
   */
  if(!gameStates.empty())
  {
    /*
     * Leaving current game state
     */
    if(gameStates.back()->onExit())
    {
      delete gameStates.back();
      gameStates.pop_back();
    }
  }
}

void GameStateMachine::changeState(GameState * state)
{
  if(!gameStates.empty())
  {
    /*
     * Check if current game state is the same as
     * the one we're about to change into
     */
    if(gameStates.back()->getStateID() == state->getStateID())
    {
      /*
       * Nothing to do
       */
      return;
    }

    if(gameStates.back()->onExit())
    {
      delete gameStates.back();
      gameStates.pop_back();
    }
  }

  /*
   * Push current game state into the stack
   */
  gameStates.push_back(state);

  /*
   * Initialize it
   */
  gameStates.back()->onEnter();
}
