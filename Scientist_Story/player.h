#pragma once

#include "personagem.h"
#include "inputmanager.h"
#include "tiro.h"
#include "teleporte.h"
typedef enum eEnergyType
{    // Adiciona com | e testa com &
    ENERGY_TYPE_FOGO     = 0,
    ENERGY_TYPE_TERRA    = 1,
    ENERGY_TYPE_AGUA     = 2,
    ENERGY_TYPE_AR       = 3,
}EnergyType;
class Player : public Personagem {

    public:
        static Player PlayerControl;

        Player();
        Player(float x, float y);

        void addEnergy(int type, int quantidade);

        //======Arruma erro de ponteiro no linux=====/
        void removeLifeBarLists(){
            lifeBar.removeFromDrawList();
            lifeBar.removeFromLoopList();
        }
        void addLifeBarLists(){
            lifeBar.addLists();
        }

        //======Arruma erro de ponteiro no linux=====/

        virtual void update(unsigned int dt);
        virtual void executaColisao();
        void handle_events();

        void resetPlayer();
    public:
        int getFogo();
        int getAgua();
        int getAr();
        int getTerra();

        int getFogoMax();
        int getAguaMax();
        int getArMax();
        int getTerraMax();


        void setFogo(int fire);
        void setAgua(int water);
        void setAr(int air);
        void setTerra(int earth);

        void setFogoMax(int firemax);
        void setAguaMax(int aguamax);
        void setArMax(int armax);
        void setTerraMax(int terramax);

    protected:
        void handle_tiros();
        void checkTeleports();

        Timer tiroTimerRandom;
        Timer tiroTimerTodos;
        Timer txtTimer;

        int fogo, agua, terra, ar;
        int fogoMax, aguaMax, terraMax, arMax;

    public:
        bool canShot;
        Sprite* spr_tiroComum;
        Sprite* spr_tiroTerra;
        Sprite* spr_tiroAr;
        Sprite* spr_tiroFogo;
};
