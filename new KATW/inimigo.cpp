#include "inimigo.h"

InimigoBase::InimigoBase() : Personagem::Personagem()
{
    srand(time(NULL));

    walking_aceleration = 32;
    stop_aceleration = 32;

    atk = 20;

    HP = HPMax = 30;
    typeInimigo = 0;

    flags |= ENTIDADE_FLAG_INIMIGO;

    //jump_speed = 300;
    jump_speed = 350;

    for(int i = 0; i < TIMERS_N; i++)
        timer[i].stop();
    for(int i = 0; i < VAR_BOOL_N; i++)
        var[i] = false;
}
void InimigoBase::update(unsigned int dt){
    if(dead == false){
        onAI();
    }
    if(dead == true){
        an.update(dt);
    }
    hitWall = false;
    Personagem::update(dt);
}
void InimigoBase::render(){
    if(dead == true){
        an.render(pos.x - Camera::CameraControl.getX(), pos.y - Camera::CameraControl.getY());
    }
    Personagem::render();

}
void InimigoBase::onDead()
{
    if(dead == false){
        //Menos 5 em y para diferenciar dano final
        TextSplash* t = new TextSplash(pos.x, pos.y-10, 0,0,80, "I'm Dead x.x!!!");
        t->addLists();
        int anFrame = an.getFrameX();
        if(anFrame == 0 || anFrame == 4 || anFrame == 5 )
            an.setFrames(2, 12, 100, true);
        else
            an.setFrames(3, 12, 100, true);
        an.continueAnimation(0);
        dead = true;
    }


    if(an.isReady())
    {
        //AnimationSplash(Animation anim, float x, float y, int loop = 1);  sprite morrendo.

        int type =  (rand()%5); //gera 0-1
        float chance = (rand()%10001);//gera 0-10001 e divide por 10001... 0.1 = 10%
        chance /=10001;//gera 0-100 e divide por 100... 0.1 = 10%
        int qtd;
        ///CHANCES DE OBTER OS ITENS
        if( chance < 0.1) { //10% de chance de dar item level 3
            qtd = 30+(rand()%20);
        } else if (chance < 0.4) { //40-10 = 30% de chance de dar item lv 2
            qtd = 5+(rand()%25);
        } else { // 100-40 = 60% de item lv 1
            qtd = (rand()%5)+1;
        }
        ItemObject* item = new ItemObject(pos,(ItemType)type,qtd);
        float dir = 80;
        dir += rand()%21; //adiciona 0-20, dir = 80-100;
        item->setDirecao(dir,150);
        item->maxVel.y = g_velMax_y;
        item->addLists();

    ///TESTES QUEST

        if(typeInimigo == 0) { //significa boomer

            Quest::QuestList[1]->addQtd(1);

            for(int i = 0; i < 20; i++)
            {
                float dir=-10;
                int posX = this->pos.x+an.getClip().w/2;
                int posY = this->pos.y;
                Tiro* t = new Tiro();
                t->setSprite( SpriteManager::SpriteControl.getSprite(SPRITE_FOGO), 20,10);
                int random = (rand()%41)-20;// 0-9
                if(i < 4) {
                    posX += 20;
                    dir += i*10+random;
                    t->setFrames(ACT_RIGHT, 1);
                }
                else{
                    dir += i*10+random;
                    posX -=15;
                    t->setFrames(ACT_LEFT, 1);
                }
                t->setDirecao(dir,450);
                t->setDamage(15);
                t->setTempo(500);
                t->setPos(posX, posY);
                t->addToTiroList();
                t->flags = ENTIDADE_FLAG_TIRO_INIMIGO|ENTIDADE_FLAG_MAP_ONLY_COLIDE;
            }
        }else{
            Quest::QuestList[0]->addQtd(1);
        }

        removeFromEntidadeList();
        delete (this);
    }

}


void InimigoBase::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        Personagem* colidido = (Personagem*)entidadeColidida[i];
        if(colidido->isFlag(ENTIDADE_FLAG_INIMIGO)){
            if(colVel.y > 0) //Se estava indo para baixo quando colidiu.
                this->extVel.x = entidadeColidida[i]->vel.x;
        }
        if(colidido->isFlag(ENTIDADE_FLAG_PLAYER) == true){
            if(typeInimigo == 0) {//se boomer, ele explode
                this->HP = 0;
                break;
            }

            colidido->takeDamage(atk);
            if(colidido->isInvencible() == false){
                colidido->vel.x > 0 ? colidido->vel.x = -300 : colidido->vel.x = 300;
                colidido->vel.y = -200;
                colidido->setThrowed(true);
                colidido->setInvencible(1000);
            }
        }
    }

    entidadeColidida.clear();
}
//Verica que ação deve ser executado pelo inimigo.
void InimigoBase::onAI(){
    if( canSee(&Player::PlayerControl, 500) ){

        if(hitWall){
            jump(true);
        }

        //Quando finalizar a animação, muda para corrida, e liga novo timer.
        if(an.isReady() && var[0] == true){
            an.setFrames(an.getFrameX()+1,8,an.getDelay(),false);
            lastMaxVel.x = maxVel.x;
            maxVel.x = maxVel.x*6;
            timer[0].start();

            if(an.getFrameX() == 5) {
                actionMovement = ACT_RIGHT;
            } else {
                actionMovement = ACT_LEFT;
            }
        }

        //Faz o movimento rage parar -- SLIME
        if(timer[0].getTime() > 1200){
                timer[0].stop();
                var[0] = false;
                moveStop();
                int frameX = 1;
                if(an.getFrameX() == 5) {
                    frameX = 0;
                }
                an.setFrames(frameX,6,an.getDelay()+150, false);
                maxVel.x = lastMaxVel.x;
                //Espera parado por um tempo
                timer[1].start();
        }
        //Faz esperar parado por algum tempo
        if(timer[1].getTime() > 1500){
            timer[1].stop();
            timer[2].start();
        }
        if( timer[1].is_started() ) {
            moveStop();
            return;
        }
        //Espera a MAIS para o proximo rage
        if(timer[2].getTime() > 3500){
            timer[2].stop();
        }

        ///SLIME RAGE BEGIN
        if( canSee(&Player::PlayerControl, 120) && typeInimigo != 0 && timer[2].is_started() == false) {

            //Inicia a execução de RAGE SLIME
            if( var[0] == false){
                var[0] = true;
                if(actionMovement == ACT_RIGHT)
                    an.setFrames(4,10,an.getDelay()-150, true);
                else
                    an.setFrames(6,10,an.getDelay()-150, true);
                moveStop();
            }

        }

        if(var[0] == true) return;

        if(Player::PlayerControl.pos.x > this->pos.x){
            moveRight();
        }
        if(Player::PlayerControl.pos.x < this->pos.x){
            moveLeft();
        }


    } else { // Se não puder ver player na tela, para
        moveStop();
    }
}

void InimigoBase::onNotValidPosition(bool isX){
    if(isX) {
        vel.x = 0;
        //Se não tiver colidido com entidades, bateu na parede
        if(entidadeColidida.empty())
            hitWall = true;
    }
    else
        vel.y = 0;
}
