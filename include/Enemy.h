#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy:public GameObject
{
  public:
    void load(int x, int y, int w, int h, string textureID);
    void draw(SDL_Renderer * renderer);
    void update();
    void clean();
};

#endif
