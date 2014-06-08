#include "inimigo.h"


#include <math.h>

InimigoLastBoss::InimigoLastBoss() : InimigoBase::InimigoBase()
{
    srand(time(NULL));

    walking_aceleration = 384;
    stop_aceleration = 704;

    atk = 35;

    HP = HPMax = 200;
    typeInimigo = 0;
    timerTeleporte.start();
    timerAtira.start();

    tiro = new Tiro();
    tiro->flags = ENTIDADE_FLAG_TIRO_INIMIGO ;//| ENTIDADE_FLAG_MAP_ONLY_COLIDE;
    tiro->setDamage(30);
    tiro->setSprite(SpriteManager::SpriteControl.getSprite(SPRITE_BALL), 32,32);
    actionMovement = ACT_NONE;
    actionType = BOSS_WAIT_L;

}

InimigoLastBoss::~InimigoLastBoss(){
    if(tiro) delete tiro;
}
void InimigoLastBoss::update(unsigned int dt){
    if(dead == false){
        onAI();
    }
    if(dead == true){
        an.update(dt);
    }
    Personagem::update(dt);
}
void InimigoLastBoss::render(){
    if(dead == true){
        an.render(pos.x - Camera::CameraControl.getX(), pos.y - Camera::CameraControl.getY());
    }
    Personagem::render();

}
void InimigoLastBoss::onDead()
{
    if(dead == false){
        //Menos 5 em y para diferenciar dano final
        TextSplash* t = new TextSplash(pos.x, pos.y-10, 0,0,80, "I'm Dead x.x!!!");
        t->addLists();

        an.setFrames(an.getFrameX()+2, 12, 100, true);
        dead = true;
    }


    if(an.isReady())
    {
        //AnimationSplash(Animation anim, float x, float y, int loop = 1);  sprite morrendo.

        int type =  (rand()%4); //gera 0-1
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
        Quest::QuestList[4]->addQtd(1);

        removeFromEntidadeList();
        delete (this);
    }

}


void InimigoLastBoss::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        Personagem* colidido = (Personagem*)entidadeColidida[i];
        if ( colidido->flags & ENTIDADE_FLAG_PLAYER){
            colidido->takeDamage(atk);
            if(colidido->isInvencible() == false){
                colidido->vel.x > 0 ? colidido->vel.x = -300 : colidido->vel.x = 300;
                colidido->vel.y = -200;
                colidido->setThrowed(true);
                colidido->setInvencible(500);
            }
        }
    }

    entidadeColidida.clear();
}
//Verica que ação deve ser executado pelo inimigo.
void InimigoLastBoss::onAI(){
    if( canSee(&Player::PlayerControl, 500) ){


        if(actionType == BOSS_WAIT_L && an.getFrameX() != 5) {
            an.setFrames(5,2);
        } else
        if(actionType == BOSS_WAIT_R && an.getFrameX() != 0) {
            an.setFrames(0,2);
        }

    //Inicia animação de teleporte
        if(timerTeleporte.getTime() > 1000){
            actionType = BOSS_TELEPORTE;
            an.setFrames(an.getFrameX()+3,6,150,true);
            an.continueAnimation(0);
            timerTeleporte.stop();
        }
    //Terminou de se desfazer, começa a refazer
        if(actionType == BOSS_TELEPORTE && an.isReady()){
            ///POSICAO
            setInvencible(-1); //invencivel

            bool isValid = false;
            while(isValid == false){
                int rX = ( rand() % Map::MapControl.map_width )-2;
                int rY = 2 + ( rand() % (Map::MapControl.map_height-2) );

                if(isValidTile(Map::MapControl.getTileFromIndex(rX,rY) ) &&
                    Map::MapControl.getTileFromIndex(rX,rY)->tipo != TILE_TIPO_PLATAFORMA  )
                    if(isValidTile(Map::MapControl.getTileFromIndex(rX+1,rY) ) &&
                        Map::MapControl.getTileFromIndex(rX+1,rY)->tipo != TILE_TIPO_PLATAFORMA )
                        if(isValidTile(Map::MapControl.getTileFromIndex(rX+1,rY+1) ) &&
                            Map::MapControl.getTileFromIndex(rX+1,rY+1)->tipo != TILE_TIPO_PLATAFORMA )
                            if(isValidTile(Map::MapControl.getTileFromIndex(rX,rY+1))  &&
                                Map::MapControl.getTileFromIndex(rX,rY+1)->tipo != TILE_TIPO_PLATAFORMA )
                                if(Map::MapControl.getTileFromIndex(rX,rY+2)->tipo == TILE_TIPO_PLATAFORMA  || isValidTile(Map::MapControl.getTileFromIndex(rX,rY+2)) == false  )
                                if(Map::MapControl.getTileFromIndex(rX+1,rY+2)->tipo == TILE_TIPO_PLATAFORMA  || isValidTile(Map::MapControl.getTileFromIndex(rX+1,rY+2)) == false  )
                                if(Player::PlayerControl.isColisaoRetangulo(rX*TILE_SIZE, rY*TILE_SIZE, TILE_SIZE*2, TILE_SIZE*2) == false )
                                {
                                   setPos(rX*TILE_SIZE,rY*TILE_SIZE);
                                   if( canSee(&Player::PlayerControl, 500) )
                                        isValid = true;
                                }





            }

            actionType = BOSS_UN_TELEPORTE;
            an.setFrames(an.getFrameX()+1,6,150,true);
            an.continueAnimation(0);
        }
    //Terminou de teleportar, inicia timer
        if(actionType == BOSS_UN_TELEPORTE && an.isReady()) {
            setInvencible(0); // vencível
            timer[0].start();
            //Vira para player
            if(Player::PlayerControl.pos.x > this->pos.x){
                actionType = BOSS_WAIT_R;
            }
            if(Player::PlayerControl.pos.x < this->pos.x){
                actionType = BOSS_WAIT_L;
            }
        }
    //Esperou, agora charge
        if(timer[0].getTime() > 1000){
            actionType = BOSS_CHARGE;
            an.setFrames(an.getFrameX()+1,14,150,true);
            an.continueAnimation(0);
            timer[0].stop();
            timer[1].start();
            timerAtira.start();
        }
    //Terminou charge, começa ATIRAR
        if(actionType == BOSS_CHARGE && timerAtira.getTime() > 1500){
            timerAtira.start();
            atira();
        }
    //Termina de atirar, descarrega
        if(actionType == BOSS_CHARGE && timer[1].getTime() > 6000){
            actionType = BOSS_UNCHARGE;
            an.setFrames(an.getFrameX()+1,6,150,true);
            an.continueAnimation(0);
            timer[1].stop();
        }
    //Termina de descarregar, espera e teleporta.
        if(actionType == BOSS_UNCHARGE && an.isReady()) {
            timerTeleporte.start();

            //Vira para player
            if(Player::PlayerControl.pos.x > this->pos.x){
                actionType = BOSS_WAIT_R;
            }
            if(Player::PlayerControl.pos.x < this->pos.x){
                actionType = BOSS_WAIT_L;
            }
        }


    } else {
    }
}

void InimigoLastBoss::atira(){


    Tiro* t = new Tiro(*tiro);

    t->setFrames(ACT_RIGHT, 1);
    float dir = atan2(pos.y - Player::PlayerControl.pos.y, Player::PlayerControl.pos.x - pos.x )*180/M_PI;
    t->setDirecao(dir,500);
    t->setTempo(500);
    t->setPos(pos.x+16, pos.y);
    t->addToTiroList();

    timerAtira.start();
}
