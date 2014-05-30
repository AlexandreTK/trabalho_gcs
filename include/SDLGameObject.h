#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include <string>
#include "Vector2D.h"
#include "GameObjectFactory.h"

using std::string;

class SDLGameObject : public GameObject
{
  public:
    SDLGameObject();

    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    Vector2D& getPosition() { return m_position; }
    int getWidth() { return w; }
    int getHeight() { return h; }
  protected:
    Vector2D m_velocity;
    Vector2D m_acceleration;
    int currentFrame;
    int currentRow;
    Vector2D m_position;
    SDL_RendererFlip flip;
    int m_numFrames;

  private:

    int w;
    int h;
    int x;
    int y;


    string textureID;

};

#endif
