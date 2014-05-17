#include "Enemy.h"

Enemy::Enemy(const LoaderParams * params):SDLGameObject(params)
{

}

void Enemy::draw(SDL_RendererFlip flags)
{
  SDLGameObject::draw(SDL_FLIP_HORIZONTAL);
}

void Enemy::update()
{
  m_position.setX(m_position.getX() - 0.2);
  m_position.setY(m_position.getY() + 0);
  this->currentFrame = int(((SDL_GetTicks() / 100) % 1));
}

void Enemy::clean()
{
}
