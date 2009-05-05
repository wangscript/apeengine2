#include "Physics.h"
//#include "ETTerrainManager.h"
//#include "ETTerrainInfo.h"
#include "CSound.h"

//Physics* Physics::ms_Singleton = 0;

template<> Physics* Ogre::Singleton<Physics>::ms_Singleton = 0;
Physics* Physics::getSingletonPtr(void)
{
	return ms_Singleton;
}
Physics& Physics::getSingleton(void)
{  
	assert( ms_Singleton );  return ( *ms_Singleton );  
}

//OgreRender* ogre,EditableTerrain* terrain
Physics::Physics() : mOgre(0),mWorld(0),mScene(0) 
{

}

//void Physics::createTerrainActor()
//{
//	NxHeightFieldDesc mNxHeightFieldDesc;
//	
//	//ET:: GameSystemManager::getSingleton()->getTerrain()->getTerrainManager()
//	
//	ET::TerrainManager * tMgr = mTerrain->getTerrainManager(); //)->getTerrainManager();
//
//	//ET::TerrainManager * tMgr = GameSystemManager::getSingleton()->getTerrain()->getTerrainManager();
//	mNxHeightFieldDesc.nbColumns = (NxU32)tMgr->getTerrainInfo().getHeight();
//    mNxHeightFieldDesc.nbRows    = (NxU32)tMgr->getTerrainInfo().getWidth();
//    mNxHeightFieldDesc.verticalExtent      = -1000;
//    mNxHeightFieldDesc.convexEdgeThreshold = 0;
//	
//    //Allocate storage for data
//    mNxHeightFieldDesc.samples      = new NxU32[mNxHeightFieldDesc.nbColumns * mNxHeightFieldDesc.nbRows];
//    mNxHeightFieldDesc.sampleStride = sizeof(NxU32);
//
//    NxU8* currentByte = (NxU8*)mNxHeightFieldDesc.samples;
//    ET::TerrainInfo i = tMgr->getTerrainInfo();
//    std::vector<float> heightData = i.getHeightmapData();
//      
//    for (NxU32 row = 0; row < mNxHeightFieldDesc.nbRows; row++)
//    {
//		for (NxU32 column = 0; column < mNxHeightFieldDesc.nbColumns; column++)
//		{
//			NxHeightFieldSample* currentSample = (NxHeightFieldSample*)currentByte;
//
//			//Transform ETM array of floats into NxHeightFieldSample
//			currentSample->height         = static_cast<NxI16>(((i.at(row,column)) * 65535) - 32768);
//			currentSample->materialIndex0 = 0;
//			currentSample->materialIndex1 = 0;
//            
//			currentSample->tessFlag = 0;
//            
//			currentByte += mNxHeightFieldDesc.sampleStride;
//		}
//    }
//	NxHeightField *mHeightField;
//    mHeightField = mWorld->getSDK()->createHeightField(mNxHeightFieldDesc);
//	
//    delete[] mNxHeightFieldDesc.samples;
//	
//    Ogre::AxisAlignedBox aab = tMgr->getTerrainInfo().getExtents(); // getDimensions();
//    Ogre::Vector3 s = aab.getSize();
//
//    NxVec3 size;
//    size.x = s.x;
//    size.y = s.y;
//    size.z = s.z;
//
//    NxHeightFieldShapeDesc heightFieldShapeDesc;
//    heightFieldShapeDesc.heightField   = mHeightField;
//    heightFieldShapeDesc.shapeFlags      = NX_SF_FEATURE_INDICES | NX_SF_VISUALIZATION;
//    heightFieldShapeDesc.heightScale   = size.y / 65536.0f;
//    heightFieldShapeDesc.rowScale      = size.x / NxReal(mNxHeightFieldDesc.nbRows-1);
//    heightFieldShapeDesc.columnScale   = size.z / NxReal(mNxHeightFieldDesc.nbColumns-1);
//
//    heightFieldShapeDesc.materialIndexHighBits = 0;
//    heightFieldShapeDesc.holeMaterial = 2;
//    heightFieldShapeDesc.localPose.t = NxVec3(0,0,0);
//    Ogre::Vector3 offset = tMgr->getTerrainInfo().getOffset();
//	heightFieldShapeDesc.localPose.t = NxVec3(offset.x,0,offset.z); // AABB1
//
//	NxMaterialDesc matDesc;
//	matDesc.setToDefault();
//	matDesc.flags = NX_MF_DISABLE_FRICTION;
//	matDesc.dynamicFriction = 0;
//	//matDesc.dynamicFriction = 0.0f;
//	matDesc.staticFriction = 0.0f;
//	//matDesc.restitution = 0.8f; 
//
//	NxMaterial* mMat = mScene->getNxScene()->createMaterial(matDesc); // ->createMaterial("terrainMaterial");
//	//mMat->setRestitution(0.8f); 
//	//mMat->setStaticFriction(0.05f); //0.05f
//	//mMat->setDynamicFriction(0.8f); //0.8f
//	
//
//	heightFieldShapeDesc.materialIndex = mMat->getMaterialIndex();
//
//    NxActorDesc actorDesc;
//    actorDesc.shapes.pushBack(&heightFieldShapeDesc);
//    actorDesc.density   = 1.0f;
//
//    actorDesc.globalPose.t = NxVec3(0,size.y/2,0);
//
//	NxActor* act = mScene->getNxScene()->createActor(actorDesc);
//	//NxShape* const* shape = act->getShapes();
//	
//	//NxMaterial* mat = mScene->getNxScene()->getMaterialFromIndex((*shape)->getMaterial());
//	//mat->setDynamicFriction(0.75f);
//	//mat->setStaticFriction(0.75f);
//
//	return;
//}

