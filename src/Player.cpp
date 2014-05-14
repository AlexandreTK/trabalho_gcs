#include "Player.h"

/*
 * Implementation by inheritance of GameObject
 */
Player::Player(const LoaderParams * params):SDLGameObject(params)
{

}

/*
 * Implementation by inheritance of GameObject
 */
void Player::draw()
{
  SDLGameObject::draw();
}

/*
 * Update the player's X position
 */
void Player::update()
{
  this->x -= 1;
  this->currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Player::clean()
{
}
