#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "GameObject.h"
#include "Layer.h"
#include <vector>

using std::vector;

class ObjectLayer : public Layer
{
public:
	virtual void update();
	virtual void render();

	vector<GameObject*>* getGameObjects()
	{
		return &m_gameObjects;
	}

private:
	vector<GameObject*> m_gameObjects;
};

#endif
