#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include <SDL.h>

using std::string;
using std::map;

class TextureManager
{
  public:
    TextureManager();
    ~TextureManager();

    bool load(string fileName, string id, SDL_Renderer * renderer);

    void draw(string id, int x, int y, int w, int h, SDL_Renderer * renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(string id, int x, int y, int w, int h, int currentRow, int currentFrame, SDL_Renderer * renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  private:
    map<string, SDL_Texture *> textureMap;
};

#endif
