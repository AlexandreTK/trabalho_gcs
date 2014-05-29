#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include "Level.h"
#include <vector>

using std::vector;

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot, vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, vector<Layer*> *pLayers, const vector<Tileset>* pTilesets);

	int m_tileSize;
	int m_width;
	int m_heigth;
};

#endif