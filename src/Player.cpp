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
  /*this->x -= 1;
  this->currentFrame = int(((SDL_GetTicks() / 100) % 6));*/
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput(); // add our function

	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

	SDLGameObject::update();
}

void Player::clean()
{
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->joysticksInitialized())
	{
		if (TheInputHandler::Instance()->xValue(0, 1) > 0 || TheInputHandler::Instance()->xValue(0, 1) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xValue(0,1));
		}

		if (TheInputHandler::Instance()->yValue(0, 1) > 0 || TheInputHandler::Instance()->yValue(0, 1) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yValue(0,1));
		}

		if (TheInputHandler::Instance()->xValue(0, 2) > 0 || TheInputHandler::Instance()->xValue(0, 2) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xValue(0,2));
		}

		if (TheInputHandler::Instance()->yValue(0, 2) > 0 || TheInputHandler::Instance()->yValue(0, 2) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yValue(0,2));
		}
	}
}
