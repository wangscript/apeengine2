#ifndef _MESSAGE_MAN_
#define _MESSAGE_MAN_

#include <assert.h> 
#include <cassert>

//#include "sigslot.h"
#include "OgreRender.h"
#include "InputHandler.h"
#include "Physics.h"
//#include "EditableTerrain.h"
#include "ApeSceneManager.h"
#include "ObjectManager.h"
#include "ZoneManager.h"
//#include "PagingSystem.h"

//class PagingSystem;
class ZoneManager;
class ObjectManager;
//class EditableTerrain;
class InputHandler;
class OgreRender;
class Physics;
class ApeSceneManager;

//#include "Ogre.h"
//using namespace Ogre;
//using namespace sigslot;

//#include "singleton.h"

/*
class testclass : public Ogre::Singleton<testclass> {
public:
	bool test;

	testclass(){};
	~testclass(){};
};
testclass* testclass::ms_Singleton = NULL;
*/

class ApeManager : public Ogre::Singleton<ApeManager> { 
public:
	ApeManager();
	~ApeManager();

	static ApeManager& getSingleton(void);
	static ApeManager* getSingletonPtr(void);

	Ogre::String mCurrentMapName;

	//static ApeManager getSingleton();
	//void getReceiver(void* object,)
	//signal1<bool> booleanSignal;
	//signal0<> emptySignal;
	//void connect(sigslot::sig)

	void initialize();
	void start();
	void update();
	bool isEditorMode();
	bool loadApeMap(Ogre::String mapFileName);

	//static OgreRender* getOgreImp() { 
	//	return mOgre; 
	//}
	//static InputHandler* getInputImp() { 
	//	return mInput; 
	//}
	/*
	static Physics* getPhysicsImp() { 
		return mPhysics;
	}
	static EditableTerrain* getTerrainImp() { 
		return mTerrain;
	}
	static ApeScene* getApeSceneImp() { 
		return mScene;
	}
	static ObjectManager* getObjectManagerImp() { 
		return mObjectManager;
	}
	*/

private:
	
	//static ApeManager* mInstance;
	/*
	ObjectManager* mObjectManager;
	InputHandler* mInput;
	OgreRender* mOgre;
	Physics* mPhysics;
	EditableTerrain* mTerrain;
	ApeSceneManager* mScene;
	ZoneManager* mZoneMan;
	*/

	//acDebug* debug = new acDebug(sceneMgr,window);
	
	bool mIsEditorMode;
};

//ApeManager* ApeManager::ms_Singleton = 0;

#endif