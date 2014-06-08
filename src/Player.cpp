#include "Player.h"
#include <iostream>
#include "InputHandler.h"

using std::cout;
/*
 * Implementation by inheritance of GameObject
 */
Player::Player():SDLGameObject()
{
  currentRow = 1;
  flip = SDL_FLIP_NONE;
}


void Player::load(const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
}

/*
 * Implementation by inheritance of GameObject
 */
void Player::draw()
{
  SDLGameObject::draw();
  currentRow = 1;
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

	currentFrame = int(((SDL_GetTicks() / 100) % 8));

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
                        flip = SDL_FLIP_NONE;
                        currentRow = 1;
		}

		if (TheInputHandler::Instance()->getButtonState(0, 7))
		{
			m_velocity.setX(-5);
                        flip = SDL_FLIP_HORIZONTAL;
                        currentRow = 1;
		}

		if (TheInputHandler::Instance()->getButtonState(0, 4))
		{
			m_velocity.setY(-5);
                        currentRow = 1;
		}

		if (TheInputHandler::Instance()->getButtonState(0, 6))
		{
			m_velocity.setY(5);
                        currentRow = 1;
		}
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
	{
		m_velocity.setX(3);
                flip = SDL_FLIP_NONE;
                currentRow = 2;
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
	{
		m_velocity.setX(-3);
                flip = SDL_FLIP_HORIZONTAL;
                currentRow = 2;
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
	{
		m_velocity.setY(-3);
                currentRow = 4;
	}

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
	{
		m_velocity.setY(3);
                currentRow = 3;
	}

        if(m_position.getX() <= 0)
        {
          m_position.setX(0);
        }
        if(m_position.getY() >= 600-119-64)
        {
          m_position.setY(600-119-64);
        }
}
