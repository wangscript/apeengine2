#ifndef _ZONEMANAGER_H_
#define _ZONEMANAGER_H_

#include "GameComponent.h"

#include "Ogre.h"
#include "ObjectManager.h"
#include "OgreRender.h"
#include "OgrePCZSceneManager.h"
#include "CRender.h"
#include "CRoom.h"
#include "CPortal.h"
#include "CActor.h"
#include "CLight.h"

//#include "CLight.h"
//class CLight;
//class PCZSceneManager;
class CLight;
class CActor;
class CRender;
class CRoom;
class CPortal;
class GameComponent;
class ObjectManager;
class OgreRender;

using namespace Ogre;
class ZoneManager : public Ogre::Singleton<ZoneManager>
{
public:

	ZoneManager(); //OgreRender* ogre,ObjectManager* objMan
	~ZoneManager();

	static ZoneManager& getSingleton(void);
	static ZoneManager* getSingletonPtr(void);

	void initialize();
	void createZones();
	void updateObjectsToZones();

	PCZSceneManager* getZoneManager() {
		return mPZSM;
	};

	Ogre::SceneNode* getRoomNode(Ogre::String roomName);
	CRoom* getRoom(Ogre::String roomName);

private:
	Ogre::PCZSceneManager * mPZSM;
	ObjectManager* mObjMan;
	OgreRender* mOgre;
};

#endif
