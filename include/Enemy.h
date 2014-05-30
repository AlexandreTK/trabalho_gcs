#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
  public:
    Enemy();

    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif
