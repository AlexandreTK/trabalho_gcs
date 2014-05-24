#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"

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

};

#endif
