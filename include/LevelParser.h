#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include "TileLayer.h"
#include "ObjectLayer.h"
#include "Layer.h"
#include "tinyxml.h"
#include <vector>
#include "Level.h"

using std::vector;

class LevelParser
{
public:
	Level* parseLevel(const char* levelFile);

private:
	void parseTilesets(TiXmlElement* pTilesetRoot, vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, vector<Layer*> *pLayers, const vector<Tileset>* pTilesets);
	void parseTextures(TiXmlElement* pTextureRoot);
	void parseObjectLayer(TiXmlElement* pObjectElement, vector<Layer*> *pLayers);

	int m_tileSize;
	int m_width;
	int m_height;
};

#endif
