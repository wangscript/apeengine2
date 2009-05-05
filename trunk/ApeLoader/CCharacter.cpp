#include "CCharacter.h"
#include "NxOgreConverter.h"
#include "ApeManager.h"

#include "CActor.h"
#include "CSound.h"

#include "SoundManager.h"

#include "GameObject.h"
#include "ObjectManager.h"

#include "CRoom.h"

class CRoom;

class ObjectManager;
class GameObject;

/*static*/ 
const std::string CCharacter::mFamilyID = "CCharacter";
const std::string CCharacter::mComponentID = "CCharacter";

NxControllerAction  CCharacter::onShapeHit(const NxControllerShapeHit& hit)
{
	if(1 && hit.shape)
	{

 		NxActor& actor = hit.shape->getActor();
		NxOgre::VoidPointer* vp = static_cast<NxOgre::VoidPointer*>(actor.userData);
		NxOgre::Actor* userDataActor = vp->toActor();
		PhysicsActor* tmpActor = dynamic_cast<PhysicsActor*>(userDataActor); //->toActor();
		if(tmpActor) {
			CRoom* room = dynamic_cast<CRoom*>(tmpActor->getOwnerObject()->getComponent("CRoom"));
			if(room) {
				//mCurrentRoom->mRoomZone
				//setCurrentRoom(room->mName);
			}
		}


		if(isMoving()) {
			
			
			//NxActor& actor = hit.shape->getActor();

			const char* actorName;
			
			if(mIsOverObject) {
				//NxOgre::VoidPointer* vp = static_cast<NxOgre::VoidPointer*>(actor.userData);
				if(vp) {

					NxOgre::Actor* userDataActor = vp->toActor();
					
					PhysicsActor* tmpActor = dynamic_cast<PhysicsActor*>(userDataActor); //->toActor();
					if(tmpActor) {
						//CRoom* room = dynamic_cast<CRoom*>(tmpActor->getOwnerObject()->getComponent("CRoom"));
						//if(room) {
							//mCurrentRoom->mRoomZone
						//	setCurrentRoom(room->mName);
						//}

						CSound* tmpObjSound;
						tmpObjSound = dynamic_cast<CSound*>(tmpActor->getOwnerObject()->getComponent("CSound")); //->toActor();
						if(tmpObjSound) {
							//tmpObjSound->
							mContactMaterial = tmpObjSound->getSoundCategory();
							//if(tmpObjSound->mSoundType == "predefined") {
							//	if(soundCat == "grass" || soundCat == "wood" || soundCat == "stone" || soundCat == "earth" || soundCat == "metal" || soundCat == "snow") {
							
							

							//if(soundCat != "") {
							//	CSound* charSound = dynamic_cast<CSound*>(getOwnerObject()->getComponent("CSound")); //->toActor();
							//	if(charSound)
							//		charSound->playSound(soundCat);

							//}

							//	}
							//}
							//else {

							//}
						}

					}

				}
				else
				{
					//mCharSound->playSound("grass");
				}
			}

			//CActor* tmpActor = dynamic_cast<CActor*>(userDataActor); //->toActor();
			//PhysicsActor* tmpActor = dynamic_cast<PhysicsActor*>(userDataActor); //->toActor();
			
		}

		NxCollisionGroup group = hit.shape->getGroup();
		if(group!=GROUP_COLLIDABLE_NON_PUSHABLE)
		{
			NxActor& actor = hit.shape->getActor();
			
			try {
				bool b = actor.isDynamic();
			} catch(...) {
				//Ogre::LogManager::getSingleton().logMessage("*** Error loading Ape map file ***");
				return NX_ACTION_NONE;
			}

			if(actor.isDynamic())
			{
				NxOgre::VoidPointer* vp = static_cast<NxOgre::VoidPointer*>(actor.userData);
				NxOgre::Actor* userDataActor = vp->toActor();
				//CActor* tmpActor = dynamic_cast<CActor*>(userDataActor); //->toActor();
				PhysicsActor* tmpActor = dynamic_cast<PhysicsActor*>(userDataActor); //->toActor();
				
				//Ogre::String name = tmpActor->getOwnerObject()->getID();
				//mOgre->getDebugText()->addText("GameObject: " + name);

				if ((mPts[mNbPts].x != hit.worldPos.x) || (mPts[mNbPts].y != hit.worldPos.y) || (mPts[mNbPts].z != hit.worldPos.z))
				{
					mPts[mNbPts++].x = hit.worldPos.x;
					mPts[mNbPts++].y = hit.worldPos.y;
					mPts[mNbPts++].z = hit.worldPos.z;
					if (mNbPts==MAX_NB_PTS)  mNbPts = 0;
				}

				CWeapon* mWeapon = dynamic_cast<CWeapon*>(tmpActor->getOwnerObject()->getComponent("CWeapon"));

				if(mWeapon && !mIsHoldingItem && !mIsHoldingGun) {
					mIsHoldingGun = true;
					mWeapon->mIsHoldingWeapon = true;
					mHasGun = true;
					mWeaponActor = tmpActor;
					
					//mWeapon->mNode = mCamera->getWeaponHolderNode();
					//mWeapon->updateWeapon();

					CRender* mWeaponRender = dynamic_cast<CRender*>(tmpActor->getOwnerObject()->getComponent("CRender"));

					Ogre::String name = mWeaponRender->getNodeName();
					mWeaponList[name] = mWeapon;

					//mWeaponActor->raiseActorFlag(NxActorFlag::)
					
					//mWeaponActor->raiseBodyFlag(NxBodyFlag::NX_BF_KINEMATIC);
					//mWeaponActor->raiseActorFlag(NxActorFlag::NX_AF_DISABLE_COLLISION);
					
					
					//OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->D
					//tmpActor->mEntity->getParentNode()->
					
					//////////////////////////////////////////////////////////////////////////
					//Removido

					tmpActor->raiseBodyFlag(NxBodyFlag::NX_BF_KINEMATIC);
					tmpActor->raiseActorFlag(NxActorFlag::NX_AF_DISABLE_COLLISION);

					tmpActor->mNode->detachAllObjects();
					mCamera->getWeaponHolderNode()->attachObject(tmpActor->mEntity);

					Quaternion mWeaponOrientOffset;
					//mWeaponOrientOffset = Quaternion(Degree(90), Vector3::NEGATIVE_UNIT_Y);
					mWeaponOrientOffset = Quaternion(Degree(45), Vector3::UNIT_Y);
					mCamera->getWeaponHolderNode()->setOrientation(mWeaponOrientOffset);
					mCamera->getWeaponHolderNode()->setScale(2.0f,2.0f,2.0f);
					//////////////////////////////////////////////////////////////////////////
					
					//CMesh* mMesh = dynamic_cast<CMesh*>(this->getOwnerObject()->getComponent("CMesh"));
					//Ogre::Bone* b = mMesh->mEntity->getSkeleton()->getBone("Black_Mama_Biped R Hand")->createChild("weapon"); 
					//b->
					//mWeapon->pickUp();

				}

				// We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
				// useless stress on the solver. It would be possible to enable/disable vertical pushes on
				// particular objects, if the gameplay requires it.
				if(hit.dir.y==0.0f)
				{
					//NxF32 coeff = actor.getMass() * hit.length * 10.0f;
					NxF32 coeff = 100.0f;
					actor.addForceAtLocalPos(hit.dir*coeff, NxVec3(0,0,0), NX_IMPULSE);
					//						actor.addForceAtPos(hit.dir*coeff, hit.controller->getPosition(), NX_IMPULSE);
					//						actor.addForceAtPos(hit.dir*coeff, hit.worldPos, NX_IMPULSE);
				}
			}
		}
	}

	return NX_ACTION_NONE;
}

