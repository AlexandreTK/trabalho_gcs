#include "TextureManager.h"

/*
 * Constructor
 */
TextureManager::TextureManager()
{
}

/*
 * Destructor
 */
TextureManager::~TextureManager()
{
}

/*
 * Load image from file
 * Set up id to texture
 * Link to renderer
 */
bool TextureManager::load(string fileName, string id, SDL_Renderer * renderer)
{
  /*
   * Load image from fileName
   */
  SDL_Surface * tempSurface = IMG_Load(fileName.c_str());

  /*
   * Check whether it's loaded the image
   * Return 0 if it failed
   */
  if(tempSurface == 0)
  {
    return false;
  }

  /*
   * Create texture based on a surface
   * and link it to a renderer
   */
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

  /*
   * Deallocates surface
   */
  SDL_FreeSurface(tempSurface);

  /*
   * Check if texture was successfully created
   * Return 0 if it failed
   */
  if(texture == 0)
  {
    return false;
  }

  /*
   * Add texture to the texture map
   */
  this->textureMap[id] = texture;

  return true;
}

void TextureManager::draw(string id, int x, int y, int w, int h, SDL_Renderer * renderer, SDL_RendererFlip flip)
{
}

void TextureManager::drawFrame(string id, int x, int y, int w, int h, int currentRow, int currentFrame, SDL_Renderer * renderer , SDL_RendererFlip flip)
{
}
