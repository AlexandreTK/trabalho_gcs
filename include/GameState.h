#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>

using std::string;

/*
 * A class to handle the Game States
 * such as Menu, Levels and Credits
 */

class GameState
{
  public:
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    

    virtual string getStateID() const = 0;

};

#endif
