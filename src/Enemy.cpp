#include "Enemy.h"

Enemy::Enemy(const LoaderParams * params):SDLGameObject(params)
{

}

void Enemy::draw()
{
  SDLGameObject::draw();
}

void Enemy::update()
{
  this->y += 1;
  this->x += 1;
  this->currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Enemy::clean()
{
}
