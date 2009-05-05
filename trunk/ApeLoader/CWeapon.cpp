#include "CWeapon.h"

/*static*/ 
const std::string CWeapon::mFamilyID = "CWeapon";
const std::string CWeapon::mComponentID = "CWeapon";

CWeapon::CWeapon(weaponType wt, std::string name)
{
	mWeaponName = name + "_weapon";
	mWeaponType = wt;
	mNode = NULL;
	mIsShooting = false;
	mIsHoldingWeapon = false;

	mGunFlareParticle = OgreRender::getSingleton().getParticleManager()->createParticleSystem(mWeaponName, "fireSystem", 
		OgreRender::getSingleton().getSceneManager());

	//mMainNode->attachObject(mSys);
	mGunFlareDelay = 200;
	mShotSoundDelay = 200;
	mGunFlareLastTime = OgreRender::getSingleton().getTimeMS();
	mShotSoundLastTime = OgreRender::getSingleton().getTimeMS();

}

CWeapon::~CWeapon()
{

}
void CWeapon::shoot() {
	if(mIsHoldingWeapon) {
		mIsShooting = true;
		mGunFlareParticle->start();
		//mSoundList["shotSound"]->play();
	}

}

void CWeapon::stopShooting() {
	if(mIsHoldingWeapon) {
		mIsShooting = false;
		mGunFlareParticle->stop();
		if(mWeaponType == weaponType::FLAME_THROWER) {
			//mSoundList["fireThrower"]- stop();
			//SoundManager::getSingleton().getManager()->stopSound(mSoundList["shotSound"]->getSound(1)->getName());
		}
		
	}
}

void CWeapon::updateWeapon() {
	
}

void CWeapon::updateNode() {
	
	mNode = OgreRender::getSingleton().mWeaponNode->createChildSceneNode(mWeaponName + "_child");
	mNode->attachObject(mGunFlareParticle);
	
	Quaternion orient;
	orient = Quaternion(Degree(45), Vector3::NEGATIVE_UNIT_Y);

	mNode->setOrientation(orient);

	//ApeSound* fireSound = new ApeSound();
	
	//Ogre::String soundFileName;
	//bool loopSound;
	//if(mWeaponType == weaponType::FLAME_THROWER) {
	//	soundFileName = "fire_large_loop.ogg";
	//	loopSound = true;
	//} else if(mWeaponType == weaponType::MACHINEGUN) {
	//	soundFileName = "Shoot_Kalashnikov.ogg";
	//	loopSound = false;
	//}

	//fireSound->addSound(mWeaponName + "_1",soundFileName,50,mNode->getName(),loopSound);
	//mSoundList["shotSound"] = fireSound; //ApeSound::SOUND_WALK

	//mWeaponOrientOffset = Quaternion(Degree(45), Vector3::UNIT_Y);

	//mRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	//CActor* mActor = dynamic_cast<CActor*>(getOwnerObject()->getComponent("CActor"));
	//CWeapon *mWeapon = dynamic_cast<CWeapon*>(this->getOwnerObject()->getComponent("CWeapon"));
	//CRender *mRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	//if(mActor && !mNode) {
	//if(mNode) {
		//mNode = OgreRender::getSingleton().mCustomCamera->getWeaponHolderNode(); // mActor->mPhysicsActor->mNode; // mRender->mNode;
	//	mNode = OgreRender::getSingleton().
		//if(!mNode->getAttachedObject(mSys->getName()))
		
		//mNode->attachObject(mSys);
	//}
}

void CWeapon::update() {

	if(mIsHoldingWeapon && mIsShooting) {
		if(mWeaponType != weaponType::FLAME_THROWER) {
			if(OgreRender::getSingleton().getTimeMS() >= (mShotSoundLastTime + mShotSoundDelay)) {
				//mSoundList["shotSound"]->play();
				//mShotSoundLastTime = OgreRender::getSingleton().getTimeMS();
			}
		}
		
		if(mWeaponType != weaponType::FLAME_THROWER) {
			if(OgreRender::getSingleton().getTimeMS() >= (mGunFlareLastTime + mGunFlareDelay)) {
				mGunFlareParticle->start();
				mGunFlareLastTime = OgreRender::getSingleton().getTimeMS();
			} else {
				mGunFlareParticle->stop();
			}
		}

	}

	/*
	Vector3 pos;
	if(mIsHoldingWeapong) {
		pos = mCamera->getItemHolderNode()->_getDerivedPosition();
	}
	*/

	/*
	Vector3 pos = mCamera->getItemHolderNode()->_getDerivedPosition();
	Ogre::Quaternion q; // = OgreRender::getSingleton().getCamera()->getDerivedOrientation();

	q = mCamera->getPlayerNode()->_getDerivedOrientation();

	//Change here later
	mPhysicsActor->setAngularVelocity(Vector3::ZERO);
	mPhysicsActor->setLinearVelocity(Vector3::ZERO);
	mPhysicsActor->setGlobalPosition(pos);
	mPhysicsActor->setGlobalOrientation(q);
	*/
	
}

void CWeapon::pickUp() {
	/*
	mIsHoldingWeapong = true;
	*/
}

void CWeapon::setup() {
	/*
	mIsHoldingWeapong = false;

	mMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	mRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	//mCharacter = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));
	mActor = dynamic_cast<CActor*>(getOwnerObject()->getComponent("CActor"));
	//mCamera = dynamic_cast<CCamera*>(getOwnerObject()->getComponent("CCamera"));
	//mPhysicsActor = mActor->mPhysicsActor;
	*/
}
