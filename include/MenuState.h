#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"

/*
 * Class that handles the game state
 * Menu
 */

class MenuState : public GameState
{
  public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual string getStateID() const { return menuID; }

  private:

    static const string menuID;
};

#endif
