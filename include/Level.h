#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include "Layer.h"
#include "LevelParser.h"

using std::string;
using std::vector;

class Level
{
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


public:

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
	friend class LevelParser;
	Level();

	vector<Tileset> m_tilesets;
	vector<Layer*> m_layers;
};

#endif
