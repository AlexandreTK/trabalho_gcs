#include "LevelParser.h"
#include "TextureManager.h"
#include "base64.h"
#include <string>

using std::string;
using std::vector;

Level* LevelParser::parseLevel(const char *levelFile)
{
	//Create a TinyXML document and load the map XML
	TiXMLDocument levelDocument;
	levelDocument.LoadFile(levelFile);

	//Create the level object
	Level* pLevel = new Level();

	//get the root node
	TiXmlElement* pRoot = levelDocument.RootElement();

	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	//parse the Tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	//parse any object layer
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("layer"))
		{
			parseTileLayers(e, pLevel->getLayers(), pLevel-> getTilesets());
		}
	}

return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, vector<Tileset>* pTilesets)
{
	//first add the tileset to the texture manager
	TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"), TheGame::Instance()-getRenderer());
	
	//create a tileset object
	Tileset tileset;

	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	pTilesetRoot->FirstChildElement()->Attribute("firstgrid", &tileset.firstGridID);
	pTilesetRoot->FirstChildElement()->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->FirstChildElement()->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->FirstChildElement()->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->FirstChildElement()->Attribute("margin", &tileset.margin);

	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tilewidth + tileset.spacing);

	pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, vector<Layer*> *pLayers, const vector<Tileset>* pTilesets)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
	//tile data
	vector< vector<int>> data;

	string decodedIDs;
	TiXmlElement* pDataNode;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("data"))
		{
			pDataNode == e;
		}
	}
	for (TiXmlElement* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText * text = e->ToText();
		string t = text -> Value();
		decodedIDs = base64_decode(t);
	}

	//uncompress zlib compression
	uLongf numGids = m_width * m_height * sizeof(int);
	vector<unsigned> gids(numGids);
	uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	vector<int> layerRow(m_width);

	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = gids[rows * m_width + cols];
		}
	}

	pTileLayer->setTileIDs(data);

	pLayers->push_back(pTileLayer);
}