NxControllerAction  CCharacter::onControllerHit(const NxControllersHit& hit)
{
	return NX_ACTION_NONE;
}


bool CCharacter::startJump(NxF32 v0)
{
	if(mJump)	
		return false;

	//mCharSound->playSound("jump"); // getSound("jump")->play();

	mJumpTime = 0.0f;
	mV0	= v0;
	mJump = true;
}
void CCharacter::startFall(NxF32 v0)
{
	if(mFall)	return;
	mFallTime = 0.0f;
	mV0	= v0;
	mFall = true;
	mCAnim->setAnimationState(9);
}
void CCharacter::stopFall()
{
	if(!mFall)	return;
	mFall = false;
}

void CCharacter::startWalking(NxF32 v0)
{
	if(mWalk)	return;
	//mWalkTime = 0.0f;
	mV0	= v0;
	mWalk = true;
}
void CCharacter::stopWalking()
{
	if(!mWalk)	return;
	mWalk = false;
}
void CCharacter::stopJump()
{
	if(!mJump)	return;
	mJump = false;
}


NxF32 CCharacter::getJumpHeight(NxF32 elapsedTime)
{

	if(mJump) {
		mJumpTime += elapsedTime * mJumpStrength;
		NxF32 h = G*mJumpTime*mJumpTime + mV0*mJumpTime;
		NxF32 height = (h - mDefaultGravity.y)*elapsedTime;
		return height;
	} else {
		return -0.1f;
	}

}

