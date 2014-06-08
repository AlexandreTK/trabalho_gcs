#pragma once


#define N_KEYS 512
#define N_MOUSE_BUTTONS 3

#include <SDL.h>

class InputManager {
    private:
        static InputManager *instance;


        Uint8 mouse, *teclado;
        bool keyDown[N_KEYS], keyUp[N_KEYS];
        bool quitGame;
        Uint8 mouseDown[N_MOUSE_BUTTONS], mouseUp[N_MOUSE_BUTTONS];
        int mouseX, mouseY;

        InputManager();
    public:
        static InputManager* getInstance();
        void Update();
        bool isKeyDown(int key = -1);
        bool isKeyUp(int key = -1);
        bool isKeyPressed(int key = -1);
        bool isMouseDown(int button);
        bool isMouseUp(int button);
        bool isMousePressed(int button);
        int mousePosX();
        int mousePosY();
        bool isMouseInside(SDL_Rect* rect);
        bool QuitGame();
};


