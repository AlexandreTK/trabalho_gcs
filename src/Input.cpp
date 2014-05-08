#include "Input.h"
#include <vector>

using std::cout;
using std::endl;

 void Input::initializeJoysticks()
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

 			if (SDL_JoystickOpened(i) == 1)
 			{
 				joysticks.push_back(joy);
 			}
 			else
 			{
 				cout << SDL_GetError(); << endl;
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