#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
  public:
    Enemy(const LoaderParams * params);

    virtual void draw(SDL_RendererFlip flags=SDL_FLIP_NONE);
    virtual void update();
    virtual void clean();
};

#endif
