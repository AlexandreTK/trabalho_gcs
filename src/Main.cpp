#include "Game.h"

int main()
{
  TheGame::Instance()->init("Kays Against The World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

  //TheGame::Instance()->drawLogos();

  TheGame::Instance()->drawMenu();
  while(TheGame::Instance()->getRunning())
  {
    while(true)
    {
      TheGame::Instance()->updateTimeStep();
      TheGame::Instance()->input();
      TheGame::Instance()->ia();
      TheGame::Instance()->physics();
      TheGame::Instance()->update();
      TheGame::Instance()->draw();
      if(TheGame::Instance()->levelFinished())
      {
       break;
      }

    }
    TheGame::Instance()->setLevel(TheGame::Instance()->nextLevel());

    TheGame::Instance()->event();
  }

  //TheGame::Instance()->drawCredits();
  return 0;
}
