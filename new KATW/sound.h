//==============================================================================
/*
    Classe responsavel por operações de música e sons.

    Declara variáveis globais:
extern Sound sfx;           --> Utilizada para reproduzir músicas e sons.


*/
//==============================================================================

#ifndef _SOUND_H__
#define _SOUND_H__

///==========================================================
/// Musicas e sons carregados
#define MUSIC_LOAD_PIANO (char*)"data/music/bgm/Second try.mp3"
#define MUSIC_LOAD_ORIENTAL (char*)"data/music/bgm/Oriental Style.mp3"
#define MUSIC_LOAD_DAY (char*)"data/music/bgm/New day_8-bit.mp3"
#define MUSIC_LOAD_TRIBAL (char*)"data/music/bgm/Tribal_8-bit.mp3"
#define MUSIC_LOAD_ORCHEST (char*)"data/music/bgm/First try_magix.mp3"
#define MUSIC_LOAD_DERROTA (char*)"data/music/bgm/First Try.mp3"
#define MUSIC_LOAD_VITORIA (char*)"data/music/bgm/Multi-Instruments First.mp3"

enum MusicPlayList { PLAY_PIANO, PLAY_ORIENTAL, PLAY_DAY, PLAY_TRIBAL, PLAY_ORCHEST, PLAY_DERROTA, PLAY_VITORIA};

#define EFFECT_LOAD_SHOT1 (char*)"data/music/sfx/shot1.wav"
#define EFFECT_LOAD_JUMP (char*)"data/music/sfx/jump.wav"

enum EffectPlayList { PLAY_SFX_SHOT1, PLAY_SFX_JUMP};

/// Fim de musicas e sons
///==========================================================



#include "defines.h"
#include <vector>

#include <SDL/SDL_mixer.h>

class Sound
{
    private:
        static Sound *instance;
        Sound(){}

    public:
        ~Sound(); //Destructor
        static Sound& getInstance();

        bool init(); //Inicia modulo de musica e sons
        void closeSound();

        void unloadMusic();
        void unloadSfx();

    public:

        void loadAllSounds();
        void loadMusic(char* filename);
        void loadSfxWAV(char* filename);

        void playMusic(MusicPlayList ID);
        int  playSfx(EffectPlayList ID);

        void stopMusic();
        void stopSfx(int ID = -1);

    private:
    //Lista de músicas e sound effects carregados
        std::vector<Mix_Music*> music_list;
        std::vector<Mix_Chunk*> sfx_list;
};

//variavel global
extern Sound sfx;

#endif



