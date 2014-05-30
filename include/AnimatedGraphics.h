#ifndef ANIMATEDGRAPHICS_H
#define ANIMATEDGRAPHICS_H

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
  public:
    AnimatedGraphic(const LoaderParams * params, int animSpeed);

    virtual void load(const LoaderParams * params);
    virtual void draw();
    virtual void update();
    virtual void clean();

  private:
    int m_animSpeed;
    int m_numFrames;
};

#endif
