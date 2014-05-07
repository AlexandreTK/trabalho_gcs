#include <cstdlib>
#include "game.h"

int main()
{
  Game * game;

  game = new Game();

  game->init("Kays against the world", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

  while(game->getLevel() > 0)
  {
    while(true)
    {
      game->updateTimeStep();
      game->input();
      game->ia();
      game->physics();
      game->update();
      game->draw();
      if(game->levelFinished())
      {
       break;
      }

    }
    game->setLevel(game->nextLevel());
  }

  game->shutdown();
  return 0;
}
