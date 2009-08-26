#include "PhysicsManager.h"

template<> Nebula::PhysicsManager* Ogre::Singleton<Nebula::PhysicsManager>::ms_Singleton = 0;

namespace Nebula {

	PhysicsManager* PhysicsManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}
	PhysicsManager& PhysicsManager::getSingleton(void)
	{  
		assert( ms_Singleton );  
		return ( *ms_Singleton );  
	}

	PhysicsManager::PhysicsManager() :	mScene(0) 
	{
		initialize();
		createScene();
	}
	
	PhysicsManager::~PhysicsManager() {
		shutdown();
	}

	//NX_STATIC_SHAPES,NX_DYNAMIC_SHAPES,NX_ALL_SHAPES
	Real PhysicsManager::castRayGetHitDistance(Vector3 startPosition, Vector3 direction, bool omitTriggers,bool omitActors, bool omitStatic, bool omitDynamic, bool omitCharacters)
	{
		//NxRay worldRay;
		//worldRay.orig = NxTools::convert(startPosition);
		//worldRay.dir	= NxTools::convert(direction);

		//NxRaycastHit hit;
		//NxShape* shape = PhysicsManager::getSingleton().getScene()->getNxScene()->raycastClosestShape(worldRay, NX_ALL_SHAPES, hit);
	
		//mWorldRay = worldRay;

		//if(shape)
		//	return hit.distance;
		//else
		//	return 0;

		return 0;
	}

	//NX_STATIC_SHAPES,NX_DYNAMIC_SHAPES,NX_ALL_SHAPES
	GameObject* PhysicsManager::castRayGetClosest(Vector3 startPosition, Vector3 direction, bool omitTriggers,bool omitActors, bool omitStatic, bool omitDynamic, bool omitCharacters)
	{
		NxRay worldRay;
		worldRay.orig = NxTools::convert(startPosition);
		worldRay.dir	= NxTools::convert(direction);

		NxShapesType flags = NX_ALL_SHAPES; // NxShapeType::;
		
		NxRaycastHit hit;
		NxShape* shape = mScene->raycastClosestShape(worldRay, flags, hit);

		if(shape) {
			NxActor& actor = shape->getActor();
			if(!omitTriggers) {
				CPhysicsTrigger* trigger = static_cast<CPhysicsTrigger*>(actor.userData);
				if(trigger)
					return trigger->getOwnerObject();
			}

			if(!omitActors) {
				
				CPhysicsActor* physicsActor = static_cast<CPhysicsActor*>(actor.userData);
				if(physicsActor) {
					//if(!omitDynamic) {
					//	if(physicsActor->isDynamic()) {
							return physicsActor->getOwnerObject();
					//	}
					//} else {
						
					//}

				}
			}
			
			if(!omitCharacters) {
				CCharacterController* character = static_cast<CCharacterController*>(actor.userData);
				if(character)
					return character->getOwnerObject();
			}
		
		}

		//if(shape)
		//	return hit.distance;
		//else
		//	return 0;

		return NULL;
	}

	bool PhysicsManager::start() { 
		return true;
	}

	void PhysicsManager::onSuspend() {

	}

	void PhysicsManager::update() {
		Ogre::Real time = OgreManager::getSingleton().getTimeSinceLastFrame();
		simulate(time);
	}

	void PhysicsManager::onResume() {

	}
	void PhysicsManager::stop() {

	}

	UserAllocator* PhysicsManager::getUserAllocator() {
		if(mUserAllocator)
			return mUserAllocator;
		else
			return NULL;
	}

	bool PhysicsManager::initialize() {
		mIsInitialized = false;
		mIsSceneCreated = false;
		mIsRunningSim = false;

		mUserAllocator = new UserAllocator;

		NxPhysicsSDKDesc desc;
		desc.setToDefault();
		
		NxSDKCreateError errorCode = NXCE_NO_ERROR;

		//&mErrorStream
		mSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION,mUserAllocator,NULL,desc); //, NULL, new ErrorStream(), desc, &errorCode
		if(mSDK == NULL)
		{
			//printf("\nSDK create error (%d - %s).\nUnable to initialize the PhysX SDK, exiting the sample.\n\n", errorCode, getNxSDKCreateError(errorCode));
			return false;
		}

		mSDK->getFoundationSDK().getRemoteDebugger()->connect("127.0.0.1");
		mSDK->setParameter(NX_SKIN_WIDTH, 0.05f);

		mIsInitialized = true;
		
		return true;

	}

	void PhysicsManager::onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status)
	{

		NxActor& triggerActor = triggerShape.getActor();
		NxActor& otherActor = otherShape.getActor();
		
		CPhysicsTrigger* trigger = (CPhysicsTrigger*)(triggerActor.userData);
		CPhysicsActor* actor = (CPhysicsActor*)(otherActor.userData);
		CCharacterController* character = (CCharacterController*)(otherActor.userData);

		if(trigger) {

			if(status & NX_TRIGGER_ON_ENTER)
			{
				if(actor) {
					if(actor->componentID() == "CPhysicsActor") {
						trigger->OnActorEnter(actor);
						actor->OnTriggerEnter(trigger);
						return;
					}
				}
				
				if(character) {
					if(character->componentID() == "CCharacterController") {
						trigger->OnControllerEnter(character);
						character->OnTriggerEnter(trigger);
						return;
					}
				}
			}
			
			if(status & NX_TRIGGER_ON_STAY)
			{
				if(actor) {
					if(actor->componentID() == "CPhysicsActor") {
						trigger->OnActorStay(actor);
						actor->OnTriggerStay(trigger);
						return;
					}
				}

				if(character) {
					if(character->componentID() == "CCharacterController") {
						trigger->OnControllerStay(character);
						character->OnTriggerStay(trigger);
						return;
					}
				}
			}

			if(status & NX_TRIGGER_ON_LEAVE)
			{
				if(actor) {
					if(actor->componentID() == "CPhysicsActor") {
						trigger->OnActorLeave(actor);
						actor->OnTriggerLeave(trigger);
						return;
					}
				}

				if(character) {
					if(character->componentID() == "CCharacterController") {
						trigger->OnControllerLeave(character);
						character->OnTriggerLeave(trigger);
						return;
					}
				}
			}

		}

	}

	//<li>NX_NOTIFY_ON_START_TOUCH,</li>
	//<li>NX_NOTIFY_ON_END_TOUCH,</li>
	//<li>NX_NOTIFY_ON_TOUCH,</li>
	//<li>NX_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD,</li>
	//<li>NX_NOTIFY_ON_END_TOUCH_FORCE_THRESHOLD,</li>
	//<li>NX_NOTIFY_ON_TOUCH_FORCE_THRESHOLD,</li>

	void PhysicsManager::onContactNotify(NxContactPair& pair, NxU32 events)
	{
		//CCharacterController* characterA = (CCharacterController*)(pair.actors[0]->userData);
		//CCharacterController* characterB = (CCharacterController*)(pair.actors[1]->userData);

		////////////////////////////////////////////////////////////////////////////////////////////////
		CPhysicsActor* actorA = static_cast<CPhysicsActor*>(pair.actors[0]->userData);
		CPhysicsActor* actorB = static_cast<CPhysicsActor*>(pair.actors[1]->userData);
		
		if(events & NX_NOTIFY_ON_START_TOUCH)
		{
			//Character/Character
			if (actorA && actorB) {
				actorA->OnActorStartTouch(actorB);
				actorB->OnActorStartTouch(actorA);
			}

		}
		if(events & NX_NOTIFY_ON_TOUCH)
		{
			if (actorA && actorB) {
				actorA->OnActorTouch(actorB);
				actorB->OnActorTouch(actorA);
			}
		}
		if(events & NX_NOTIFY_ON_END_TOUCH)
		{
			if (actorA && actorB) {
				actorA->OnActorEndTouch(actorB);
				actorB->OnActorEndTouch(actorA);
			}
		}
	}
	
	bool PhysicsManager::createScene() {
		
		if(!mSDK)
			return false;

		// Create a scene
		NxSceneDesc sceneDesc;
		sceneDesc.setToDefault();
		
		//sceneDesc.timeStepMethod = NX_TIMESTEP_VARIABLE;
		sceneDesc.timeStepMethod = NX_TIMESTEP_FIXED;

		sceneDesc.gravity				= NxVec3(0.0f, -14.1f, 0.0f);

		sceneDesc.simType = NX_SIMULATION_SW;

		mScene = mSDK->createScene(sceneDesc);
		if(mScene == NULL) 
		{
			printf("\nError: Unable to create a PhysX scene, exiting the sample.\n\n");
			return false;
		}

		mScene->setActorGroupPairFlags(0,0,NX_NOTIFY_ON_START_TOUCH|NX_NOTIFY_ON_TOUCH|NX_NOTIFY_ON_END_TOUCH);

		// Set default material
		NxMaterial* defaultMaterial = mScene->getMaterialFromIndex(0);
		defaultMaterial->setRestitution(0.0f);
		defaultMaterial->setStaticFriction(0.5f);
		defaultMaterial->setDynamicFriction(0.5f);

		// Create ground plane
		//NxPlaneShapeDesc planeDesc;
		//NxActorDesc actorDesc;
		//actorDesc.shapes.pushBack(&planeDesc);
		//mScene->createActor(actorDesc);


		mScene->setUserTriggerReport(this);
		mScene->setUserContactReport(this);

		mIsSceneCreated = true;
		mIsRunningSim = true;

		mCurrentTime = 0;

		return true;
	}

	void PhysicsManager::startSimulation() {
		mIsRunningSim = true;
	}

	void PhysicsManager::stopSimulation() {
		mIsRunningSim = false;
	}

	//Destroy all Nx objects of the current world
	void PhysicsManager::resetScene() {

	}

	void PhysicsManager::simulate(const Ogre::Real &time)
	{
		if(mScene && mIsRunningSim && mIsSceneCreated) {

			
			float deltaTime = (float(OgreManager::getSingleton().getGlobalTime_Milliseconds()) * 0.001) - mCurrentTime;
			mCurrentTime += deltaTime;

			//OgreManager::getSingleton().getDebugText()->addText(Ogre::StringConverter::toString(deltaTime) );

			//mScene->simulate(deltaTime);
			
			mScene->simulate(1.0f/60);

			mScene->flushStream();
			mScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
		}
	}

	void PhysicsManager::setDefaultConfig()
	{
		mGravity = 9.8f;
		mSkin = 1.0f;
		mRestitution = 0.8f;
		mStaticFriction = 0.05f;
		mDynamicFriction = 0.8f;
	}

	NxScene* PhysicsManager::getScene()
	{
		return mScene;
	}

	NxPhysicsSDK* PhysicsManager::getSDK()
	{
		return mSDK;
	}

	void PhysicsManager::shutdown()
	{
		if(mSDK != NULL)
		{
			if(mScene != NULL) 
				mSDK->releaseScene(*mScene);
			mScene = NULL;
			NxReleasePhysicsSDK(mSDK);
			mSDK = NULL;
		}
	}


} //end namespace