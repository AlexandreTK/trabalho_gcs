#include "StateParser.h"
#include "Game.h"
#include "GameObjectFactory.h"

using std::cerr;

bool StateParser::parseState(const char *stateFile, string stateID, vector<GameObject *> *pObjects, vector<string> *pTextureIDs)
{
	//create the XML document
	TiXmlDocument xmlDoc;

	//load the state file
	if(!xmlDoc.LoadFile(stateFile))
	{
		cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	//get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();

	//pre declare the states root node
        TiXmlElement* pTextureRoot = 0;
	TiXmlElement* pStateRoot = 0;
	//get this states root node and assign it to pStateRoot
	for(TiXmlElement* e = pRoot-> FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(e->Value() == string("TEXTURES"))
		{
			pTextureRoot = e;
		}
	}

	//now parse the textures
	parseTextures(pTextureRoot, pTextureIDs);

	//pre declare the root node
	TiXmlElement* pObjectRoot = 0;

	//get the root node and assign it to pObjectRoot
	for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if(e->Value() == string("OBJECTS"))
		{
			pObjectRoot = e;
		}
	}

	//now parse the objects
	parseObjects (pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, vector<string> *pTextureIDs)
{
	for(TiXmlElement* e = pStateRoot->FirstChildElement(); e!=NULL; e = e->NextSiblingElement())
	{
		string fileAttribute = e->Attribute("filename");
		string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute); //push into list

		TheTextureManager::Instance()->load(fileAttribute, idAttribute, TheGame::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(TiXmlElement * pStateRoot, vector<GameObject *> *pObjects)
{
	for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		string textureID;

		e->Attribute ("x", &x);
		e->Attribute ("y", &y);
		e->Attribute ("width", &width);
		e->Attribute ("height", &height);
		e->Attribute ("numFrames", &numFrames);
		e->Attribute ("callbackID", &callbackID);
		e->Attribute ("animSpeed", &animSpeed);

		textureID = e->Attribute("textureID");

		GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
		pGameObject->load(new LoaderParams(x,y,width,height,textureID,numFrames,callbackID,animSpeed));
		pObjects->push_back(pGameObject);
	}
}
