#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include <string>
#include "Vector2D.h"

using std::string;

class SDLGameObject : public GameObject
{
  public:
    SDLGameObject(const LoaderParams * params);

    virtual void draw();
    virtual void update();
    virtual void clean();
  protected:
    Vector2D m_velocity;
    Vector2D m_acceleration;
    int currentFrame;
    int currentRow;
    Vector2D m_position;
    SDL_RendererFlip flip;

  private:

    int w;
    int h;
    int x;
    int y;


    string textureID;

};

#endif
