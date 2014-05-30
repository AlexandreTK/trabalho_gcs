#ifndef STATEPARSER_H
#define STATEPARSER_H

#include <iostream>
#include <vector>
#include <string>
#include "tinyxml.h"

using std::vector;
using std::string;

class GameObject;

class StateParser
{
public:
	bool parseState(const char* stateFile, string stateID, vector<GameObject*> *pObjects, vector<string> *pTextureIDs);

private:
	void parseObjects (TiXmlElement* pStateRoot, vector<GameObject*> * pObjects);
	void parseTextures(TiXmlElement* pStateRoot, vector<string> *pTextureIDs);

};

#endif