NxF32 CCharacter::getFallHeight(NxF32 elapsedTime)
{
	if(mJump)
		return -0.1f;
	//if(mJump) {
	//	mJumpTime += elapsedTime * 6.0;
//
//	}

	if(mFall) {
		mFallTime += elapsedTime * mJumpStrength;
		//NxF32 h = G*mFallTime*mFallTime;
		NxF32 h = G*mFallTime*mFallTime - mV0*mFallTime;
		NxF32 height = (h - mDefaultGravity.y)*elapsedTime;
		if(height > 0)
			return -0.1;
		//else
			return height;
	} else {
		return -0.1; //mDefaultGravity.y
	}
}

class myRaycastQueryReport : public NxSceneQueryReport
{
	virtual	NxQueryReportResult	onBooleanQuery(void* userData, bool result){ return NX_SQR_CONTINUE; };
	virtual	NxQueryReportResult	onShapeQuery(void* userData, NxU32 nbHits, NxShape** hits){ return NX_SQR_CONTINUE; };
	virtual	NxQueryReportResult	onSweepQuery(void* userData, NxU32 nbHits, NxSweepQueryHit* hits){ return NX_SQR_CONTINUE; };

	virtual	NxQueryReportResult	onRaycastQuery(void* userData, NxU32 nbHits, const NxRaycastHit* hits)
	{
		unsigned int i = (unsigned int)userData;
		if (nbHits > 0) {
		//	gHits[i] = hits[0];
		} else {
		//	gHits[i].shape = NULL;
		}
		return NX_SQR_CONTINUE;
	}
}gQueryReport;

//, UserAllocator* userAlloc, NxScene* scene,

void CCharacter::setCurrentRoom(Ogre::String room) {
	if(mCurrentRoomName == room)
		return;

	mCurrentRoomName = room;

	std::map<const std::string, GameObject*>::iterator iter;
	std::map<const std::string, GameObject*> gos;
	gos = ObjectManager::getSingleton().getGOs();
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		CRoom *mCRoom = dynamic_cast<CRoom*>(iter->second->getComponent("CRoom"));
		if(mCRoom) {
			if(mCRoom->mName == mCurrentRoomName) {
				mCurrentRoom = mCRoom;
			}
			//mCRoom->mCamera = maxScene->GetSceneManager()->getCamera(mCRoom->mCameraName);
		}
	}
	//mCamera->

}
CRoom* CCharacter::getCurrentRoom() {
	return mCurrentRoom;
}

bool CCharacter::loadSettings() { //std::string characterFileName

	if(mXMLFileName != "") {
		
		std::string mFilePath = "../../Media/Characters/" + mXMLFileName + ".xml";
		
		XMLNode xMainNode;

		try {
			xMainNode=XMLNode::openFileHelper(mFilePath.c_str(),"ApeEngine"); //,"PMML"

		} catch(...) {
			Ogre::LogManager::getSingleton().logMessage("*** Error loading character file ***");
			return false;
		}
		
		XMLNode xNode=xMainNode.getChildNode("Character");

		try {
			//mMeshName = xNode.getAttribute("mMeshName");
			mSpeed = Ogre::StringConverter::parseReal(xNode.getAttribute("mSpeed"));
			mAcceleration = Ogre::StringConverter::parseReal(xNode.getAttribute("mAcceleration"));
			mInitialRadius = Ogre::StringConverter::parseReal(xNode.getAttribute("mInitialRadius"));
			mInitialHeight = Ogre::StringConverter::parseReal(xNode.getAttribute("mInitialHeight"));
			mScale = Ogre::StringConverter::parseReal(xNode.getAttribute("mScale"));
			mSkinwidth = Ogre::StringConverter::parseReal(xNode.getAttribute("mSkinwidth"));
			mJumpStrength = Ogre::StringConverter::parseReal(xNode.getAttribute("mJumpStrength"));
			mTurnReactionSpeed = Ogre::StringConverter::parseReal(xNode.getAttribute("mTurnReactionSpeed"));
			mTimestepMultiplier = Ogre::StringConverter::parseReal(xNode.getAttribute("mTimestepMultiplier"));

			mSpeedMultiplier = Ogre::StringConverter::parseReal(xNode.getAttribute("mSpeedMultiplier"));
			mCharacterSpeed = Ogre::StringConverter::parseReal(xNode.getAttribute("mCharacterSpeed"));
			
			G = Ogre::StringConverter::parseReal(xNode.getAttribute("mGravity"));
			mDefaultGravity = NxVec3(0,Ogre::StringConverter::parseReal(xNode.getAttribute("mGravity")),0);

			mSensibility = Ogre::StringConverter::parseReal(xNode.getAttribute("mSensibility"));
			mMouseSpeed = Ogre::StringConverter::parseReal(xNode.getAttribute("mMouseSpeed"));


		} catch (...) {
			Ogre::LogManager::getSingleton().logMessage("*** Error loading ApeScene data from Character map file ***");
			return false;
		}

	}
	return true;
}

