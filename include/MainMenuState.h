#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "MenuState.h"
#include "GameObject.h"

class MainMenuState : public MenuState
{
  public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual string getStateID() const { return menuID; }

  private:
    virtual void setCallbacks(const vector<Callback>& callbacks);

    static void menuToPlay();
    static void exitFromMenu();

    static const string menuID;

    vector<GameObject*> gameObjects;
};

#endif
