#pragma once

#include "state.h"
#include "map.h"
#include "player.h"
#include "tiro.h"
#include "inimigo.h"
#include "itemobj.h"
#include "interfaceMenu.h"
#include "quest.h"
#include "npc.h"
#include "spriteManager.h"
#include "player.h"

#include "save.h"

class StateGame : public State
{
    private:
        Sprite* sp_player;
        Sprite* sp_bg;
        Sprite* sp_item;
        Sprite* sp_bar;

        NPC* npc;

    public:
        void load(int stack = 0);
        int unload();
        void destroyObjetos();
        eStateType update(unsigned int dt);
        void render();
        int stack;

};

