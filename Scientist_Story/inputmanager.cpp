#include "inputmanager.h"


InputManager* InputManager::instance;

InputManager* InputManager::getInstance()
{
    if (!instance)
    {
        instance = new InputManager();
    }

    return instance;
};

InputManager::InputManager(){

    for(int i = 0; i < N_KEYS; i++) {
        keyDown[i] = false;
        keyUp[i] = false;
    }
    for (int i = 0; i < N_MOUSE_BUTTONS; i++){
        mouseDown[i] = false;
        mouseUp[i] = false;
    }

    teclado = SDL_GetKeyState(NULL);
    mouse = SDL_GetMouseState(NULL,NULL);
    quitGame = false;
}

void InputManager::Update()
{
    for(int i = 0; i < N_KEYS; i++) {
        keyDown[i] = false;
        keyUp[i] = false;
    }
    for (int i = 0; i < N_MOUSE_BUTTONS; i++){
        mouseDown[i] = false;
        mouseUp[i] = false;
    }
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        mouse = SDL_GetMouseState(NULL,NULL);
        teclado = SDL_GetKeyState(NULL);
        switch (event.type) {
        case SDL_KEYDOWN:
            keyDown[event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            keyUp[event.key.keysym.sym] = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouseDown[event.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseUp[event.button.button] = true;
            break;
        case SDL_MOUSEMOTION:
            mouseX = event.button.x;
            mouseY = event.button.y;
            mouse = event.button.state;
            break;
        case SDL_QUIT:
            quitGame = true;
            break;
        default:;
        }
    }
}
bool InputManager::isKeyDown(int key){
    if(key == -1)
    {
        for(int i = 0; i < N_KEYS;i++) {
            if(keyDown[i])
                return true;
        }
        return false;
    }
    return keyDown[key];

}
bool InputManager::isKeyUp(int key){
    if(key == -1)
    {
        for(int i = 0; i < N_KEYS;i++) {
            if(keyUp[i])
                return true;
        }
        return false;
    }

    return keyUp[key];
}
bool InputManager::isKeyPressed(int key){
    if(key == -1)
    {
        for(int i = 0; i < N_KEYS;i++) {
            if(teclado[i])
                return true;
        }
        return false;
    }
    return teclado[key];
}
bool InputManager::isMouseDown(int button){
    return mouseDown[button];
}
bool InputManager::isMouseUp(int button){
    return mouseUp[button];
}
//Use 1 para esquerdo, 2 meio e 3 direito
bool InputManager::isMousePressed(int button){
    return mouse&SDL_BUTTON(button);
}
int InputManager::mousePosX(){
    return mouseX;
}
int InputManager::mousePosY(){
    return mouseY;
}
bool InputManager::isMouseInside(SDL_Rect* rect){
    if (mouseX> rect->x && (mouseX < (rect->x+rect->w)) )
        if (mouseY > rect->y && (mouseY < (rect->y+rect->h)) )
            return true;
    return false;
}
bool InputManager::QuitGame(){
    return quitGame;
}