PhysicsActor* Physics::getActorFromCrosshair() {
	//NxShape* characterShape = getCharacterActor(0)->getShapes()[0];

	//NxRay worldRay;
	//worldRay.orig	= NxVec3(588.064,900.998,988.782);
	//worldRay.orig = NxTools::convert(OgreRender::getSingleton().getCamera()->getPosition());
	//worldRay.dir	= NxTools::convert(OgreRender::getSingleton().getCamera()->getDirection());

	//NxRaycastHit hit;

	//NxOgre::RayCaster* mRay = mScene->getActorsFromRaycast();

	/*
	NxOgre::Actors acts = mScene->getActorsFromRaycast(OgreRender::getSingleton().getCamera()->getPosition(),
											   OgreRender::getSingleton().getCamera()->getDirection(),
												1000);
	for (NxOgre::Actor* a = acts.begin(); a = acts.next();) { 
		if(a->isDynamic())
		{
			//NxOgre::VoidPointer* vp = static_cast<NxOgre::VoidPointer*>(a.userData);
			//NxOgre::Actor* userDataActor = vp->toActor();
			CActor* tmpActor = dynamic_cast<CActor*>(a); //->toActor();
			OgreRender::getSingleton().getDebugText()->addText("GameObject: " + tmpActor->getOwnerObject()->getID());
			return tmpActor;
		}
	}
	*/

	Ogre::Vector3 pos = OgreRender::getSingleton().getCamera()->getDerivedPosition();
	Ogre::Vector3 dir = OgreRender::getSingleton().getCamera()->getDerivedOrientation() * Vector3::NEGATIVE_UNIT_Z;
	//Vector3 dir = ori * Vector3::UNIT_Z;

	//NxOgre::RayCaster *rc = new NxOgre::RayCaster(pos, dir.normalisedCopy(), 50000, NxOgre::RayCaster::RCT_ALL, mScene);
	NxOgre::RayCaster *rc = new NxOgre::RayCaster(pos, dir.normalisedCopy(), 50000, NxOgre::RayCaster::RCT_CLOSEST, mScene);
	//if(rc->castShape(NxOgre::RayCaster::AF_NONE))

	if(rc->castShape(NxOgre::RayCaster::AF_DYNAMIC_ONLY))
	{
		//NxShape* characterShape =  getCharacterActor(0)->getShapes()[0];

		//NxOgre::NxString s;
		//s = rc->mReport.mShortName;
		//int i = &rc->mReport.getFirst() count();

		//if(rc) {
		//	NxOgre::CharacterSystem::Character* ch = rc->getClosestCharacter();
		//	if(ch)
		//		return NULL;
		//}

		//if(&rc->mReport.mShortName)
		//	return NULL;

		for(NxOgre::RayCastHit* aHit = &rc->mReport._begin(); !rc->mReport._atEnd(); aHit = &rc->mReport._next())
		{
			//m_pLog->logMessage("RayCastHit");
			NxOgre::Actor *actor = rc->getClosestActor();
			PhysicsActor* tmpActor = 0;
			tmpActor = static_cast<PhysicsActor*>(actor); //->toActor();
			//OgreRender::getSingleton().getDebugText()->addText("GameObject: " + tmpActor->getOwnerObject()->getID());
			return tmpActor;
			//actor->_destroyActor();
		}
	}
	return NULL;

/*
	NxRay worldRay;
	//worldRay.orig	= NxVec3(588.064,900.998,988.782);
	worldRay.orig = NxTools::convert(cpos);
	worldRay.dir	= NxTools::convert(dir);

	NxRaycastHit hit;
	characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, true);
	NxShape* shape = mScene->raycastClosestShape(worldRay, NX_ALL_SHAPES, hit);
*/

	//mRay->setOrigin(OgreRender::getSingleton().getCamera()->getPosition());
	//mRay->setDirection(OgreRender::getSingleton().getCamera()->getDirection());
	//mRay->setDsetMaxDistance(100);
	//mRay->type(NxOgre::Raycaster::RCT_All);
	//mRay->accuracy(NxOgre::Raycaster::AC_Accurate); 
	//mRay->cast();
	

	//ActorRaycastHits::SharedListIterator ah = mRay->getActors().getIterator();  mScene->getActorsFromRaycast()
	//characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, true);
	//mScene->getNxScene()->raycastClosestShape(worldRay, NX_ALL_SHAPES, hit);
	//characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, false);
	/*
	if(hit.shape)
	{

		NxActor& actor = hit.shape->getActor();
		if(actor.isDynamic())
		{
			NxOgre::VoidPointer* vp = static_cast<NxOgre::VoidPointer*>(actor.userData);
			NxOgre::Actor* userDataActor = vp->toActor();
			CActor* tmpActor = dynamic_cast<CActor*>(userDataActor); //->toActor();
			OgreRender::getSingleton().getDebugText()->addText("GameObject: " + tmpActor->getOwnerObject()->getID());
			return tmpActor;
		}
	} else {
		return NULL;
	}
	*/
}

