#include <cstdlib>
#include "Game.h"

int main()
{
  Game * game;

  game = new Game();

  game->init("Kays Against The World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

  game->drawLogos();

  while(game->getRunning())
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

    game->event();
  }

  delete game;
  return 0;
}
