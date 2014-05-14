#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <string>

using std::string;

class GameObject
{
  public:

    virtual void draw()=0;
    virtual void update()=0;
    virtual void clean()=0;

  protected:
    GameObject(const LoaderParams* params){}
    virtual ~GameObject(){}
};

#endif
