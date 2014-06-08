#include "player.h"

Player Player::PlayerControl;

Player::Player() : Personagem::Personagem()
{
    HP = 100;
    fogo = agua = terra = ar = 0;
    HPMax = fogoMax = aguaMax = terraMax = arMax = 100;
    flags |= ENTIDADE_FLAG_PLAYER;
    srand(time(NULL));
    tiroTimerRandom.start();
    tiroTimerTodos.start();
    canShot = true;
    txtTimer.start();

    showCollision = false;
}
void Player::resetPlayer(){
    HP = HPMax = 100;
    fogo = agua = terra = ar = 0;
    vel.x = vel.y = acel.x = acel.y;
    actionMovement = ACT_STOPPING;
    tiroTimerRandom.start();
    tiroTimerTodos.start();
    dead = false;
}
Player::Player(float x, float y) : Personagem::Personagem(x,y){
    HP = 100;
    fogo = agua = terra = ar = 0;
    HPMax = fogoMax = aguaMax = terraMax = arMax = 100;
    flags |= ENTIDADE_FLAG_PLAYER;
    srand(time(NULL));
    tiroTimerRandom.start();
    tiroTimerTodos.start();
    canShot = true;
    txtTimer.start();
}

void Player::update(unsigned int dt){
    Personagem::update(dt);
    checkTeleports();
}

void Player::addEnergy(int type, int quantidade)
{
    int r=0,g=0,b=0;
    switch(type)
    {
        case 0:
            fogo += quantidade;
            if(fogo > fogoMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (fogo-fogoMax);
                fogo = fogoMax;
            }
            r = 200;g=50;b=25;
            break;
        case 1:
            terra += quantidade;
            if(terra > terraMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (terra-terraMax);
                terra = terraMax;
            }
            r = 50;g = 255;b = 50;
            break;
        case 2:
            agua += quantidade;
            if(agua > aguaMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (agua-aguaMax);
                agua = aguaMax;
            }
            b = 255;
            break;
        case 3:
            ar += quantidade;
            if(ar > arMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (ar-arMax);
                ar = arMax;
            }
            r= 255;b = 255; g = 255;
            break;
        case 4:
            HP += quantidade;
            if(HP > fogoMax){
                //seta quantidade como o quanto recuperou
                quantidade -= (HP-HPMax);
                HP = HPMax;
            }
            r = 255;g=0;b=0;
            break;
    }

    TextSplash* t = new TextSplash(pos.x, pos.y, r, g,b, "+%d!", quantidade );
    t->addLists();
    ///TESTES
    Quest::QuestList[2]->addQtd(1);
}

void Player::handle_events()
{
    if(InputManager::getInstance()->isKeyPressed(SDLK_RIGHT) )
        moveRight();
    else
    if(InputManager::getInstance()->isKeyPressed(SDLK_LEFT) )
        moveLeft();
    else{
             actionMovement = ACT_STOPPING;
        }


    //Verifica tiros
    handle_tiros();


    ///JUMP
    if(InputManager::getInstance()->isKeyDown(SDLK_SPACE) || InputManager::getInstance()->isKeyDown(SDLK_z) ) {
        if(canDoJump) SDLBase::sfx.playSfx(PLAY_SFX_JUMP);
        jump(true);
    }

   if(InputManager::getInstance()->isKeyPressed(SDLK_SPACE) || InputManager::getInstance()->isKeyPressed(SDLK_z) )
        jump(false);
    else
        jumpTimer.stop();
    ///END JUMP
}

void Player::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        if(colVel.y > 0) //Se estava indo para baixo quando colidiu.
            this->extVel.x = entidadeColidida[i]->vel.x;
    }

    entidadeColidida.clear();
}

