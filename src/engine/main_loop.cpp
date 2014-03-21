#include <iostream>

using std::cout;
using std::endl;

int init()
{
  cout << "Inicialização" << endl;

  return 1; 
}

bool levelFinished()
{
  cout << "Terminou o nível?" << endl;
  return true;
}

int nextLevel()
{
  cout << "Próximo nível" << endl;
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