void Physics::initialize() {

	mOgre = OgreRender::getSingleton().getSingletonPtr();
	//mTerrain = EditableTerrain::getSingleton().getSingletonPtr();

	//NxOgre::PhysXParams params;
	//params.mTimeController = NxOgre::PhysXParams::TC_NONE;
	
	

	//params.mCustomTimeControllerPtr = time;
	//mWorld = new NxOgre::World(params); 

	
	
	//mWorld = new NxOgre::World("time-controller: ogre, framelistener: no");
	mWorld = new NxOgre::World("time-controller: none, framelistener: no");

	//mWorld->getSDK()->setParameter(NX_SKIN_WIDTH, 0.025f);
	mWorld->getSDK()->setParameter(NX_SKIN_WIDTH, 0.025f);
	mWorld->getSDK()->setParameter(NX_VISUALIZATION_SCALE, 1.0f);
	//mWorld->getSDK()->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
	//mWorld->getSDK()->setParameter(NxParameter::)
	mWorld->getSDK()->getFoundationSDK().getRemoteDebugger()->connect("127.0.0.1");

	mGravity = 9.8f;
	mSkin = 1.0f;
	mRestitution = 0.8f;
	mStaticFriction = 0.05f;
	mDynamicFriction = 0.8f;

	mIsInitialized = true;
	mIsRunningSim = false;
	
	createScene();

	
	NxOgre::ActorGroup* mDynamicGroup = mScene->createActorGroup("dynamic_group");
	NxOgre::ActorGroup* mStaticGroup = mScene->createActorGroup("static_group");
	
	mDynamicGroup->setCallback(this);
	
	//mDynamicGroup->setCollisionCallback(mStaticGroup, NX_NOTIFY_ALL, true);
	mDynamicGroup->setCollisionCallback(mDynamicGroup, NX_NOTIFY_ALL, true);
	mDynamicGroup->setCollisionCallback(mStaticGroup, NX_NOTIFY_ALL, true);

	mScene->getNxScene()->setUserTriggerReport(this);
}



