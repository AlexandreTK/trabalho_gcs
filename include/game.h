#ifndef GAME_H
#define GAME_H

class Game
{
  public:
    Game();
    ~Game();

    int init();
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
};

#endif
