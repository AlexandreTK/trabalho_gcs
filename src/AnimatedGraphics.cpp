#include "AnimatedGraphics.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams * params, int animSpeed) : SDLGameObject(), m_animSpeed(animSpeed)
{
}

void AnimatedGraphic::load(const LoaderParams * params)
{
  SDLGameObject::load(params);
  m_animSpeed = params->getAnimSpeed();
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
