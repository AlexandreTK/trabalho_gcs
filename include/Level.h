#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Layer.h"

using std::string;
using std::vector;

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	string name;
};

class Level
{
public:
		Level();
		~Level() {}

		void update();
		void render();

		vector<Tileset>* getTilesets()
		{
			return &m_tilesets;
		}
		vector<Layer*>* getLayers()
		{
			return &m_layers;
		}
private:
	vector<Tileset> m_tilesets;
	vector<Layer*> m_layers;
};

#endif
