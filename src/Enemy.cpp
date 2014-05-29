#include "Enemy.h"

Enemy::Enemy(const LoaderParams * params):SDLGameObject(params)
{
  flip = SDL_FLIP_HORIZONTAL;
}

void Enemy::draw()
{
  SDLGameObject::draw();
}

void Enemy::update()
{
  m_position.setX(m_position.getX() - 0.2);
  m_position.setY(m_position.getY() + 0);
  this->currentFrame = int(((SDL_GetTicks() / 100) % 1));
  if(m_position.getX() <= 0)
  {
    m_position.setX(0);
  }
}

void Enemy::clean()
{
}
