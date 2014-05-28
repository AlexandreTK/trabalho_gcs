#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <vector>
#include <SDL.h>
#include "Vector2D.h"

using std::vector;
using std::pair;

class InputHandler
{
	static InputHandler* inputInstance;
public:
	
	static InputHandler* Instance ()
	{
		if (inputInstance == 0)
		{
			inputInstance = new InputHandler();
		}

		return inputInstance;
	}

	void handle(SDL_Event &event);
	void clean();
	void initializeJoysticks();
	bool joysticksInitialized () {
		return numberJoysticks;
	}
	bool getButtonState(int joy, int buttonNumber)
	{
		return buttonStates[joy] [buttonNumber];
	}
	bool isKeyDown(SDL_Scancode key);

	int xValue (int joy, int stick);
	int yValue (int joy, int stick);


private:
	InputHandler();
	~InputHandler(){}

	vector<SDL_Joystick*> joysticks;
	vector<pair<Vector2D*, Vector2D*> > joystickValues;	
	vector< vector<bool> > buttonStates;

	bool numberJoysticks;

	int buttonNumber;

	const Uint8* keystate;

	static const int joystickDeadZone = 10000;

	// private functions to handle different event types
	
	// handle keyboard events
	void onKeyDown(SDL_Event &event);
	void onKeyUp(SDL_Event &event);
	
	// handle joysticks events
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

};
typedef InputHandler TheInputHandler;

#endif
