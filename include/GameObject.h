#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "LoaderParams.h"
#include <SDL.h>


using std::string;

class GameObject
{
  public:

    virtual void draw()=0;
    virtual void update()=0;
    virtual void clean()=0;

    //new load function
    virtual void load(const LoaderParams* pParams) =0;

  protected:
    GameObject(){}
    virtual ~GameObject(){}
};

#endif
