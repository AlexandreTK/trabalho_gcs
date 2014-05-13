#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <string>

using std::string;

class GameObject
{
  public:

    void load(int x, int y, int w, int h, string textureID);
    void draw(SDL_Renderer * renderer);
    void update();
    void clean();

  protected:

    string textureID;

    int currentFrame;
    int currentRow;

    int x;
    int y;

    int w;
    int h;
};

#endif
