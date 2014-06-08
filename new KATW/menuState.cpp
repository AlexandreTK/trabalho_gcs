#include "menuState.h"

void StateMenu::load(int stack)
{
    background = new Sprite();

    background->load("data/img/title.png");
//
    btn_start = new Button();
    btn_load = new Button();
    btn_exit = new Button();

    btn_start->load_image((char*)"data/btn/NewGameKays.png", 2);
    btn_load->load_image((char*)"data/btn/LoadGameKays.png", 2);
    btn_exit->load_image((char*)"data/btn/ExitKays.png", 2);

    btn_start->setXY(279, 303);
    btn_load->setXY(279, 376);
    btn_exit->setXY(279, 452);

    BtnList.push_back(btn_start);
    BtnList.push_back(btn_load);
    BtnList.push_back(btn_exit);

    SDLBase::sfx.playMusic(PLAY_PIANO);
//
    stack = 0;

}

int StateMenu::unload()
{
    delete background;
//
    for(unsigned int i = 0; i < BtnList.size();i++)
        delete BtnList[i];

    BtnList.clear();

    SDLBase::sfx.stopMusic();
//
    return stack;
}

eStateType StateMenu::update(unsigned int dt)
{
//
    for(unsigned int i = 0; i < BtnList.size();i++)
    {
        BtnList[i]->handleEvents();
    }

    if (btn_start->isClick())
        return GST_INTRO;
    else
    if (btn_load->isClick()){
        stack = 1;
        return GST_GAME;
    }
    else
    if (btn_exit->isClick())
        return GST_QUIT;
//
    return GST_NONE;
}
void StateMenu::render()
{
    background->render(0,0);
//
    for(unsigned int i = 0; i < BtnList.size();i++)
    {
        BtnList[i]->render();
    }//
}