CCharacter::CCharacter(std::string xmlCharacterFileName) : mSceneQueryObject(0)
{
	mOgre = OgreRender::getSingletonPtr();
	mPhysics = Physics::getSingletonPtr();
	mObjMan = ObjectManager::getSingletonPtr();

	mMyAllocator = (UserAllocator*)mPhysics->getWorld()->getPhysXDriver()->getUserAllocator();
	mScene = mPhysics->getWorld()->getScenes()->get("Main")->getNxScene();

	//////////////////////////////////////////////////////////////////////////
	
	mSceneQueryObject = NULL;
	NxSceneQueryDesc sceneQueryDesc;
	sceneQueryDesc.report = &gQueryReport;
	mSceneQueryObject = mScene->createSceneQuery(sceneQueryDesc);
	mXMLFileName = xmlCharacterFileName;
    //.
}

void CCharacter::setCamera(Ogre::Camera* cam) {
	//mCamera = cam;
}

Real CCharacter::getTurnReactionSpeed() {
	return mTurnReactionSpeed;
}

float getElapsedTime()
{
	static LARGE_INTEGER previousTime;
	static LARGE_INTEGER freq;
	static bool init = false;
	if(!init){
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&previousTime);
		init=true;
	}
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	unsigned long long elapsedTime = currentTime.QuadPart - previousTime.QuadPart;
	previousTime = currentTime;
	return (float)(elapsedTime)/(freq.QuadPart);
}

void CCharacter::createControllerManager(NxUserAllocator* a)
{
	mManager = NxCreateControllerManager(a);
}

void CCharacter::releaseControllerManager()
{
	NxReleaseControllerManager(mManager);
}

void CCharacter::updateControllers()
{
	mManager->updateControllers();
}

NxController* CCharacter::initCharacterControllers(const NxVec3 startPos, NxReal scale, NxScene& scene)
{
	NxCapsuleControllerDesc desc;
	NxVec3 tmp			= startPos;
	desc.position.x		= tmp.x;
	desc.position.y		= tmp.y;
	desc.position.z		= tmp.z;
	desc.radius			= mInitialRadius * mScale;
	desc.height			= mInitialHeight * mScale;
	desc.upDirection	= NX_Y;
	//		desc.slopeLimit		= cosf(NxMath::degToRad(45.0f));
	desc.slopeLimit		= 0;
	desc.skinWidth		= mSkinwidth;
	desc.stepOffset		= 0.5;
	desc.stepOffset		= mInitialRadius * 0.5 * mScale;
	//	desc.stepOffset	= 0.01f;
	//		desc.stepOffset		= 0;	// Fixes some issues
	//		desc.stepOffset		= 10;
	desc.callback		= this; //&gControllerHitReport;
	
	NxController* c = mManager->createController(&scene, desc);
	c->setCollision(true);
	
	NxActor* mActor = c->getActor(); 
	mActor->setGroup(1);			

	NxShape* characterShape = getCharacterActor(0)->getShapes()[0];
	characterShape->setFlag(NX_SF_DYNAMIC_DYNAMIC_CCD, true);

	return mManager->getController(0);
}

void CCharacter::releaseCharacterControllers(NxScene& scene)
{
	mManager->purgeControllers();
}

const NxVec3& CCharacter::getCharacterPos() //NxU32 characterIndex
{
	NxExtendedVec3 pos = mManager->getController(0)->getFilteredPosition();
	return NxVec3(pos.x,pos.y,pos.z);
}

NxActor* CCharacter::getCharacterActor(NxU32 characterIndex)
{
	return mManager->getController(characterIndex)->getActor();
}

