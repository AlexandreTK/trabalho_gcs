#include "character.h"

/*
 * Constructor
 */
Character::Character()
{
  /*
   * Initialize offsets
   */
  cPosX = 0;
  cPosY = 0;

  /*
   * Initialize height and width
   */
  cWidth = 0;
  cHeight = 0;
}

void Character::render(int camX, int camY)
{
  /*
   * Show the character's sprite relative to the camera
   */
    
}

int Character::getPosX()
{
  return cPosX;
}

int Character::getPosY()
{
  return cPosY;
}

int Character::getWidth()
{
  return cWidth;
}

int Character::getHeight()
{
  return cHeight;
}

void Character::setWidth(int width)
{
  cWidth = width;
}

void Character::setHeight(int height)
{
  cHeight = height;
}
