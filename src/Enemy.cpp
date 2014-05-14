#include "Enemy.h"

void Enemy::update()
{
  this->y += 1;
  this->x += 1;
  this->currentFrame = int(((SDL_GetTicks() / 100) %6));
}
