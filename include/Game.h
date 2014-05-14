#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "TextureManager.h"
#include "InputHandler.h"

class Game
{
  public:
    Game();
    ~Game();

    bool init(const char * title, int x, int y, int w, int h, int flags);
    bool levelFinished();
    int nextLevel();
    void shutdown();
    void updateTimeStep();
    void input();
    void ia();
    void physics();
    void event();
    void update();
    void drawLogos();
    void draw();
    void setLevel(int inputLevel);
    int getLevel();
    bool getRunning();

  private:
    int level;
    SDL_Window * window;
    SDL_Renderer * renderer;
    bool running;
};

#endif
