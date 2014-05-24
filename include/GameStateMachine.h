#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include "GameState.h"
#include <vector>

using std::vector;

class GameStateMachine
{
  public:

    void pushState(GameState * state);
    void changeState(GameState * state);

    void update();
    void render();

    void popState();

  private:
    vector<GameState *> gameStates;
};

#endif
