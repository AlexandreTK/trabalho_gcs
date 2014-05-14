#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include <string>

using std::string;

class SDLGameObject : public GameObject
{
  public:
    SDLGameObject(const LoaderParams * params);

    virtual void draw();
    virtual void update();
    virtual void clean();

  private:
    int x;
    int y;

    int w;
    int h;

    int currentRow;
    int currentFrame;

    string textureID;
};

#endif
