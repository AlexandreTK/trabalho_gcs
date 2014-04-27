#include <string>
#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include "texture.h"

using std::cout;
using std::endl;
using std::string;

Texture::Texture()
{
  texture = NULL;
  tWidth = 0;
  tHeight = 0;
}

Texture::~Texture()
{
  /*
   * Deallocates
   */
  free();
}

bool Texture::loadFromFile(string path, SDL_Renderer * wRenderer)
{
  free();

  SDL_Texture * newTexture = NULL;

  SDL_Surface * loadedSurface = IMG_Load(path.c_str());
  if(loadedSurface == NULL)
  {
    cout << "Unable to load image: " << SDL_GetError() << endl;
    return false;
  }

  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

  newTexture = SDL_CreateTextureFromSurface(wRenderer, loadedSurface);

  if(newTexture == NULL)
  {
    cout << "Unable to create texture: " << SDL_GetError() << endl;
  }
  else
  {
    tWidth = loadedSurface->w;
    tHeight = loadedSurface->h;
  }

  SDL_FreeSurface(loadedSurface);

  texture = newTexture;

  return texture != NULL;
}

Texture::free()
{
  if(texture != NULL)
  {
    SDL_DestroyTexture(texture);
    texture = NULL;
    tWidth = 0;
    tHeight = 0;
  }
}

Texture::render(int x, int y, SDL_Rect * clip = NULL, SDL_Renderer * wRenderer = NULL, double angle = 0.0, SDL_Point * center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
  SDL_Rect renderQuad = {x, y, tWidth, tHeight};

  if(clip != NULL)
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopyEx(wRenderer, texture, clip, &renderQuad, angle, center, flip);
}

Texture::getWidth()
{
  return tWidth;
}

Texture::getHeight()
{
  return tHeight;
}
