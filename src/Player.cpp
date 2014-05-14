#include "Player.h"

/*
 * Implementation by inheritance of GameObject
 */
void Player::load(int x, int y, int w, int h, string textureID)
{
  GameObject::load(x, y, w, h, textureID);
}

/*
 * Implementation by inheritance of GameObject
 */
void Player::draw(SDL_Renderer * renderer)
{
  GameObject::draw(renderer);
}

/*
 * Update the player's X position
 */
void Player::update()
{
  this->x -= 1;
}
