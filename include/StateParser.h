#ifndef STATEPARSER_H
#define STATEPARSER_H

#include <iostream>
#include <vector>
#include <string>
#include "ẗinyxml.h"

using std::vector;
using std::string;

class GameObject;

class StateParser
{
public:
	bool parseState(const char* stateFile, string stateID, vector<GameObject*> *pObjects);

private:
	void parseObjects (TiXmlElements* pStateRoot, vector<GameObject*> * pObjects);
	void parseTextures(TiXmlElements* pStateRoot, vector<string> *pTextureIDs);

};

#endif