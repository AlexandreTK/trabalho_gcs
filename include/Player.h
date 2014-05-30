#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "InputHandler.h"

class Player : public SDLGameObject
{
  public:
    Player();

    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
  private:
    void handleInput();
};



#endif
