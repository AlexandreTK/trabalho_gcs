#include <cstdlib>
#include "game.h"

int main()
{
  Game * game;

  game = NULL;

  game = (Game *) malloc(sizeof(Game));
 
  game->setLevel(game->init());

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
        break;

    }
    game->setLevel(game->nextLevel());
  }

  game->shutdown();
  return 0;
}
