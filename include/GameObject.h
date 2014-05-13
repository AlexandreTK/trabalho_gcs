#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>

using std::cout;

class GameObject
{
  public:

    void draw() { cout << "draw game object"; }
    void update() { cout << "update game object"; }
    void clean() { cout << "clean game object"; }

  protected:
    int x;
    int y;
};

#endif
