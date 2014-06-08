#pragma once

#define N_SPRITES 256

enum {
    SPRITE_BOOMER = 0,
    SPRITE_SLIME_SIMPLE,
    SPRITE_PLAYER,
    SPRITE_SLIME_GOD,
    SPRITE_NPC1, // 4
    SPRITE_NPC2, // 5
    SPRITE_NPC3, // 6
    SPRITE_NPC4, // 7
    SPRITE_CYBORG_SLIME, // 8
    SPRITE_TILESET,
    SPRITE_FOGO,
    SPRITE_AR,
    SPRITE_TIRO,
    SPRITE_TERRA,
    SPRITE_BALL
};


#include "sprite.h"

class SpriteManager{
    public:
        static SpriteManager SpriteControl;
        SpriteManager();

        Sprite* getSprite(int index);
        void loadSprite(const char* filename, int index);
        void deleteSprite(int index);
        void deleteAllSprites();
    private:
        Sprite* vetorSprite[N_SPRITES];

};
