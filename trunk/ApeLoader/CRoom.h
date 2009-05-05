#ifndef _CROOM_H_
#define _CROOM_H_

#include "GameComponent.h"
#include "Ogre.h"
#include "OgrePCZSceneManager.h"
#include "Physics.h"
#include "NxOgre.h"
#include "PhysicsActor.h"

using namespace Ogre;

class GameComponent;
class Physics;
class PhysicsActor;

class CRoom : public GameComponent {
public:

	Vector3 mRoomSize;
	Ogre::String mName;
	PCZone * mRoomZone;
	Ogre::String mZoneType;
	Ogre::String mZoneName;
	
	Ogre::String mCameraName;
	Ogre::Camera* mCamera;

	///NxOgre::Actor* mActor;
	//PhysicsActor* mActor;
	NxActor* mActor;
	
	//PCZSceneNode* mRoomNode;
	//static Ogre::Vector3 Position;
	//Ogre::Vector3 Position;

	CRoom(Vector3 roomSize,Ogre::String name, Ogre::String cameraName);
	
	//void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);
	void createBoxTrigger(Ogre::Vector3 boxSize);

	//CPosition(Ogre::Vector3 vec);

	~CRoom();

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
};

#endif