bool CCharacter::resetCharacterPos(NxU32 index, const NxVec3& pos)
{
	return mManager->getController(index)->setPosition(NxExtendedVec3(pos.x, pos.y, pos.z));
}

bool CCharacter::updateCharacterExtents(NxU32 index, bool& increase)
{
	if(index&1)
	{
		NxBoxController* c = static_cast<NxBoxController*>(mManager->getController(index));
		NxVec3 extents = c->getExtents();
		NxF32 inc = 1.0f;
		NxVec3 pos = getCharacterPos();
		if (increase)
		{
			extents.y += inc;
			pos.y += inc;
		} 
		else 
		{ 
			extents.y -= inc;
			pos.y -= inc;
		}

		if(1)
		{
			NxBounds3 worldBounds;
			worldBounds.setCenterExtents(NxVec3(pos.x, pos.y, pos.z), extents);
			c->setCollision(false);	// Avoid checking overlap with ourself
			bool Status = mScene->checkOverlapAABB(worldBounds);
			c->setCollision(true);
			if(Status)
			{
				printf("Can not resize box!\n");
				return false;
			}
		}

		increase = !increase;	// Increase or decrease height each time we're called

		// WARNING: the SDK currently doesn't check for collisions when changing extents, so if you're close
		// to a wall you might end up penetrating it. In some cases you might also fall through the level.
		// A more advanced implementation will take care of that later.
		c->setPosition(NxExtendedVec3(pos.x,pos.y,pos.z));
		return c->setExtents(extents);
	}
	else
	{
		NxCapsuleController* c = static_cast<NxCapsuleController*>(mManager->getController(index));
		NxF32 height = c->getHeight();
		NxF32 radius = c->getRadius();
		NxF32 inc = 1.0f;
		NxVec3 pos = getCharacterPos();
		if (increase)
		{
			height += inc;
			pos.y += inc*0.5f;
		} 
		else 
		{ 
			height -= inc;
			pos.y -= inc*0.5f;
		}

		if(1)
		{
			NxCapsule worldCapsule;
			worldCapsule.p0.x = worldCapsule.p1.x = pos.x;
			worldCapsule.p0.y = worldCapsule.p1.y = pos.y;
			worldCapsule.p0.z = worldCapsule.p1.z = pos.z;
			worldCapsule.p0.y -= height*0.5f;
			worldCapsule.p1.y += height*0.5f;
			worldCapsule.radius = radius;
			c->setCollision(false);	// Avoid checking overlap with ourself
			bool Status = mScene->checkOverlapCapsule(worldCapsule);
			c->setCollision(true);
			if(Status)
			{
				printf("Can not resize capsule!\n");
				return false;
			}
		}

		increase = !increase;	// Increase or decrease height each time we're called

		// WARNING: the SDK currently doesn't check for collisions when changing height, so if you're close
		// to a wall you might end up penetrating it. In some cases you might also fall through the level.
		// A more advanced implementation will take care of that later.
		c->setPosition(NxExtendedVec3(pos.x, pos.y, pos.z));
		return c->setHeight(height);
	}
}


void CCharacter::update() {

	//updateCharacter();

}
void CCharacter::setup() {
	
	mIsOverObject = false;

	//mSpeed = 60.0;
	//mAcceleration = 1.3f;
	//mInitialRadius = 3.0f;
	//mInitialHeight = 18.0f;
	//mSkinwidth = 0.2f;
	//mScale = 1.5;
	//mJumpStrength = 200; //160
	//mTurnReactionSpeed = 445.0;
	//mTimestepMultiplier	= 1.0f;
	//mSpeedMultiplier = 1.0f;
	//mCharacterSpeed	= 0.1f;
	//G = -9.8f;
	//mDefaultGravity = NxVec3(0.0f, -9.8f, 0.0f);
	//mSensibility = 0.005f;
	//mMouseSpeed = 0.10;

	//loadSettings();

	//mCurrentState = IDLE;
	mPause = false;
	mApplyGravity = true;
	mMotion			= false;	
	mManager = NULL;
	mNbPts = 0;
	mJump =  false;
	mV0 = 0.0f;
	mJumpTime = 0.0f;
	//mAnimState = IDLE;
	mWalk = false;
	mFall = false;
	mWalkTime = 0;
	mFallTime = 0;
	mStopWalk = false;
	mIsHoldingGun = false;
	mHasGun = false;
	mIsHoldingItem = false;
	


	Vector3 mPos = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"))->Position;
	mCAnim = dynamic_cast<CAnimation*>(getOwnerObject()->getComponent("CAnimation"));
	mCamera = dynamic_cast<CCamera*>(getOwnerObject()->getComponent("CCamera"));
	//mCharSound = dynamic_cast<CCharacterSound*>(getOwnerObject()->getComponent("CCharacterSound"));

	mStartPos = NxVec3(mPos.x,mPos.y,mPos.z); //

	//loadSettings(mXMLFileName);

	createControllerManager(mMyAllocator); //getUserAllocator()
	initCharacterControllers(mStartPos, 1, *mScene);


	//Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(mMeshName + "_entity",mMeshName);
	//ent->setCastShadows(true);
	
	//CMesh* mCMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	//if(mCMesh) {
	//	mCMesh->mEntity = ent;
	//}
	
}
void CCharacter::setWalkState(bool state) {
	mStopWalk = state;
}


