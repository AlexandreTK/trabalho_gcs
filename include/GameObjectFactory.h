#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <string>
#include <map>
#include "GameObject.h"
#include <iostream>



using std::string;
using std::map;
using std::cout;

class BaseCreator
{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator(){}
	
};

class GameObjectFactory
{
public:
  ~GameObjectFactory();
  
  static GameObjectFactory * Instance()
  {
    if(!instance)
      instance = new GameObjectFactory();

    return instance;
  }
	bool registerType(std::string typeID, BaseCreator* pCreator)
	{
		map<string, BaseCreator*>::iterator it = m_creators.find(typeID);
		// if the type is already registered, do nothing
		if(it != m_creators.end())
		{
			delete pCreator;
			return false;
		}

		m_creators[typeID] = pCreator;
		return true;
	}

	GameObject* create(string typeID)
	{

		map<string, BaseCreator*>::iterator it =
		m_creators.find(typeID);

		if(it == m_creators.end())
		{
			cout << "could not find type: " << typeID << "\n";
			return 0;
		}

		BaseCreator* pCreator = (*it).second;
		return pCreator->createGameObject();
	}

private:
	GameObjectFactory() { }
  static GameObjectFactory * instance;
	map<string, BaseCreator*> m_creators;
		
};
typedef GameObjectFactory TheGameObjectFactory;
#endif
