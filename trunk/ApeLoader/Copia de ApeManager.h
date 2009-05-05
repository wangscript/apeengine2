#ifndef _MESSAGE_MAN_
#define _MESSAGE_MAN_

#include "sigslot.h"
#include "OgreRender.h"
#include "InputHandler.h"
#include "Physics.h"
#include "EditableTerrain.h"
#include "ApeScene.h"
#include "ObjectManager.h"

class ObjectManager;
class EditableTerrain;
class InputHandler;
class OgreRender;
class Physics;
class ApeScene;

//#include "Ogre.h"

//using namespace Ogre;
using namespace sigslot;

class ApeManager {
public:
	ApeManager();
	~ApeManager();

	static ApeManager getSingleton();

	//void getReceiver(void* object,)

	//signal1<bool> booleanSignal;
	//signal0<> emptySignal;

	//void connect(sigslot::sig)

	

	void initialize();
	void update();
	bool isEditorMode();

	bool loadApeMap(Ogre::String mapFileName);

	static OgreRender* getOgreImp() { 
		return mOgre; 
	}
	static InputHandler* getInputImp() { 
		return mInput; 
	}
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

private:
	
	static ApeManager* mInstance;
	
	static ObjectManager* mObjectManager;
	static InputHandler* mInput;
	static OgreRender* mOgre;
	static Physics* mPhysics;
	static EditableTerrain* mTerrain;
	static ApeScene* mScene;
	//acDebug* debug = new acDebug(sceneMgr,window);

	static bool mIsEditorMode;
};

#endif