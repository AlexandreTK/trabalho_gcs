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
    Vector2D m_position;

<<<<<<< HEAD
  protected:
    int x;
    int y;
=======
  private:
>>>>>>> 1ebb34d9d33b87a0042350431ffafc54bc9068b1

    int w;
    int h;

    int currentRow;

    string textureID;

};

#endif
