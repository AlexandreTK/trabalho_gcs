#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>
#include <SDL.h>
#include "Vector2D.h"

using std::vector;
using std::pair;

class InputHandler
{
public:
	
	static InputHandler* Instance ()
	{
		if (inputInstance == 0)
		{
			inputInstance = new InputHandler();
		}

		return inputInstance;
	}

	void update();
	void clean();
	void initializeJoysticks();
	bool joysticksInitialized () {
		return numberJoysticks;
	}

private:
	InputHandler();
	~InputHandler(){}

	vector<SDL_Joystick*> joysticks;
	bool numberJoysticks;
	vector<pair<Vector2D*, Vector2D*> > joystickValues;	
	int xValue(int joy, int stick);
	int yValue (int joy, int stick);

	static InputHandler* inputInstance;
};
typedef InputHandler TheInputHandler;

#endif
