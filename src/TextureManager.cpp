#include "TextureManager.h"
#include <SDL_image.h>

/*
 * Initializing the instance
 * So it can work as a singleton
 */
TextureManager * TextureManager::instance = NULL;

/*
 * Destructor
 */
TextureManager::~TextureManager()
{
  /*
   * Clear textureMap content
   */
  this->textureMap.clear();
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
  /*
   * The Rects there are gonna be used
   * to set up src and dest
   */
  SDL_Rect srcRect;
  SDL_Rect destRect;

  /*
   * Initializing x and y
   */
  srcRect.x = 0;
  srcRect.y = 0;

  /*
   * Setting width and height of rects
   * with input values
   */
  srcRect.w = destRect.w = w;
  srcRect.h = destRect.h = h;

  /*
   * Setting destination x and y
   * from input values
   */
  destRect.x = x;
  destRect.y = y;

  /*
   * Rendering src based on textureMap id
   * and whether or not it flips
   */
  SDL_RenderCopyEx(renderer, this->textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTexture(string id)
{
  this->textureMap.erase(id);
}

void TextureManager::drawTile(string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = margin + (spacing + width) * currentFrame;
  srcRect.y = margin + (spacing + height) * currentRow;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawFrame(string id, int x, int y, int w, int h, int currentRow, int currentFrame, SDL_Renderer * renderer , SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  /*
   * Setting up source rect to
   * move in the spritesheet
   */
  srcRect.x = w * currentFrame;
  srcRect.y = h * (currentRow - 1);

  srcRect.w = destRect.w = w;
  srcRect.h = destRect.h = h;

  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(renderer, this->textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
