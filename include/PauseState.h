#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "GameObject.h"
#include <vector>

using std::vector;

class PauseState : public GameState
{
  public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual string getStateID() const { return pauseID; }

  private:

    static void pauseToMain();
    static void resumePlay();

    static const string pauseID;

    vector<GameObject *> gameObjects;
};

#endif
