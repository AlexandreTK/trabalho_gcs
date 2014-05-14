#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include "InputHandler.h"

#include <SDL.h>
#include <vector>

class Game
{
  public:
    ~Game();

    static Game * Instance()
    {
      if(!instance)
        instance = new Game();

      return instance;
    }

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
    SDL_Renderer * getRenderer() const { return renderer; }

  private:
    Game()
    { 
      level = 1;
      running = true;
      atexit(SDL_Quit);
    }
    static Game * instance;
    int level;
    SDL_Window * window;
    SDL_Renderer * renderer;
    bool running;
    InputHandler * inputHandler;
};
typedef Game TheGame;

#endif
