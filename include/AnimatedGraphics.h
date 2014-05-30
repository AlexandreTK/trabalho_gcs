#ifndef ANIMATEDGRAPHICS_H
#define ANIMATEDGRAPHICS_H

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
  public:
    AnimatedGraphic(const LoaderParams * params);

    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif
