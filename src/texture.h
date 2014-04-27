#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL.h>
#include <string>

using std::string;

/*
 * Texture wrapper class
 */
class Texture
{
  public:
    /*
     * Initialize variables
     */
    Texture();

    /*
     * Deallocates memory
     */
    ~Texture();

    /*
     * Loads an image from specified path
     */
    bool loadFromFile(string path);

    /*
     * Deallocates texture
     */
    void free();

    /*
     * Renders texture
     */
    void render(int x, int y, SDL_Rect * clip = NULL, double angle = 0.0, SDL_Point * center = NULL,  SDL_RendererFlip flip = SDL_FLIP_NONE);

    /*
     * Gets image dimensions
     */

    int getWidth();
    int getHeight();

  private:
    /*
     * Actual hardware texture
     */
    SDL_Texture * texture;

    /*
     * Image dimensions
     */
    int tWidth;
    int tHeight;

};

#endif
