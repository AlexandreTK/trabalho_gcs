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

    virtual void draw(SDL_RendererFlip flags=SDL_FLIP_NONE);
    virtual void update();
    virtual void clean();
  protected:
    Vector2D m_velocity;
    Vector2D m_acceleration;
    int currentFrame;
    Vector2D m_position;

  private:

    int w;
    int h;
    int x;
    int y;

    int currentRow;

    string textureID;

};

#endif
