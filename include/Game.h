#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "SDLGameObject.h"
#include "GameStateMachine.h"

#include <SDL.h>
#include <vector>

using std::vector;

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
    void drawMenu();
    void drawCredits();
    bool getRunning();
    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }
    SDL_Renderer * getRenderer() const { return renderer; }
    void finishGame();
    bool checkCollision(SDLGameObject * p1, SDLGameObject * p2);

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
    vector<GameObject *> gameObjects;
    int m_gameWidth;
    int m_gameHeight;

};
typedef Game TheGame;

#endif