// TODO (Gust#1#): Colocar para usar o tiro selecionado, e mudar o sprite do tiro selecionado no InterfaceMenu.
void Player::handle_tiros()
{
    if(canShot == false) return;
//Tiro random, atira mais rapido doq os outros
    if(InputManager::getInstance()->isKeyPressed(SDLK_f)) {
        if(tiroTimerRandom.getTime() > 80)
        {

            tiroTimerTodos.start();
            tiroTimerRandom.start();
            if(ar < 1) {
                if(txtTimer.getTime() < 1000) return; // Se não tiver passado 1sec, ignora texto
                txtTimer.start();

                TextSplash* t = new TextSplash(pos.x, pos.y+12, 100, 0,0, "No ammo!!" );
                t->addLists();
                TextSplash* t2 = new TextSplash(pos.x-5, pos.y, 0, 50,0, "Gasta 1 ar.");
                t2->addLists();
                return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
            }

            ar-= 1;

            float dir=0;
            int posX = this->pos.x;
            int posY = this->pos.y + 9;
            Tiro* t = new Tiro();

            int variacao = rand() % 31;  //vai de 0-30
            t->setSprite(spr_tiroAr, 20,10);
            if(this->an.getFrameX() == ACT_RIGHT) {
                posX += 20;
                dir = variacao-15;
                t->setFrames(ACT_RIGHT, 1);
            }
            else if(this->an.getFrameX() == ACT_LEFT){
                dir = 165+variacao;
                posX -=10;
                t->setFrames(ACT_LEFT, 1);
            }
            t->setDirecao(dir,500);
            t->setDamage(3);
            t->setTempo(500);
            t->setPos(posX, posY);
            t->addToTiroList();
            SDLBase::sfx.playSfx(PLAY_SFX_SHOT1);

        } ///FIM DO TIRO 'S'
        return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
    }
/// Só podem atirar 1 vez a kd 150ms
    if(tiroTimerTodos.getTime() < 150) return; // limita 1 tira para cada 150ms

    //Tiro normal?
    if(InputManager::getInstance()->isKeyDown(SDLK_x)) {
        tiroTimerTodos.start();
        float dir=0;
        int posX = this->pos.x;
        int posY = this->pos.y + 9;
        Tiro* t = new Tiro();
        t->setSprite(spr_tiroComum, 20,10);
        if(this->an.getFrameX() == ACT_RIGHT) {
            posX += 20;
            dir = 0;
            t->setFrames(ACT_RIGHT, 1);
        }
        else if(this->an.getFrameX() == ACT_LEFT){
            dir = 180;
            posX -=10;
            t->setFrames(ACT_LEFT, 1);
        }
        t->setDirecao(dir,300);
        t->setDamage(3);
        t->setTempo(1000);
        t->setPos(posX, posY);
        t->addToTiroList();
        SDLBase::sfx.playSfx(PLAY_SFX_SHOT1);

    }

    //Tiro perfurante/acido
    if(InputManager::getInstance()->isKeyDown(SDLK_d)) {

        tiroTimerTodos.start();
        tiroTimerRandom.start();
        if(agua < 5) {
            if(txtTimer.getTime() < 1000) return; // Se não tiver passado 1sec, ignora texto

            TextSplash* t = new TextSplash(pos.x, pos.y+12, 100, 0,0, "No ammo!!" );
            t->addLists();
            TextSplash* t2 = new TextSplash(pos.x-5, pos.y, 0, 50,0, "Gasta 5 agua.");
            t2->addLists();
            txtTimer.start();
            return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
        }

        agua-= 5;

        float dir=0;
        int posX = this->pos.x;
        int posY = this->pos.y + 9;
        Tiro* t = new Tiro();

        t->setSprite(spr_tiroComum, 20,10);
        if(this->an.getFrameX() == ACT_RIGHT) {
            posX += 20;
            dir = 0;
            t->setFrames(ACT_RIGHT, 1);
        }
        else if(this->an.getFrameX() == ACT_LEFT){
            dir = 180;
            posX -=10;
            t->setFrames(ACT_LEFT, 1);
        }
        t->setDirecao(dir,500);
        t->setDamage(4);
        t->setTempo(500);
        t->setPos(posX, posY);
        t->addToTiroList();
        t->setPiercing(true);
        SDLBase::sfx.playSfx(PLAY_SFX_SHOT1);

        return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
    }

    //Shotgun -> 3 fire
    if(InputManager::getInstance()->isKeyDown(SDLK_a)) {
        tiroTimerTodos.start();

        if(fogo < 3) {
            if(txtTimer.getTime() < 1000) return; // Se não tiver passado 1sec, ignora texto
            txtTimer.start();
            TextSplash* t = new TextSplash(pos.x, pos.y+12, 100, 0,0, "No ammo!!" );
            t->addLists();
            TextSplash* t2 = new TextSplash(pos.x-5, pos.y, 0, 50,0, "Gasta 3 fogo.");
            t2->addLists();
            return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
        }

        fogo-= 3;

        for(int i = 0; i < 5; i++)
        {
            float dir=0;
            int posX = this->pos.x;
            int posY = this->pos.y + 9;
            Tiro* t = new Tiro();
            t->setSprite(spr_tiroFogo, 20,10);
            if(this->an.getFrameX() == ACT_RIGHT) {
                posX += 20;
                dir = i*10-20;
                t->setFrames(ACT_RIGHT, 1);
            }
            else if(this->an.getFrameX() == ACT_LEFT){
                dir = 160+i*10;
                posX -=10;
                t->setFrames(ACT_LEFT, 1);
            }
            t->setDirecao(dir,450);
            t->setDamage(4);
            t->setTempo(500);
            t->setPos(posX, posY);
            t->addToTiroList();
        }

        SDLBase::sfx.playSfx(PLAY_SFX_SHOT1);
        return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.

    }


    //Tiro rasteiro
    if(InputManager::getInstance()->isKeyDown(SDLK_s)) {
        tiroTimerTodos.start();

        tiroTimerTodos.start();
            if(terra < 1) {
                if(txtTimer.getTime() < 1000) return; // Se não tiver passado 1sec, ignora texto
                txtTimer.start();
                TextSplash* t = new TextSplash(pos.x, pos.y+12, 100, 0,0, "No ammo!!" );
                t->addLists();
                TextSplash* t2 = new TextSplash(pos.x-5, pos.y, 0, 50,0, "Gasta 1 terra.");
                t2->addLists();
                return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
            }

            terra-= 1;

        float dir=0;
        int posX = this->pos.x;
        int posY = this->pos.y + 9;
        Tiro* t = new Tiro();
        t->setSprite(spr_tiroTerra, 20,10);
        if(this->an.getFrameX() == ACT_RIGHT) {
            posX += 20;
            dir = -30;
            t->setFrames(ACT_RIGHT, 1);
        }
        else if(this->an.getFrameX() == ACT_LEFT){
            dir = 180+30;
            posX -=10;
            t->setFrames(ACT_LEFT, 1);
        }
        t->setDirecao(dir,300);
        t->setDamage(5);
        t->setTempo(2000);
        t->setPos(posX, posY);
        t->elemento = TIRO_FLAG_TERRA;
        t->addToTiroList();

        SDLBase::sfx.playSfx(PLAY_SFX_SHOT1);
        return; //Só pode utilizar 1 tiro de cada ver, então retorna função e ignora outros.
    }
}

// Verifica se o player colidiu com o teleporte, e muda o mapa------------
void Player::checkTeleports()
{
    for(unsigned int i = 0; i < Teleporte::TeleporteList.size();i++)
    {
        Teleporte::TeleporteList[i]->update(this);
    }
}

int Player::getFogo() { return fogo; }
int Player::getAgua() { return agua; }
int Player::getAr() { return ar; }
int Player::getTerra() { return terra; }

int Player::getFogoMax() { return fogoMax; }
int Player::getAguaMax() { return aguaMax; }
int Player::getArMax() { return arMax; }
int Player::getTerraMax() { return terraMax; }

void Player::setFogo(int fire){fogo = fire;}
void Player::setAgua(int water){agua = water;}
void Player::setAr(int air){ar = air;}
void Player::setTerra(int earth){terra = earth;}

void Player::setFogoMax(int firemax){fogoMax = firemax;}
void Player::setAguaMax(int watermax){aguaMax = watermax;}
void Player::setArMax(int airmax){arMax = airmax;}
void Player::setTerraMax(int earthmax){terraMax = earthmax;}
