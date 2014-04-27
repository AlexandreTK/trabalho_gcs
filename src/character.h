#ifndef _CHARACTER_H
#define _CHARACTER_H

/*
 * A class for the characters displayed in the game
 */
class Character
{
  public:
    /*
     * Initialize variables
     */
    Character();

    /*
     * Shows the character on the screen relative to the camera
     */
    void render(int camX, int camY);
    
    /*
     * Access the position of the character
     */
    int getPosX();
    int getPosY();


    /*
     * Set the character's sprite width and height
     */
    void setWidth(int width);
    void setHeight(int height);

    /*
     * Access the dimensions of the sprite
     */
    void getWidth();
    void getHeight();

  private:
    /*
     * The X and Y position of the character's sprite
     */
    int cPosX, cPosY;

    /*
     * The width and height of the character's sprite
     */
    int cWidth, cHeight;
};

#endif
