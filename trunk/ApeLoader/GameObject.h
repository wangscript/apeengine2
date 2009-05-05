#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <string>
#include <list>

#include "GameComponent.h"

class GameComponent;

class GameObject {
public:
	GameObject( const std::string& id) {
		setID(id);
	}

	const std::string& getID() const { 
		return mOID; 
	}
	
	void setID( const std::string& id ) { 
		mOID = id; 
	}

	GameComponent* getComponent(const std::string& familyID ) {
		//if(std::find(mComponents.begin(),mComponents.end())!=mComponents.end())

		if(mComponents.empty())
			return NULL;

		std::list<GameComponent*>::iterator it;
		for(it=mComponents.begin();it!=mComponents.end();it++)
		{
			GameComponent* comp = (*it);
			if(comp->familyID() == familyID)
				return comp;
		}
		return NULL;

		//std::map<const std::string, GameComponent*>::iterator iter = mComponents.begin();
		//iter = mComponents.find(familyID);
		
		//if(iter != mComponents.end()) 
		//	return iter->second;
		
		//return NULL;
	}

	GameComponent* setComponent(GameComponent *newComp) {
		//std::string family = newComp->familyID();
		//GameComponent *oldComp = mComponents[family];
		newComp->setOwnerObject(this);
		//mComponents[family] = newComp;
		mComponents.push_back(newComp);

		return newComp;
	}

	void clearComponents() {
		//std::map<const std::string, GameComponent*>::iterator iter;
		//for(iter = mComponents.begin(); iter != mComponents.end(); iter++) {
		//	delete iter->second;
		//	
		//}
		std::list<GameComponent*>::iterator it;
		for(it=mComponents.begin();it!=mComponents.end();it++)
		{
			//delete it;
		}
		mComponents.clear();
	}

	void update() {
		//std::map<const std::string, GameComponent*>::iterator iter;
		//for(iter = mComponents.begin(); iter != mComponents.end(); iter++) {
		//	iter->second->update();
		//}
		std::list<GameComponent*>::iterator it;
		for(it=mComponents.begin();it!=mComponents.end();it++)
		{
			(*it)->update();
		}
	}
	void setup() {
		//std::map<const std::string, GameComponent*>::iterator iter;
		//for(iter = mComponents.begin(); iter != mComponents.end(); iter++) {
		//	iter->second->setup();
		//}
		std::list<GameComponent*>::iterator it;
		for(it=mComponents.begin();it!=mComponents.end();it++)
		{
			(*it)->setup();
		}

	}

private:
	std::string mOID;			//unique identifier for this object
	std::list<GameComponent*> mComponents;

	//std::map<const std::string, GameComponent*> mComponents; 
	
};

#endif