void Physics::onStartTouch(NxOgre::Actor* _actorA, NxOgre::Actor* _actorB, NxOgre::ContactStream*) {
	Ogre::String namea = _actorA->getName();
	Ogre::String nameb = _actorB->getName();

	Ogre::Vector3 v = _actorA->getLinearVelocity();
	Ogre::Vector3 v2 = _actorB->getLinearVelocity();

	NxOgre::VoidPointer* vp = static_cast<NxOgre::VoidPointer*>(_actorA->getUserData());
	if(vp) {
		NxOgre::Actor* userDataActor = vp->toActor();

		if(userDataActor) {
			PhysicsActor* tmpActor = dynamic_cast<PhysicsActor*>(userDataActor); //->toActor();

			if(tmpActor) {
				CSound* sound = dynamic_cast<CSound*>(tmpActor->getOwnerObject()->getComponent("CSound"));
				if(sound)
					sound->playSound();

				//CRoom* room = dynamic_cast<CRoom*>(tmpActor->getOwnerObject()->getComponent("CRoom"));
				//if(room) {
					//mCurrentRoom->mRoomZone
				//	setCurrentRoom(room->mName);
				//}

					//mOgre->getDebugText()->addText("onStartTouch: " + tmpActor->getOwnerObject()->getID());
			}

		}
	}
	

}
void Physics::onEndTouch(NxOgre::Actor* _actorA, NxOgre::Actor* _actorB, NxOgre::ContactStream*) {
	/*
	Ogre::String namea = _actorA->getName();
	Ogre::String nameb = _actorB->getName();

	Ogre::Vector3 v = _actorA->getLinearVelocity();
	Ogre::Vector3 v2 = _actorB->getLinearVelocity();

	NxOgre::VoidPointer* vp = static_cast<NxOgre::VoidPointer*>(_actorA->getUserData());
	NxOgre::Actor* userDataActor = vp->toActor();

	if(userDataActor) {
		PhysicsActor* tmpActor = dynamic_cast<PhysicsActor*>(userDataActor); //->toActor();

		if(tmpActor) {
			CObjectSound* sound = dynamic_cast<CObjectSound*>(tmpActor->getOwnerObject()->getComponent("CObjectSound"));
			if(sound)
				sound->stop();
			
			//mOgre->getDebugText()->addText("onStartTouch: " + tmpActor->getOwnerObject()->getID());
		}

	}
	*/
}
void Physics::onTouch(NxOgre::Actor* _actorA, NxOgre::Actor* _actorB, NxOgre::ContactStream*) {

}

void Physics::onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status)
{
	// other actor is a trigger too?
	//if ((NxI32)(otherShape.getActor().userData) < 0)
	//	return;

	NxActor& triggerActor = triggerShape.getActor();
	//NxI32 triggerNumber = -(NxI32)triggerActor.userData;
	//NxI32 triggerIndex = triggerNumber - 1;

	if(status & NX_TRIGGER_ON_ENTER)
	{
		// A body entered the trigger area for the first time
		//	gNbTouchedBodies[triggerIndex]++;
		
		GameObject* g = static_cast<GameObject*>(triggerActor.userData);
		if(g) {
			//OgreRender::getSingleton().getDebugText()->addText("On_Enter: " + Ogre::StringConverter::toString(triggerShape.getName()));
			GameObject* go = ObjectManager::getSingleton().mMainCharacter;
			CCharacter* mCChar = dynamic_cast<CCharacter*>(go->getComponent("CCharacter"));
			CRoom* room = dynamic_cast<CRoom*>(g->getComponent("CRoom"));
			if(room && mCChar) {
				mCChar->setCurrentRoom(room->mName);
				Ogre::Camera* cam = mCChar->getCurrentRoom()->mCamera;

				OgreRender::getSingleton().getCamera()->setOrientation(cam->getDerivedOrientation() );
				OgreRender::getSingleton().getCamera()->setPosition(cam->getDerivedPosition() );
				//mOgre->getCamera() = mCChar->getCurrentRoom()->mCamera;
				//mOgre->getCamera()
				//Ogre::Camera* cam = OgreRender::getSingleton().getCamera();
				//cam = mCChar->getCurrentRoom()->mCamera;

			}

		}
	}
	if(status & NX_TRIGGER_ON_LEAVE)
	{
		// A body left the trigger area
		//	gNbTouchedBodies[triggerIndex]--;
 		OgreRender::getSingleton().getDebugText()->addText("On_Leave: " + Ogre::StringConverter::toString(triggerShape.getName()));
	}
	//NX_ASSERT(gNbTouchedBodies[triggerIndex]>=0);	//Shouldn't go negative
}

