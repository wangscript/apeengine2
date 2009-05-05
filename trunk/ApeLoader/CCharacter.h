#ifndef _CCHARACTER_H_
#define _CCHARACTER_H_

#include "xmlParser.h"

#include <stdio.h>
#define NOMINMAX
#include <Windows.h>

#include "GameComponent.h"
#include "Physics.h"
#include "NxOgre.h"
#include "Ogre.h"
#include "NxPhysics.h"
#include "NxUserAllocator.h"
#include "UserAllocator.h"
#include "ErrorStream.h"
#include "NxScene.h"
#include "NxControllerManager.h"
#include "NxController.h"
#include "NxBoxController.h"
#include "NxCapsuleController.h"
#include "OgreRender.h"
#include "ObjectManager.h"
#include "MouseFilter.h"
#include "CAnimation.h"

#include "CPosition.h"
#include "COrientation.h"
#include "CMesh.h"
#include "CActor.h"
#include "CCamera.h"
//#include "CCharacterSound.h"
#include "CWeapon.h"
#include "PhysicsActor.h"
#include "CRoom.h"

class CWeapon;
//class CCharacterSound;
class PhysicsActor;
class CCamera;
class CActor;
class CAnimation;
class InputManager;
class ObjectManager;
class OgreRender;
class Physics;
class NxScene;
class ErrorStream;
class UserAllocator;
class NxUserAllocator;
class NxController;
class NxControllerManager;
class CRoom;

enum GameGroup
{
	GROUP_NON_COLLIDABLE,
	GROUP_COLLIDABLE_NON_PUSHABLE,
	GROUP_COLLIDABLE_PUSHABLE,
};

#define COLLIDABLE_MASK	(1<<GROUP_COLLIDABLE_NON_PUSHABLE) | (1<<GROUP_COLLIDABLE_PUSHABLE)
#define MAX_NB_PTS	100

enum Direction {
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	JUMP
};

class CCharacter : public NxUserControllerHitReport, public GameComponent { // : public NxUserControllerHitReport 
private:
	static const std::string mFamilyID;
	static const std::string mComponentID;

	OgreRender* mOgre;
	Physics* mPhysics;
	ObjectManager* mObjMan;
	InputHandler* mInput;

	CAnimation* mCAnim;
	//CCharacterSound* mCharSound;

	bool mWalk;
	Real mWalkTime;
	bool mStopWalk;
	
	bool mIsOnAir;
	bool mIsFalling;

	//The material wich the character is touching
	Ogre::String mContactMaterial;

	Ogre::String mMeshName;
	Ogre::String mXMLFileName;

	NxVec3 mStartPos;
	UserAllocator* mMyAllocator;
	ErrorStream	mErrorStream;
	NxPhysicsSDK* mPhysicsSDK;
	NxVec3 mDefaultGravity;
	bool mPause;
	NxF32 G;
	NxF32 mTimestepMultiplier;
	//NxU32 mControlledCharacterIndex;
	bool mApplyGravity;
	bool mDrawSkinWidth;
	
	bool mMotion;
	
	
	NxF32 mCharacterSpeed;
	NxF32 mSpeedMultiplier;
	NxF32 mScale;
	NxF32 mV0;
	NxF32 mJumpTime;
	NxF32 mFallTime;
	bool mJump;
	bool mFall;
	NxF32 mJumpStrength;
	
	bool mRotating;

	NxRay mWorldRay;
	NxControllerManager* mManager;
	float mSkinwidth; //	0.2f
	NxF32 mInitialRadius; // = 0.5f;
	NxF32 mInitialHeight; // = 2.0f;
	NxScene* mScene;
	NxU32 mNbPts;
	NxVec3 mPts[MAX_NB_PTS];
	
	Ogre::Real mSpeed;
	Ogre::Real mAcceleration;
	Ogre::Vector3 mNextMovement;
	Ogre::Quaternion mDirection;
	Ogre::SceneManager* mSceneMgr;
	//Ogre::Camera* mCamera;
	Ogre::SceneNode* mEntityNode;
	Ogre::Entity* mEntity;
	//CameraView mCurrentView;
	NxSceneQuery* mSceneQueryObject;
	Ogre::Real mTurnReactionSpeed;

	bool mIsHoldingItem;
	PhysicsActor* mItemInHand;
	PhysicsActor* mWeaponActor;

	bool mIsHoldingGun;
	bool mHasGun;

	Real mSensibility;
	Real mMouseSpeed;
	//Real mZoom;
	//Vector3 mNodeOffset;
	enum animState mCurrentState;
	enum animState mAnimState;

	CCamera* mCamera;
	
	Ogre::String mCurrentRoomName;
	CRoom* mCurrentRoom;

	bool mIsOverObject;
	//Vector3 mNextMovement;
	//Quaternion mDirection;

	//CWeapon* mCurrentWeapon;
	//weapons mCurrentWeapon;
	std::map<const std::string,CWeapon*> mWeaponList;

public:
	
	CCharacter(std::string xmlCharacterFileName);

	bool loadSettings();
	void update();
	void setup();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
	
	void setCurrentRoom(Ogre::String room);

	Ogre::String getContactMaterial() {
		return mContactMaterial;
	}

	//Ogre::Root::getSingleton().getSceneManager()->getCamera()

	//Ogre::String getCurrentRoomName() {
	//	mCurrentRoomName;
	//}
	//void setCurrentRoom(CRoom* room) {
	//	mCurrentRoom = room;
	//}
	//Ogre::Root::getSingleton().getSceneManager()->getCamera()

	CRoom* getCurrentRoom();

	void startShooting();
	void stopShooting();

	bool isArmed();
	bool isHoldingItem();

	//int getCharacterState();
	void startFall(NxF32 v0);
	void stopFall();

	void throwItemInHand(Real force);

	void startWalking(NxF32 v0);
	void stopWalking();

	void enableMotion(bool _motion);
	void enableRotation(bool _rotation);
	bool isRotating();
	bool isMoving();
	
	bool isFalling();
	bool isOnAir();
	bool isOverObject();

	Real getTurnReactionSpeed();
	void setDisplacement(Ogre::Vector3 dispVector);
	void setWalkState(bool state);

	NxF32 rayHitGroundDistance();
	NxF32 rayHitDistance(Vector3 cpos, Vector3 dir);
	
	void pickItem(PhysicsActor* item);

	void setDirection(Ogre::Quaternion q);
	void setCamera(Ogre::Camera* cam);
	
	Ogre::Vector3 getDisplacement();
	Ogre::Quaternion getDirection();

	bool startJump(NxF32 v0);
	void stopJump();
	
	void setSpeed(Ogre::Real speed) {
		mSpeed = speed;
	}
	Ogre::Real getSpeed() {
		return mSpeed;
	}

	NxF32 getJumpHeight(NxF32 elapsedTime);
	NxF32 getFallHeight(NxF32 elapsedTime);

	void updateCharacter();
	void createControllerManager(NxUserAllocator* a);
	void releaseControllerManager();
	void updateControllers();
	NxController* initCharacterControllers(const NxVec3 startPos, NxReal scale, NxScene& scene);
	void releaseCharacterControllers(NxScene& scene);
	const NxVec3& getCharacterPos();

	Ogre::Vector3 getCharacterPosOgre();

	NxActor* getCharacterActor(NxU32 characterIndex);
	bool resetCharacterPos(NxU32 index, const NxVec3& pos);
	bool updateCharacterExtents(NxU32 index, bool& increase);
	NxControllerAction  onShapeHit(const NxControllerShapeHit& hit);
	NxControllerAction  onControllerHit(const NxControllersHit& hit);

};

#endif

