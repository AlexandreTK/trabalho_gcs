#include "presentationState.h"


void PresentationState::load(int stack)
{
    background = new Sprite("data/img/Village.jpg");
    story1 = new Sprite("data/img/Story1.jpg");
    story2 = new Sprite("data/img/Story2.jpg");

    anim.setSprite(background);
    anim.addWaiting(1000);
    sub_state = 0;
}
int PresentationState::unload()
{
    delete background;
    delete story1;
    delete story2;

    return 0;

}
StateType PresentationState::update(unsigned int dt)
{
    if (InputManager::getInstance()->isKeyDown() )
    {
        return GST_GAME;
    }
    anim.update(dt);

    switch(sub_state)
    {
        case 0:
            sub_state = 1;
            break;
        case 1: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(story1);
                anim.setPos(128,24);
                anim.addWaiting(2000);
                anim.addMoveToXY(-200,24, 350);
                anim.addWaiting(800);
                anim.addMoveToXY(88,-191, 450);
                anim.addWaiting(1500);
                anim.addMoveToXY(-259,-191, 400);
                anim.addWaiting(1000);
                sub_state++;
            }
            break;
        case 2: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(story2);
                anim.setPos(100,15);
                anim.addWaiting(2000);
                anim.addMoveToXY(-234,15, 350);
                anim.addWaiting(2000);
                anim.addMoveToXY(95,-174, 450);
                anim.addWaiting(1500);
                anim.addMoveToXY(-140,-174, 400);
                anim.addWaiting(1500);
                anim.addMoveToXY(-317,-174, 300);
                anim.addWaiting(3000);
                sub_state++;
            }
            break;
        case 3:
            if(anim.isReady())
                return GST_GAME; //Retorna avisando para mudar o estado do jogo
            break;
    }

    return GST_NONE;


}

void PresentationState::render()
{
    anim.render();
}

