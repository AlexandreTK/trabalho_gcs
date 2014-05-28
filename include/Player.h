#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "InputHandler.h"

class Player : public SDLGameObject
{
  public:
    Player(const LoaderParams * params);

    virtual void draw(SDL_RendererFlip flags=SDL_FLIP_NONE);
    virtual void update();
    virtual void clean();
  private:
    void handleInput();
};

#endif
