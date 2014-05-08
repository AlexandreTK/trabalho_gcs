#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <SDL.h>

using std::vector;

/*
*Creates the class to handdle the input.
*/
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

	static InputHandler* inputInstance;
};
typedef InputHandler TheInputhandler;

#endif