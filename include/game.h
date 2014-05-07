#ifndef GAME_H
#define GAME_H

#include <SDL.h>

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
    void update();
    void draw();
    void setLevel(int inputLevel);
    int getLevel();

  private:
    int level;
    SDL_Window * window;
    SDL_Renderer * renderer;
};

#endif
