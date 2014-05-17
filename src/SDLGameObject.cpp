#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Vector2D.h"

SDLGameObject::SDLGameObject(const LoaderParams * params):GameObject(params) :GameObject(params), m_position(params->getX(), params->getY()), m_velocity(0,0)
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
  TextureManager::Instance->drawFrame(this->textureID,(int) m_position.getX(), (int) m_position.getY(), this->w, this->h, this->currentRow, this->currentFrame, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{

	m_velocity += m_acceleration;
	m_position += m_velocity;
}
