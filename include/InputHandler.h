#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>
#include <SDL.h>

using std::vector;
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
	bool joysticksInitialized () {
		return numberJoysticks;
	}

private:
	InputHandler();
	~InputHandler(){}

	vector<SDL_Joystick*> joysticks;
	bool numberJoysticks;
	void initializeJoysticks();

	static InputHandler* inputInstance;
};
typedef InputHandler TheInputHandler;

#endif
