#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <SDL.h>
#include "GameObject.h"

using std::string;

class Player:public GameObject // inherit from GameObject
{
  public:

    void load(int x, int y, int w, int h, string textureID);
    void draw(SDL_Renderer * renderer);
    void update();
    void clean();
};

#endif
