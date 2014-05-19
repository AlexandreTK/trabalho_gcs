#include "Player.h"
#include <iostream>
#include "InputHandler.h"

using std::cout;
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

	currentFrame = int(((SDL_GetTicks() / 100) % 4));

	m_acceleration.setX(0);

	SDLGameObject::update();
}

void Player::clean()
{
}
//Sets the input of the player via the velocity.
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
			m_velocity.setY(1 * TheInputHandler::Instance()->yValue(0,2));
		}

		if (TheInputHandler::Instance()->xValue(0, 2) > 0 || TheInputHandler::Instance()->xValue(0, 2) < 0)
		{
			m_velocity.setX(1 * TheInputHandler::Instance()->xValue(0,2));
		}

		if (TheInputHandler::Instance()->yValue(0, 2) > 0 || TheInputHandler::Instance()->yValue(0, 2) < 0)
		{
			m_velocity.setY(1 * TheInputHandler::Instance()->yValue(0,2));
		}

		if (TheInputHandler::Instance()->getButtonState(0, 5))
		{
			m_velocity.setX(5);
		}

		if (TheInputHandler::Instance()->getButtonState(0, 7))
		{
			m_velocity.setX(-5);
		}

		if (TheInputHandler::Instance()->getButtonState(0, 4))
		{
			m_velocity.setY(-5);
		}

		if (TheInputHandler::Instance()->getButtonState(0, 6))
		{
			m_velocity.setY(5);
		}
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(2);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-2);
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		m_velocity.setY(-2);

	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_velocity.setY(2);
	}
}
