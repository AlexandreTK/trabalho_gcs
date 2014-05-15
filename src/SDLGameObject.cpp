#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams * params):GameObject(params)
{
  this->x = params->getX();
  this->y = params->getY();

  this->w = params->getW();
  this->h = params->getH();

  this->textureID = params->getTextureID();

  this->currentRow = 1;
  this->currentFrame = 1;
}

void SDLGameObject::draw()
{
  TextureManager::Instance->drawFrame(this->textureID, this->x, this->y, this->w, this->h, this->currentRow, this->currentFrame, TheGame::Instance()->getRenderer());
}
