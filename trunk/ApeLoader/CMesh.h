#ifndef _CMESH_H_
#define _CMESH_H_

#include "GameComponent.h"
#include "Ogre.h"

#include "ObjectManager.h"
#include "OgreRender.h"

class ObjectManager;
class OgreRender;

using namespace Ogre;

class GameComponent;

class CMesh : public GameComponent {
public:
	Ogre::Entity *mEntity;
	Ogre::String mMeshName;
	Ogre::String mEntityName;

	CMesh();
	CMesh(Ogre::String meshName,Ogre::String entityName);
	CMesh(Ogre::Entity* entity);

	~CMesh();

	void update();
	void setup();
	
	Ogre::Entity* getEntity();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
private:
	static std::string mFamilyID;
	static std::string mComponentID;

	ObjectManager* mObjMan;
	OgreRender* mOgre;
};

#endif
