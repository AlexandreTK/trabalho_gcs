#include "AnimatedGraphics.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams * params, int animSpeed) : SDLGameObject(params), m_animSpeed(animSpeed)
{
}

void AnimatedGraphic::update()
{
  currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::draw()
{
  SDLGameObject::draw();
}

void AnimatedGraphic::clean()
{
  SDLGameObject::clean();
}
