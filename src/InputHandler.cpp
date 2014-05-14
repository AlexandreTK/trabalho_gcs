#include "InputHandler.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

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
 		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
 		{
 			SDL_JoystickClose(joysticks[i]);
 		}
 	}
 }

void InputHandler::update()
{
	/*SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			//Game::Instance()->quit();
		}
	}*/
} 
