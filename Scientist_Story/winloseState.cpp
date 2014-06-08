#include "winloseState.h"

void WinLoseState::load(int stack)
{
    if(stack == -1) //DERROTA
        background = new Sprite((char*)"data/img/Grass Field_1.jpg");
    else //VITORIA
        background = new Sprite((char*)"data/img/Grass FieldText.jpg");

    if(stack == -1)    {
        texto = "DERROTA!! VOCE DROPOU NO CHÃO!!";
        r = g = b = 255;
        offX = -170;

    }
    else{
        texto = "VITORIA, SALVOU A CIDADE!";
        r = g = b = 0;
        offX = -150;
    }

    if(stack == -1) {
        SDLBase::sfx.playMusic(PLAY_DERROTA);
    }else {
        SDLBase::sfx.playMusic(PLAY_VITORIA);
    }
}

int WinLoseState::unload()
{
    delete (background);

    return 0;
}

eStateType WinLoseState::update(unsigned int dt)
{

    if(InputManager::getInstance()->isKeyDown(SDLK_RETURN))
        return GST_MENU;
    if(InputManager::getInstance()->isKeyDown(SDLK_ESCAPE))
        return GST_QUIT;

    return GST_NONE;
}
void WinLoseState::render()
{
    background->render(0,0);

    SDLBase::txt.applyText((SCREEN_WIDTH/2)+offX,
                  (SCREEN_HEIGHT/2)-68, 16,
                            r,g,b, texto.c_str()
                            );
}
