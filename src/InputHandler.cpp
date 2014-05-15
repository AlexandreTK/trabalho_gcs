#include "InputHandler.h"
#include <vector>
#include <iostream>
#include "Game.h"

using std::cout;
using std::endl;
using std::make_pair;

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

void InputHandler::update()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			//TheGame::Instance()->~Game();
		}

		if (event.type == SDL_JOYAXISMOTION)
		{
			int whichOne = event.jaxis.which;
			//left stick move left or right
			if (event.jaxis.value == 0)
			{
				if (event.jaxis.value > joystickDeadZone)
				{
					joystickValues[whichOne].first->setX(1);
				}else if (event.jaxis.value < -joystickDeadZone)
				{
					joystickValues[whichOne].first->setX(-1);
				}else
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
				}else if (event.jaxis.value < -joystickDeadZone)
				{
					joystickValues[whichOne].first->setY(-1);
				}else
				{
					joystickValues[whichOne].first->setY(0);
				}
			}
		}
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