//NxF32 CCharacter::cameraHit(NxVec3 cpos, NxVec3 dir)
NxF32 CCharacter::rayHitDistance(Vector3 cpos, Vector3 dir)
{
	
	NxShape* characterShape = getCharacterActor(0)->getShapes()[0];

	NxRay worldRay;
	//worldRay.orig	= NxVec3(588.064,900.998,988.782);
	worldRay.orig = NxTools::convert(cpos);
	worldRay.dir	= NxTools::convert(dir);

	NxRaycastHit hit;
	characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, true);
	NxShape* shape = mScene->raycastClosestShape(worldRay, NX_ALL_SHAPES, hit);
	characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, false);

	if(!mPause)	
		mWorldRay = worldRay;

	return shape ? hit.distance : 0; //NX_MAX_F32
}

NxF32 CCharacter::rayHitGroundDistance()
{

	NxShape* characterShape = getCharacterActor(0)->getShapes()[0];

	NxVec3 aPos = getCharacterPos();
	NxVec3 dir = NxVec3(0,-1,0);

	NxRay worldRay;
	worldRay.orig = aPos;
	worldRay.dir	= dir;

	NxRaycastHit hit;
	characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, true);
	NxShape* shape = mScene->raycastClosestShape(worldRay, NX_ALL_SHAPES, hit);
	characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, false);

	if(!mPause)	
		mWorldRay = worldRay;

	return shape ? hit.distance : 0; //NX_MAX_F32
}

void CCharacter::setDisplacement(Ogre::Vector3 dispVector) {
	mNextMovement = dispVector;
}
Ogre::Vector3 CCharacter::getDisplacement() {
	return mNextMovement;
}

void CCharacter::setDirection(Ogre::Quaternion orientation) {
	mDirection = orientation;
}
Ogre::Quaternion CCharacter::getDirection() {
	return mDirection;
}
void CCharacter::enableMotion(bool _motion) {
		mMotion = _motion;
}
void CCharacter::enableRotation(bool _rotation) {
	mRotating = _rotation;
}
bool CCharacter::isRotating() {
	return mRotating;
}
bool CCharacter::isMoving() {
	return mMotion;
}

bool CCharacter::isArmed() {
	return mIsHoldingGun;
}
bool CCharacter::isHoldingItem() {
	return mIsHoldingItem;
}

void CCharacter::startShooting() {

	std::map<const std::string, CWeapon*>::iterator iter;
	for(iter = mWeaponList.begin(); iter != mWeaponList.end(); iter++) {
		iter->second->shoot();
	}

}
void CCharacter::stopShooting() {
	std::map<const std::string, CWeapon*>::iterator iter;
	for(iter = mWeaponList.begin(); iter != mWeaponList.end(); iter++) {
		iter->second->stopShooting();
	}
}

