#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Vector2D.h"

SDLGameObject::SDLGameObject():GameObject(), m_position(0, 0), m_acceleration(0,0), m_velocity(0,0)
{
}

void SDLGameObject::load(const LoaderParams *pParams)
{
  m_position = Vector2D(pParams->getX(),pParams->getY());
  m_velocity = Vector2D(0,0);
  m_acceleration = Vector2D(0,0);
  w = pParams->getWidth();
  h = pParams->getHeight();
  textureID = pParams->getTextureID();
  currentRow = 1;
  currentFrame = 1;
  m_numFrames = pParams->getNumFrames();
}

void SDLGameObject::draw()
{
  TextureManager::Instance()->drawFrame(this->textureID,(Uint32) m_position.getX(), (Uint32) m_position.getY(), this->w, this->h, this->currentRow, this->currentFrame, TheGame::Instance()->getRenderer(), flip);
}

void SDLGameObject::update()
{

	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLGameObject::clean()
{

}