Physics::~Physics() {
	//destroyPhysx();
}
/*
void Physics::addUserCharacter(Character* character) {
	if(character)
		mCharacter = character;
}
*/
void Physics::createScene() {

	//mScene = mWorld->createScene("Main", GameSceneManager::getSingleton()->getSceneManager()
//		, "gravity: yes, floor: no, renderer: ogre");


	/*
	NxOgre::SceneParams sceneParams;
	sceneParams.setToDefault();   
	
	sceneParams.mGravity = NxVec3(0,-100,0);
	sceneParams.mFloor = false;
	sceneParams.mRenderer = NxOgre::SceneParams::RN_OGRE;

	//sceneParams.m
/*
	mScene = mWorld->createScene("Main",sceneParams );
	mScene->setGravity()
		mScene->setSimulationMode())
*/

	
	mScene = mWorld->createScene("Main", mOgre->getSceneManager()
		, "gravity: yes, floor: false, renderer: ogre"); //controller: accumulator, 
	
	mScene->setGravity(Vector3(0,-6.8,0));

	//mWorld->
	//SceneController* sc = new SceneController(mScene);
	//sc->

	//mScene->setSceneController()

	

	//mWorld->

	//Body *mCube = mScene->createBody("cube;cube.1m.mesh", new Cube(1), Vector3(600,400,280), "mass: 10");
	
	//mCube->setGlobalPosition(Vector3(600,400,280));

	//Create user controlled Character
//	Character* mChar = new Character("ninja","ninja.mesh",mOgre->getCamera()
//		,CameraView::CAMERA_FIRST_PERSON,mWorld);

//	addUserCharacter(mChar);

	//createTerrainActor();

}

void Physics::startSimulation() {
	if(mWorld) {
		mIsRunningSim = true;
//		mCharacter->isActive = true;
	}
	//else
		//Display error saying cant start sim without initialazing PhysX
		
}
void Physics::stopSimulation() {
	if(mWorld)
		mIsRunningSim = false;
}

//Destroy all Nx objects of the current world
void Physics::resetScene() {
	//resetScene();
}

void Physics::simulate(const Ogre::Real &time)
{
	//updatePhysics(time);
	//mScene->simulate(time);
	//if(mIsInitialized && mIsRunningSim && mWorld)
	
	mWorld->simulate(time);
	mWorld->render(time);

	//mWorld->getPhysXDriver()->simulate(time);
	//mWorld->render(time);

//	if(mIsInitialized && mIsRunningSim && mCharacter)
//		mCharacter->simulate(time);
}

void Physics::setDefaultConfig()
{
	mGravity = 9.8f;
	mSkin = 1.0f;
	mRestitution = 0.8f;
	mStaticFriction = 0.05f;
	mDynamicFriction = 0.8f;
}

NxOgre::World* Physics::getWorld()
{
	return mWorld;
}
NxOgre::Scene* Physics::getScene()
{
	return mScene;
}

void Physics::shutdown()
{
	//destroyPhysx();
}
/*
Character* Physics::getUserCharacter() {
	if(mCharacter)
		return mCharacter;
}
*/