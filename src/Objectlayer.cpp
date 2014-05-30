#include "Objectlayer.h"

void Objectlayer::update()
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->update();
	}
}

void Objectlayer::render()
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects[i]->draw();
	}
}