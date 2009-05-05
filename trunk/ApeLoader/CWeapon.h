#ifndef _CWEAPON_H_
#define _CWEAPON_H_

#include "GameComponent.h"
#include "Ogre.h"

#include "CMesh.h"
#include "CActor.h"
#include "CRender.h"
#include "PhysicsActor.h"
#include "CCharacter.h"
#include "CCamera.h"
#include "CSound.h"

#include "ParticleUniverseSystem.h"
#include "ParticleUniverseSystemManager.h"

//class CMesh:
class GameComponent;
class CMesh;
class CActor;
class CRender;
class PhysicsActor;
class CCharacter;
class CCamera;
//class CCharacterSound;
//class ApeSound;

using namespace Ogre;

enum weaponType {
	MACHINEGUN,
	FLAME_THROWER
};

class CWeapon : public GameComponent {
public:
	
	//static Ogre::Vector3 Position;
	//Ogre::Vector3 Position;
	std::string mWeaponName;
	bool mIsHoldingWeapon;

	CWeapon(weaponType wt, std::string name);
	//CWeapon(Ogre::Vector3 vec);
	
	~CWeapon();

	void update();
	
	void updateNode();
	void updateWeapon();

	void setup();
	void pickUp();
	void shoot();
	void stopShooting();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}

	Ogre::SceneNode* mNode;

private:
	bool mIsShooting;

	PhysicsActor* mPhysicsActor;
	CMesh* mMesh;
	CRender* mRender;
	CCharacter* mCharacter;
	CActor* mActor;
	CCamera* mCamera;
	
	Ogre::Real mGunFlareLastTime;
	Ogre::Real mGunFlareDelay;
	
	Ogre::Real mShotSoundLastTime;
	Ogre::Real mShotSoundDelay;

	//std::map<std::string,ApeSound*> mSoundList;

	Ogre::Vector3 mOffsetParticlePosition;
	weaponType mWeaponType;
	
	ParticleUniverse::ParticleSystem* mGunFlareParticle;
	ParticleUniverse::ParticleSystem* mShotParticle;
	ParticleUniverse::ParticleSystem* mHitParticle;

	static const std::string mFamilyID;
	static const std::string mComponentID;
};

#endif