void CCharacter::updateCharacter() {
	
	if(mIsHoldingItem) {
		Vector3 pos = mCamera->getItemHolderNode()->_getDerivedPosition();
		Ogre::Quaternion q; // = OgreRender::getSingleton().getCamera()->getDerivedOrientation();

		q = mCamera->getPlayerNode()->_getDerivedOrientation();

		mItemInHand->setAngularVelocity(Vector3::ZERO);
		mItemInHand->setLinearVelocity(Vector3::ZERO);
		
		mItemInHand->moveGlobalPosition(pos);
		mItemInHand->moveGlobalOrientation(q);

	}

	float elapsedTime = mOgre->getTimeSinceLastFrame();
	NxVec3 disp = NxVec3(0,0,0);
	NxVec3 horizontalDisp = NxVec3(0,0,0);

	Real mJumpMovementForce = 0.8f;

	if(!mStopWalk)
		mWalkTime += elapsedTime * mAcceleration; //acc
	else
		mWalkTime -= elapsedTime * mAcceleration;

	int maxSpeed = 1;

	//if(mJump) {
	//	maxSpeed = mJumpMovementForce;
	//}
	if(mWalkTime >= maxSpeed) {
		mWalkTime = maxSpeed;
	}

	if(mWalkTime <= 0) {
		mWalkTime = 0;
		//mCurrentState = IDLE;
		mMotion = false;
		//mCAnim->setAnimState(mCurrentState);
	}
	
	//mOgre->getDebugText()->addText("mDirection = " + Ogre::StringConverter::toString(mDirection));	
	mOgre->getDebugText()->addText("mNextMovement = " + Ogre::StringConverter::toString(mNextMovement));	
	mOgre->getDebugText()->addText("mWalkTime = " + Ogre::StringConverter::toString(mWalkTime));	

	Ogre::Vector3 tmpPos = (mDirection * mNextMovement);
	horizontalDisp = NxTools::convert(tmpPos);
	disp += horizontalDisp * (mSpeed * mWalkTime);

	disp = disp * elapsedTime;

	NxF32 heightDelta;
	
	if(mJump) {
		heightDelta = getJumpHeight(elapsedTime);
		if(heightDelta!=0.0f) {
			disp.y+=heightDelta;
		}
		if(heightDelta < 0)
			mIsFalling = true;
	
	} else {
		heightDelta = getFallHeight(elapsedTime);
		if(heightDelta!=0.0f)
			disp.y+=heightDelta;
	}

	mNbPts = 0;
	NxF32 sharpness = 1.0f;
	NxU32 collisionFlags;
	NxController* c = mManager->getController(0);
	
	disp.z = 0;

	c->move(disp, 1, 0.000001f, collisionFlags, sharpness);

	mIsOnAir = true;

	if(collisionFlags & NXCC_COLLISION_SIDES) {
		stopJump();
		mIsOverObject = false;
		mIsOnAir = false;
	}

	if(collisionFlags & NXCC_COLLISION_UP) {
		stopJump();
		mIsOverObject = false;
		mIsOnAir = false;
	}

	if(collisionFlags & NXCC_COLLISION_DOWN) {
		stopJump();
		stopFall();
		mIsOverObject = true;
		mIsOnAir = false;
		if(mIsFalling) {
			mCAnim->setAnimationState(6);
			mWalkTime = 0;
		}
	}
	//mCAnim->setAnimationState(9);
	if(!(collisionFlags & NXCC_COLLISION_DOWN)) {
		if(!mJump) {
			startFall(0);
			mIsFalling = true;
		} else {
			if(mIsFalling)
			//	startFall(0);
			mCAnim->setAnimationState(9);
		}

		mIsOverObject = false;
	} else {
		mIsFalling = false;
	}
	
	updateControllers();
	
	//mMainNode->setPosition(getCharacterPos().x,getCharacterPos().y,getCharacterPos().z);
	//Vector3 pos = Vector3(getCharacterPos().x,getCharacterPos().y,getCharacterPos().z);
	//mCamera->getTargetNode()->setPosition(pos);
	//Vector3 dispVec = Vector3(disp.x,disp.y,disp.z);
	//dispVec.normalise();
	//tmpPos.normalise();
	//mCamera->getTargetNode()->setDirection(tmpPos, Ogre::SceneNode::TS_WORLD, Ogre::Vector3::UNIT_Z);

	//mCamera->getTargetNode()->setOrientation(mCamera->mCamera->getDerivedOrientation());

	//mCamera->getTargetNode()->setOrientation(Ogre::Vector3::UNIT_Z.getRotationTo(dispVec));

	//mMotion = false;
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	//Vector3 dist = PlayerNode->getOrientation() * Vector3::NEGATIVE_UNIT_Z;
	//Quaternion quat = dist.getRotationTo(MainNode->getOrientation() * Vector3::NEGATIVE_UNIT_Z); 
	//mDestYaw = quat.getYaw();
	//mOgre->getDebugText()->addText("yaw =" + Ogre::StringConverter::toString(mDestYaw));
	//mOgre->getDebugText()->addText("yaw =" + Ogre::StringConverter::toString(quat.getYaw()));
	//mOgre->getDebugText()->addText("keyPress =" + Ogre::StringConverter::toString(mInput->forward));
}

