#include "GameObject.h"

/*
 * Load the object into the game
 */
void GameObject::load(int x, int y, int w, int h, string textureID)
{
  /*
   * Making object's x and y position equal to input x and y
   */
  this->x = x;
  this->y = y;

  /*
   * Making object's width and height equal to input width and height
   */
  this->w = w;
  this->h = h;

  /*
   * Receiving an ID for this texture
   */
  this->textureID = textureID;

  /*
   * Starting from the first frame
   */
  this->currentRow = 1;
  this->currentFrame = 1;
}

/*
 * Draw the object into the game
 */
void GameObject::draw(SDL_Renderer * renderer)
{
}

/*
 * Update the object into the game
 */
void update()
{
}

/*
 * Clean object
 */
void clean()
{
}
