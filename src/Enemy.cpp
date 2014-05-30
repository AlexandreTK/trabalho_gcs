#include "Enemy.h"

Enemy::Enemy():SDLGameObject()
{
  flip = SDL_FLIP_HORIZONTAL;
}

void Enemy::load(const LoaderParams * params)
{
  SDLGameObject::load(params);
  m_velocity.setX(2);
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