bool CCharacter::isFalling() {
	return mIsFalling;
}
bool CCharacter::isOnAir() {
	return mIsOnAir;
}
bool CCharacter::isOverObject() {
	return mIsOverObject;
}

Ogre::Vector3 CCharacter::getCharacterPosOgre() {

	NxVec3 pos = getCharacterPos();
	return Ogre::Vector3(pos.x,pos.y,pos.z);
}

void CCharacter::throwItemInHand(Real force) {

	if(mIsHoldingItem && mItemInHand) {
		
		if(!mItemInHand->isDynamic())
			return;

		mItemInHand->clearBodyFlag(NxBodyFlag::NX_BF_KINEMATIC);

		mItemInHand->setAngularVelocity(Vector3::ZERO);
		mItemInHand->setLinearVelocity(Vector3::ZERO);
		mIsHoldingItem = false;

		//Ogre::Vector3 dir = mCamera->getPlayerNode()->_getDerivedOrientation() * Vector3::NEGATIVE_UNIT_Z;
		Ogre::Vector3 dir = OgreRender::getSingleton().getCamera()->getDerivedOrientation() * Vector3::NEGATIVE_UNIT_Z;


		//dir.normalise();

		mItemInHand->addForce(dir * force);
		mItemInHand = NULL;
	}
	if(mIsHoldingGun && mWeaponActor) {
		if(!mWeaponActor->isDynamic())
			return;
		
		//Vector3 pos = mCamera->getPlayerNode()->_getDerivedPosition();
		//Ogre::Quaternion q;
		//q = mCamera->getPlayerNode()->_getDerivedOrientation();
		//mWeaponActor->moveGlobalPosition(pos); // + Vector3(10,20,0)
		//Quaternion mWeaponOrientOffset;
		//mWeaponOrientOffset = Quaternion(Degree(90), Vector3::NEGATIVE_UNIT_Y);
		//mWeaponActor->moveGlobalOrientation(q);
	

		//mWeaponActor->mNode->detachAllObjects();
		mCamera->getWeaponHolderNode()->detachAllObjects(); // attachObject(mWeaponActor->mEntity);
		mWeaponActor->mNode->attachObject(mWeaponActor->mEntity);

		mWeaponActor->clearBodyFlag(NxBodyFlag::NX_BF_KINEMATIC);
		mWeaponActor->clearActorFlag(NxActorFlag::NX_AF_DISABLE_COLLISION);
		
		CWeapon* mWeapon = dynamic_cast<CWeapon*>(mWeaponActor->getOwnerObject()->getComponent("CWeapon"));
		if(mWeapon) {
			mWeapon->mIsHoldingWeapon = false;
		}

		mIsHoldingItem = false;
		pickItem(mWeaponActor);
		//mIsHoldingItem = true;
		//mItemInHand = mWeaponActor;

		//throwItemInHand(0);

		mWeaponActor->setAngularVelocity(Vector3::ZERO);
		mWeaponActor->setLinearVelocity(Vector3::ZERO);
		mIsHoldingGun = false;

		//Ogre::Vector3 dir = mCamera->getPlayerNode()->_getDerivedOrientation() * Vector3::NEGATIVE_UNIT_Z;
		Ogre::Vector3 dir = OgreRender::getSingleton().getCamera()->getDerivedOrientation() * Vector3::NEGATIVE_UNIT_Z;


		//dir.normalise();

		mWeaponActor->addForce(dir * force);
		mWeaponActor = NULL;

		
	}

}

void CCharacter::pickItem(PhysicsActor* item) {

	if(!mIsHoldingItem) { 

		if(!item)
			return;

		if(!item->isDynamic())
			return;

		mItemInHand = NULL;
		mItemInHand = item;
		mIsHoldingItem = true;
		mItemInHand->raiseBodyFlag(NxBodyFlag::NX_BF_KINEMATIC);

		NxShape* characterShape = getCharacterActor(0)->getShapes()[0];

		NxCapsuleController* character = static_cast<NxCapsuleController*>(mManager->getController(0));
		Vector3 posOffset = Vector3::ZERO;
	
		Ogre::Real objectSizeY = 0;
		
		objectSizeY = item->mEntity->getBoundingBox().getSize().y;

		posOffset.y += (mInitialHeight * mScale * 4.5) + (objectSizeY * 2);
		
		mCamera->getItemHolderNode()->setPosition(0,0,0);
		mCamera->getItemHolderNode()->translate(posOffset); //0,150,-150 Vector3(0,0,-90)

	} else {
		throwItemInHand(0);
	}
}