#include "InputHandler.h"
#include <vector>
#include <iostream>
#include "Game.h"

using std::cout;
using std::endl;
using std::make_pair;

InputHandler* InputHandler::inputInstance = NULL;

InputHandler::InputHandler()
{
	initializeJoysticks();
}

 void InputHandler::initializeJoysticks()
 {
 	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
 	{
 		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
 	}

 	if (SDL_NumJoysticks() > 0)
 	{
 		for (int i = 0; i < SDL_NumJoysticks(); i++)
 		{
 			SDL_Joystick* joy = SDL_JoystickOpen(i);

 			if (joy)
 			{
 				joysticks.push_back(joy);
 				joystickValues.push_back(make_pair(new Vector2D(0,0), new Vector2D(0,0)));//Adds a pair
 				vector<bool> tempButtons;

 				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
 				{
 					tempButtons.push_back(false);
 				}

 				buttonStates.push_back(tempButtons);
 			}
 			else
 			{
 				cout << SDL_GetError() << endl;
 			}
 		}
 		SDL_JoystickEventState(SDL_ENABLE);
 		numberJoysticks = true;

 		cout << "Initialized" << joysticks.size() << "joystick(s)" << endl;
 	}
 	else
 	{
 		numberJoysticks = false;
 	}
 }

 void InputHandler::clean()
 {
 	if (numberJoysticks)
 	{
 		for (int i = 0; i < SDL_NumJoysticks(); i++)
 		{
 			SDL_JoystickClose(joysticks[i]);
 		}
 	}
 }

void InputHandler::onJoystickAxisMove(SDL_Event &event)
{
	if (event.type == SDL_JOYAXISMOTION)
	{
		int whichOne = event.jaxis.which;
		//left stick move left or right
		if (event.jaxis.value == 0)
		{
			if (event.jaxis.value > joystickDeadZone)
			{
				joystickValues[whichOne].first->setX(1);
			}
			else if (event.jaxis.value < -joystickDeadZone)
			{
				joystickValues[whichOne].first->setX(-1);
			}
			else
			{
				joystickValues[whichOne].first->setX(0);
			}
		}

		//left stick move up or down.
		if (event.jaxis.value == 1)
		{
			if (event.jaxis.value > joystickDeadZone)
			{
				joystickValues[whichOne].first->setY(1);
			}
			else if (event.jaxis.value < -joystickDeadZone)
			{
				joystickValues[whichOne].first->setY(-1);
			}
			else
			{
				joystickValues[whichOne].first->setY(0);
			}
		}

		//Right stick move left or right
		if (event.jaxis.value == 3)
		{
			if (event.jaxis.value > joystickDeadZone)
			{
				joystickValues[whichOne].second->setX(1);
			}
			else if (event.jaxis.value < -joystickDeadZone)
			{
				joystickValues[whichOne].second->setX(-1);
			}
			else
			{
				joystickValues[whichOne].second->setX(0);
			}
		}
			//Right stick move left or right
		if (event.jaxis.value == 4)
		{
			if (event.jaxis.value > joystickDeadZone)
			{
				joystickValues[whichOne].second->setY(1);
			}
			else if (event.jaxis.value < -joystickDeadZone)
			{
				joystickValues[whichOne].second->setY(-1);
			}
			else
			{
				joystickValues[whichOne].second->setY(0);
			}
		}
	}
}

void InputHandler::onJoystickButtonDown(SDL_Event &event)
{
	if (event.type == SDL_JOYBUTTONDOWN)
		{
			int whichOne = event.jaxis.which;

			buttonStates[whichOne][event.jbutton.button] = true;
		}
}

void InputHandler::onJoystickButtonUp(SDL_Event &event)
{
	if (event.type == SDL_JOYBUTTONUP)
		{
			int whichOne = event.jaxis.which;

			buttonStates[whichOne][event.jbutton.button] = false;
		}
}

void InputHandler::onKeyDown(SDL_Event &event)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
	{
		TheGame::Instance()->finishGame();
	}
}

void InputHandler::onKeyUp(SDL_Event &)
{

}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	keystate = SDL_GetKeyboardState(0);
	if (keystate != 0)
	{
		if (keystate[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
return false;
}

void InputHandler::handle(SDL_Event &event)
{
	switch(event.type)
		{
			case SDL_QUIT:
				TheGame::Instance()->finishGame();
				break;

			case SDL_JOYAXISMOTION:
				onJoystickAxisMove(event);
				break;

			case SDL_JOYBUTTONDOWN:
				onJoystickButtonDown(event);
				break;

			case SDL_JOYBUTTONUP:
				onJoystickButtonUp(event);
				break;

			case SDL_KEYDOWN:
				onKeyDown(event);
				break;

			case SDL_KEYUP:
				onKeyUp(event);
				break;

			default:
				break;
		}		
} 

int InputHandler::xValue(int joy, int stick)
{
	if (joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return joystickValues[joy].first->getX();
		}
		else if (stick == 2)
		{
			return joystickValues[joy].second->getX();
		}
	}
return 0;
}

int InputHandler::yValue(int joy, int stick)
{
	if (joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return joystickValues[joy].first->getY();
		}
		else if (stick == 2)
		{
			return joystickValues[joy].second->getY();
		}
	}
return 0;	
}

