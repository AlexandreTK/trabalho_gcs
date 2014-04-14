#include <iostream>
#include "window.h"

using std::cout;
using std::endl;

int init()
{
  cout << "Initialization" << endl;

  return 1; 
}

bool levelFinished()
{
  cout << "Is the level over?" << endl;
  return true;
}

int nextLevel()
{
  cout << "Next level" << endl;
  return 0;
}

void shutdown()
{
  cout << "Shutdown" << endl;
}

void updateTimeStep() { }
void input() { }
void ia() { }
void physics() { }
void update() { }
void draw() { }

int main()
{
  int level = init();
  Window window;

  window.OpenWindow();
  while(level > 0)
  {
    while(true)
    {
      updateTimeStep();
      input();
      ia();
      physics();
      update();
      draw();
      if(levelFinished())
        break;

    }
    level = nextLevel();
  }

  shutdown();
  return 0;
}
