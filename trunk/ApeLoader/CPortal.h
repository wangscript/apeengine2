#ifndef _CPORTAL_H_
#define _CPORTAL_H_

#include "GameComponent.h"
#include "Ogre.h"
#include "ObjectManager.h"
#include "CRoom.h"
#include "OgrePCZSceneManager.h"

using namespace Ogre;

class GameComponent;
class ObjectManager;

class CPortal : public GameComponent {
public:
	
	Ogre::Real mLength;
	Ogre::Real mWidth;

	Ogre::String mRoom1;
	Ogre::String mRoom2;

	PCZSceneNode* mRoom1Node;
	PCZSceneNode* mRoom2Node;

	Ogre::PCZSceneManager * mPCZSceneMgr;

	//static Ogre::Vector3 Position;
	//Ogre::Vector3 Position;

	CPortal(Ogre::Real mLength,Ogre::Real mWidth,Ogre::String room1,Ogre::String room2);
	//CPortal(CPortalTemplate* ct);
	
	~CPortal();

	void update();
	void setup();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
private:
	static const std::string mFamilyID;
	static const std::string mComponentID;

	ObjectManager* mObjMan;
	OgreRender* mOgre;

};

#endif
