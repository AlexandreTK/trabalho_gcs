#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "base64.h"
#include <string>
#include "tinyxml.h"
#include "GameObjectFactory.h"
#include <zconf.h>
#include <zlib.h>
#include "Level.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

Level* LevelParser::parseLevel(const char *levelFile)
{
	//Create a TinyXML document and load the map XML
	TiXmlDocument levelDocument;
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
			parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
		}
	}
	//parse the tectures needed for this level, which have been added to properties.
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("property"))
		{
			parseTextures(e);
		}
	}

	//parse any object layers.
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("objectgroup") || e->Value() == string("layer"))
		{
			if (e->FirstChildElement()->Value() == string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers());
			}
			else if (e->FirstChildElement()->Value() == string("data"))
			{
				parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
			}
		}
	}

return pLevel;
}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, vector<Tileset>* pTilesets)
{
	//first add the tileset to the texture manager
	TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"), pTilesetRoot->Attribute("name"), TheGame::Instance()->getRenderer());
	
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
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, vector<Layer*> *pLayers, const vector<Tileset>* pTilesets)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
	//tile data
	vector< vector<int> > data;

	string decodedIDs;
	TiXmlElement* pDataNode;

	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("data"))
		{
			pDataNode = e;
		}
	}
	for (TiXmlElement* e = pDataNode->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		TiXmlText * text = e->ToText();
		string t = text -> Value();
		decodedIDs = base64_decode(t);
	}

	//uncompress zlib compression
	uLongf numGids = m_width * m_height * sizeof(int);
	vector<unsigned> gids(numGids);
	//uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

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

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
	TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, vector<Layer*> *pLayers)
{
	//create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();

	cout << pObjectElement->FirstChildElement()->Value() << endl;
	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		cout << e->Value() << endl;
		if (e->Value() == string("object"))
		{
			int x, y, width, height, numFrames, callbackID, animSpeed;
			string textureID;

			//get the initial node values type, x and y
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			GameObject *pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));

			//get the property values
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == string("properties"))
				{
					for (TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == string("property"))
						{
							if (property->Attribute("name") == string("numFrames"))
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Attribute("name") == string("textureHeight"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Attribute("name") == string("textureWidth"))
							{
								property->Attribute("value", &width);
							}
							else if (property->Attribute("name") == string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}
							else if (property->Attribute("name") == string("animSpeed"))
							{
								property->Attribute("value", &animSpeed);
							}
						}
					}
				}
			}
			pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}	

	pLayers->push_back(pObjectLayer);
}
