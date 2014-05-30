#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "GameObject.h"
#include "Level.h"
#include <vector>

using std::vector;

class PlayState : public GameState
{
  public:
    
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual string getStateID() const { return playID; }

  private:
    
    static const string playID;
    Level * pLevel;

    vector<GameObject *> gameObjects;
};

#endif
