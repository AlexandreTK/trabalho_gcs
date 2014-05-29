#include "LevelParser.h"

using std::string

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