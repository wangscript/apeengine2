#include "CCharacterController.h"

//#define _HAS_ITERATOR_DEBUGGING 0
//#define _SECURE_SCL 0

namespace Nebula {

	class myRaycastQueryReport : public NxSceneQueryReport
	{
		virtual	NxQueryReportResult	onBooleanQuery(void* userData, bool result){ return NX_SQR_CONTINUE; };
		virtual	NxQueryReportResult	onShapeQuery(void* userData, NxU32 nbHits, NxShape** hits){ return NX_SQR_CONTINUE; };
		virtual	NxQueryReportResult	onSweepQuery(void* userData, NxU32 nbHits, NxSweepQueryHit* hits){ return NX_SQR_CONTINUE; };

		virtual	NxQueryReportResult	onRaycastQuery(void* userData, NxU32 nbHits, const NxRaycastHit* hits)
		{
			unsigned int i = (unsigned int)userData;
			return NX_SQR_CONTINUE;
		}
	}gQueryReport;

	CCharacterController::CCharacterController(const CCharacterControllerDesc& desc) // : mSceneQueryObject(0)
	{

		mComponentID = "CCharacterController";
		mDesc = desc;
		
		mMyAllocator = PhysicsManager::getSingleton().getUserAllocator();
		mScene = PhysicsManager::getSingleton().getScene();

		mSceneQueryObject = NULL;
		NxSceneQueryDesc sceneQueryDesc;
		sceneQueryDesc.report = &gQueryReport;
		mSceneQueryObject = mScene->createSceneQuery(sceneQueryDesc);

		mExternalForces = Vector3::ZERO;
		mItemInHand = NULL;
	}

	//Handle collisions with actors
	NxControllerAction  CCharacterController::onShapeHit(const NxControllerShapeHit& hit)
	{
		if(1 && hit.shape)
		{			
			CPhysicsActor* actor = static_cast<CPhysicsActor*>(hit.shape->getActor().userData);

			if(actor) {
				actor->OnControllerTouch(this);

				//OgreManager::getSingleton().getDebugText()->addText( "touchingActor: true");

				if( actor->getNxActor()->readBodyFlag(NX_BF_KINEMATIC) ) {
					CAnimation* anim = static_cast<CAnimation*>(actor->getOwnerObject()->getComponent("CAnimation"));
					CElevator* elevator = dynamic_cast<CElevator*>(actor->getOwnerObject()->getComponent("CElevator"));
					
					NxF32 d = rayHitDistance(getCharacterPosOgre(),Vector3(0,-1,0));
					if(anim && !mIsOnElevator && elevator) {
						mIsOnElevator = true;
						mElevator = anim;
					}
					
				} else {
					mIsOnElevator = false;
					mElevator = NULL;
				}
				
			} else {
				//OgreManager::getSingleton().getDebugText()->addText( "isOnElevator: false");
			}

			NxCollisionGroup group = hit.shape->getGroup();
			if(group!=GROUP_COLLIDABLE_NON_PUSHABLE)
			{
				NxActor& actor = hit.shape->getActor();
				
				try {
					bool b = actor.isDynamic();
				} catch(...) {
					
					return NX_ACTION_NONE;
				}

				if(actor.isDynamic())
				{
					if(hit.dir.y==0.0f)
					{
						NxF32 coeff = 20.0f;
						actor.addForceAtLocalPos(hit.dir*coeff, NxVec3(0,0,0), NX_IMPULSE);
					}
				}
			}
		}
		return NX_ACTION_NONE;
	}
	
	//Handle collisions between Character Controlers
	NxControllerAction  CCharacterController::onControllerHit(const NxControllersHit& hit)
	{
		//Collision between Character/Character
		//callLuaFunction("OnControllerHit");
		if(1 && hit.other)
		{
			
			CCharacterController* character = static_cast<CCharacterController*>(hit.other->getActor()->userData);
				
			if(character) {
				character->OnControllerTouch(this);
			}

		}
		return NX_ACTION_NONE;
	}
	
	Real CCharacterController::getDistanceToActor(CPhysicsActor* actor) {

		return 0;
	}

	Real CCharacterController::getDistanceToCharacter(CCharacterController* character) {
		
		return 0;
	}

	Real CCharacterController::getDistanceToTrigger(CPhysicsTrigger* trigger) {

		return 0;
	}

	bool CCharacterController::OnMouseMovedOverObject( GameObject* object, Ogre::Vector3 position ) {
		
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnMouseMovedOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),object,position ); // this
		}

		//CPhysicsActor* actor = static_cast<CPhysicsActor*>(object->getComponent("CPhysicsActor"));
		//if(actor) {
		//	actor->OnCharacterMouseMovedOverObject(this, position);
		//}
		CMesh* mesh = static_cast<CMesh*>(object->getComponent("CMesh"));
		if(mesh) {
			mesh->OnCharacterMouseMovedOverObject(this, position);
		}

		return true;
	}
	bool CCharacterController::OnMouseMovedEnterOverObject( GameObject* object, Ogre::Vector3 position) {

		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnMouseMovedEnterOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),object,position); // this
		}

		//CPhysicsActor* actor = static_cast<CPhysicsActor*>(object->getComponent("CPhysicsActor"));
		//if(actor) {
		//	actor->OnCharacterMouseMovedEnterOverObject(this, position);
		//}
		CMesh* mesh = static_cast<CMesh*>(object->getComponent("CMesh"));
		if(mesh) {
			mesh->OnCharacterMouseMovedEnterOverObject(this, position);
		}

		return true;
	}
	bool CCharacterController::OnMouseMovedLeaveOverObject( GameObject* object, Ogre::Vector3 position) {

		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnMouseMovedLeaveOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),object,position); // this
		}

		//CPhysicsActor* actor = static_cast<CPhysicsActor*>(object->getComponent("CPhysicsActor"));
		//if(actor) {
		//	actor->OnCharacterMouseMovedLeaveOverObject(this, position);
		//}
		CMesh* mesh = static_cast<CMesh*>(object->getComponent("CMesh"));
		if(mesh) {
			mesh->OnCharacterMouseMovedLeaveOverObject(this, position);
		}

		return true;
	}

	bool CCharacterController::OnMouseMoved( const OIS::MouseEvent &arg ) {

		return true;
	}

	bool CCharacterController::OnMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {

		//CppEvent1<void, const bool > eventStartAttack;
		//CppEvent1<void, CPhysicsActor* > eventStartThrow;

		if(id == OIS::MB_Left) {
			if(!MyGUI::InputManager::getInstance().isFocusMouse()) {
				if (mItemInHand) {
					CPhysicsActor* actor = static_cast<CPhysicsActor*>(mItemInHand->getComponent("CPhysicsActor"));
					if(actor) {
						eventStartThrow.notify(actor);
					}
				} else {
					eventStartAttack.notify(true);
				}
			}
		}
		return true;
	}

	bool CCharacterController::OnMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {

		return true;
	}

	bool CCharacterController::OnMousePressedObject(GameObject* object, Ogre::Vector3 position, int mouseButton) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnMousePressedObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),object, position, mouseButton);
		}

		//CPhysicsActor* actor = static_cast<CPhysicsActor*>(object->getComponent("CPhysicsActor"));
		//if(actor) {
		//	actor->OnCharacterMousePressedObject(this, position, mouseButton);
		//}
		CMesh* mesh = static_cast<CMesh*>(object->getComponent("CMesh"));
		if(mesh) {
			mesh->OnCharacterMousePressedObject(this, position, mouseButton);
		}

		return true;
	}

	bool CCharacterController::OnMouseReleasedObject(GameObject* object, Ogre::Vector3 position, int mouseButton) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnMouseReleasedObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),object, position, mouseButton);
		}

		//CPhysicsActor* actor = static_cast<CPhysicsActor*>(object->getComponent("CPhysicsActor"));
		//if(actor) {
		//	actor->OnCharacterMouseReleasedObject(this, position, mouseButton);
		//}
		CMesh* mesh = static_cast<CMesh*>(object->getComponent("CMesh"));
		if(mesh) {
			mesh->OnCharacterMouseReleasedObject(this, position, mouseButton);
		}

		return true;
	}
	
	//bool CCharacterController::OnMousePressedObject(GameObject* object, Ogre::Vector3 position) {
	//	
	//}

	//bool CCharacterController::OnMouseReleasedObject(GameObject* object, Ogre::Vector3 position) {

	//}

	void CCharacterController::OnTriggerEnter(CPhysicsTrigger* trigger) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnTriggerEnter"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),trigger->getOwnerObject());
		}
	}
	void CCharacterController::OnTriggerStay(CPhysicsTrigger* trigger) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnTriggerStay"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),trigger->getOwnerObject());
		}
	}
	void CCharacterController::OnTriggerLeave(CPhysicsTrigger* trigger) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnTriggerLeave"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), trigger->getOwnerObject());
		}
	}

	void CCharacterController::OnActorStartTouch(CPhysicsActor* actor){
	
		//luabind::object componentState = getOwnerObject()->getTemplateObject();
		//if(componentState) {
		//	luabind::object CallBack = componentState["OnActorEnter"];
		//	if(CallBack)
		//		luabind::call_function<void>(CallBack,this->getOwnerObject(),actor);
		//}
		
	}

	void CCharacterController::OnActorTouch(CPhysicsActor* actor){
		//callLuaFunction("OnActorStay");

		//luabind::object componentState = getOwnerObject()->getTemplateObject();
		//if(componentState) {
		//	luabind::object CallBack = componentState["OnActorStay"];
		//	if(CallBack)
		//		luabind::call_function<void>(CallBack,this->getOwnerObject(),actor);
		//}

		//CAnimation* anim = static_cast<CAnimation*>(actor->getOwnerObject()->getComponent("CAnimation"));

		//if(anim) {
			//return *comp;
			//mExternalForces =  NxTools::convert( anim->getVelocity() );
			//mExternalForces =  anim->getVelocity();
			//OgreManager::getSingleton().getDebugText()->addText( "mExternalForces " + Ogre::StringConverter::toString(mExternalForces) );
		//}

	}

	void CCharacterController::OnActorEndTouch(CPhysicsActor* actor){
		//callLuaFunction("OnActorLeave");
		
		//CAnimation* anim = static_cast<CAnimation*>(actor->getOwnerObject()->getComponent("CAnimation"));

		//if(anim) {
		//	if(mElevator == anim) {
		//		mExternalForces = Vector3::ZERO;
		//		mElevator = NULL;
		//		mIsOnElevator = false;
		//	}
		//}
		

	}

	void CCharacterController::OnControllerStartTouch(CCharacterController* character) {
		callLuaFunction("OnControllerStartTouch");
	}

	void CCharacterController::OnControllerTouch(CCharacterController* character){
		callLuaFunction("OnControllerTouch");
	}

	void CCharacterController::OnControllerEndTouch(CCharacterController* character){
		callLuaFunction("OnControllerEndTouch");
	}

	//////////////////////////////////////////////////////////////////////////
	// Getting input from user
	
	void CCharacterController::registerEvents() {
		InputManager::getSingleton().eventMouseMoved.attach(this,&CCharacterController::OnMouseMoved);
		InputManager::getSingleton().eventMousePressed.attach(this,&CCharacterController::OnMousePressed);
		InputManager::getSingleton().eventMouseReleased.attach(this,&CCharacterController::OnMouseReleased);
		InputManager::getSingleton().eventKeyPressed.attach(this,&CCharacterController::OnKeyPressed);
		InputManager::getSingleton().eventKeyReleased.attach(this,&CCharacterController::OnKeyReleased);

		GuiManager::getSingleton().eventMouseMovedOverObject.attach(this,&CCharacterController::OnMouseMovedOverObject);
		
		GuiManager::getSingleton().eventMouseMovedEnterOverObject.attach(this,&CCharacterController::OnMouseMovedEnterOverObject);
		GuiManager::getSingleton().eventMouseMovedLeaveOverObject.attach(this,&CCharacterController::OnMouseMovedLeaveOverObject);

		GuiManager::getSingleton().eventMousePressedObject.attach(this,&CCharacterController::OnMousePressedObject);
		GuiManager::getSingleton().eventMouseReleasedObject.attach(this,&CCharacterController::OnMouseReleasedObject);
		
		

		
		
	}

	bool isDirectionalPressed(InputManager* input) {
		bool right = input->getKeyboardObject()->isKeyDown(OIS::KC_D);
		bool left = input->getKeyboardObject()->isKeyDown(OIS::KC_A);
		bool up = input->getKeyboardObject()->isKeyDown(OIS::KC_W);
		bool down = input->getKeyboardObject()->isKeyDown(OIS::KC_S);

		if(right || left || up || down)
			return true;
		else
			return false;
	}

	bool CCharacterController::OnKeyPressed( const OIS::KeyEvent &arg ) {

		//InputManager* input = InputManager::getSingletonPtr();
		//bool isDirPressed = isDirectionalPressed(input);

		if(arg.key == OIS::KC_F4) {
			OgreManager::getSingleton().getDebugText()->toggleFPSWindow();
		}
		
		//if(!isDirPressed)
		//{
			if(arg.key == OIS::KC_W) {
				startWalking(0);
				setWalkState(false);
				eventStartMoving.notify(true);
			}
			if(arg.key == OIS::KC_S) {
				startWalking(0);
				setWalkState(false);
				eventStartMoving.notify(true);
			}
			if(arg.key == OIS::KC_A) {
				startWalking(0);
				setWalkState(false);
				eventStartMoving.notify(true);
			}
			if(arg.key == OIS::KC_D) {
				startWalking(0);
				setWalkState(false);
				eventStartMoving.notify(true);
			}
		//}
			if(arg.key == OIS::KC_LCONTROL) {
				eventStartCrouching.notify(true);
			}
		

		//CppEvent1<void, const bool > eventStartAttack;
		//CppEvent1<void, CPhysicsActor* > eventStartThrow;


		if(arg.key == OIS::KC_SPACE) {
			eventJumped.notify(true);
			startJump(9);
		}
		
		return true;
	}

	bool CCharacterController::OnKeyReleased( const OIS::KeyEvent &arg ) {

		InputManager* input = InputManager::getSingletonPtr();
		
		bool isDirPressed = isDirectionalPressed(input);

		if(arg.key == OIS::KC_W) {
			if(!isDirPressed)
			{
				eventStopMoving.notify(true);
			}
		}

		if(arg.key == OIS::KC_S) {
			if(!isDirPressed)
			{
				eventStopMoving.notify(true);
			}
		}
		if(arg.key == OIS::KC_A) {
			if(!isDirPressed)
			{
				eventStopMoving.notify(true);
			}
		}

		if(arg.key == OIS::KC_D) {
			if(!isDirPressed)
			{
				eventStopMoving.notify(true);
			}
		}
		
		if(arg.key == OIS::KC_LCONTROL) {
			eventEndCrouching.notify(true);
		}

		if(arg.key == OIS::KC_LSHIFT) {
			//setSpeed(30.0f);
		}

		return true;
	}

	bool CCharacterController::startJump(NxF32 v0)
	{
		if(mJump)	
			return false;

		mIsOnElevator = false;
		mElevator = NULL;

		mJumpTime = 0.0f;
		mV0	= v0;
		mJump = true;

		return true;
	}
	void CCharacterController::startFall(NxF32 v0)
	{
		if(mFall)	return;
		mFallTime = 0.0f;
		mV0	= v0;
		mFall = true;
		//mCAnim->setAnimationState(9); OnStartFalling
		eventStartFalling.notify(true);
	}
	void CCharacterController::stopFall()
	{
		if(!mFall)	return;
		mFall = false;
	}

	void CCharacterController::startWalking(NxF32 v0)
	{
		if(mWalk)	return;
		//mWalkTime = 0.0f;
		mV0	= v0;
		mWalk = true;
	}
	void CCharacterController::stopWalking()
	{
		if(!mWalk)	return;
		mWalk = false;
	}
	void CCharacterController::stopJump()
	{
		if(!mJump)	return;
		mJump = false;
	}

	NxF32 CCharacterController::getJumpHeight(NxF32 elapsedTime)
	{

		if(mJump) {
			mJumpTime += elapsedTime * mDesc.jumpStrength;
			NxF32 h = G*mJumpTime*mJumpTime + mV0*mJumpTime;
			NxF32 height = (h - mDesc.gravity.y)*elapsedTime;
			return height;
		} else {
			return -0.1f;
		}

	}

	NxF32 CCharacterController::getFallHeight(NxF32 elapsedTime)
	{
		if(mJump)
			return -0.1f;
	
		if(mFall) {
			mFallTime += elapsedTime * mDesc.jumpStrength;
			NxF32 h = G*mFallTime*mFallTime - mV0*mFallTime;
			NxF32 height = (h - mDesc.gravity.y)*elapsedTime;
			if(height > 0)
				return -0.1;

			return height;
		} else {
			return -0.1;
		}
	}

	bool CCharacterController::loadSettings() { //std::string characterFileName

		if(mDesc.resourceFileName != "") {
			std::string mFilePath = "../Media/Characters/" + mDesc.resourceFileName + ".xml";
			
			XMLNode xMainNode;

			try {
				xMainNode=XMLNode::openFileHelper(mFilePath.c_str(),"Nebula_Engine"); //,"PMML"

			} catch(...) {
				//Ogre::LogManager::getSingleton().logMessage("*** Error loading character file ***");
				return false;
			}
			
			XMLNode xNode=xMainNode.getChildNode("Character");

			try {
				mDesc.speed = Ogre::StringConverter::parseReal(xNode.getAttribute("mSpeed"));
				mDesc.acceleration = Ogre::StringConverter::parseReal(xNode.getAttribute("mAcceleration"));
				mDesc.initialRadius = Ogre::StringConverter::parseReal(xNode.getAttribute("mInitialRadius"));
				mDesc.initialHeight = Ogre::StringConverter::parseReal(xNode.getAttribute("mInitialHeight"));
				mDesc.scale = Ogre::StringConverter::parseReal(xNode.getAttribute("mScale"));
				mDesc.skinWidth = Ogre::StringConverter::parseReal(xNode.getAttribute("mSkinwidth"));
				mDesc.jumpStrength = Ogre::StringConverter::parseReal(xNode.getAttribute("mJumpStrength"));
				mDesc.turnReactionSpeed = Ogre::StringConverter::parseReal(xNode.getAttribute("mTurnReactionSpeed"));
				mDesc.timestepMultiplier = Ogre::StringConverter::parseReal(xNode.getAttribute("mTimestepMultiplier"));
				mDesc.speedMultiplier = Ogre::StringConverter::parseReal(xNode.getAttribute("mSpeedMultiplier"));
				
				//Ogre::Real g 
				G = Ogre::StringConverter::parseReal(xNode.getAttribute("mGravity"));
				mDesc.gravity = Vector3(0, G,0);

			} catch (...) {
				Ogre::LogManager::getSingleton().logMessage("*** Error loading ApeScene data from Character map file ***");
				return false;
			}

		}
		return true;
	}

	Real CCharacterController::getTurnReactionSpeed() {
		return mDesc.turnReactionSpeed;
	}

	//float getElapsedTime()
	//{
	//	static LARGE_INTEGER previousTime;
	//	static LARGE_INTEGER freq;
	//	static bool init = false;
	//	if(!init){
	//		QueryPerformanceFrequency(&freq);
	//		QueryPerformanceCounter(&previousTime);
	//		init=true;
	//	}
	//	LARGE_INTEGER currentTime;
	//	QueryPerformanceCounter(&currentTime);
	//	unsigned long long elapsedTime = currentTime.QuadPart - previousTime.QuadPart;
	//	previousTime = currentTime;
	//	return (float)(elapsedTime)/(freq.QuadPart);
	//}

	void CCharacterController::createControllerManager(NxUserAllocator* a)
	{
		mManager = NxCreateControllerManager(a);
	}

	void CCharacterController::releaseControllerManager()
	{
		NxReleaseControllerManager(mManager);
	}

	void CCharacterController::updateControllers()
	{
		mManager->updateControllers();
	}

	NxController* CCharacterController::initCharacterControllers(const NxVec3 startPos, NxReal scale, NxScene& scene)
	{
		NxCapsuleControllerDesc desc;
		NxVec3 tmp			= startPos;
		desc.position.x		= tmp.x;
		desc.position.y		= tmp.y;
		desc.position.z		= tmp.z;
		desc.radius			= mDesc.initialRadius * mDesc.scale;
		desc.height			= mDesc.initialHeight * mDesc.scale;
		desc.upDirection	= NX_Y;
		//		desc.slopeLimit		= cosf(NxMath::degToRad(45.0f));

		//Limiting the slopes
		desc.slopeLimit		= cosf(NxMath::degToRad(60.0f));
		desc.skinWidth		= mDesc.skinWidth;
		desc.stepOffset		= 1.5;
		//desc.stepOffset		= mDesc.initialRadius * 0.5 * mDesc.scale;
		//	desc.stepOffset	= 0.01f;
		//		desc.stepOffset		= 0;	// Fixes some issues
		//		desc.stepOffset		= 10;
		desc.callback		= this; //&gControllerHitReport;
		
		//desc.callback = PhysicsManager::getSingletonPtr();

		NxController* c = mManager->createController(&scene, desc);
		c->setCollision(true);
		
		NxActor* mActor = c->getActor(); 
		mActor->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);			

		//mActor->userData = (void*)getOwnerObject();
		mActor->userData = this; //(void*)

		NxShape* characterShape = getCharacterActor(0)->getShapes()[0];
		characterShape->setFlag(NX_SF_DYNAMIC_DYNAMIC_CCD, true);

		return mManager->getController(0);
	}

	void CCharacterController::releaseCharacterControllers(NxScene& scene)
	{
		mManager->purgeControllers();
	}

	const NxVec3& CCharacterController::getCharacterPos() //NxU32 characterIndex
	{
		NxExtendedVec3 pos = mManager->getController(0)->getFilteredPosition();
		return NxVec3(pos.x,pos.y,pos.z);
	}

	NxActor* CCharacterController::getCharacterActor(NxU32 characterIndex)
	{
		return mManager->getController(characterIndex)->getActor();
	}

	bool CCharacterController::resetCharacterPos(NxU32 index, const NxVec3& pos)
	{
		return mManager->getController(index)->setPosition(NxExtendedVec3(pos.x, pos.y, pos.z));
	}

	bool CCharacterController::updateCharacterExtents(NxU32 index, bool& increase)
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

	void CCharacterController::update() {

		const OIS::MouseState &ms = InputManager::getSingleton().getMouseObject()->getMouseState(); // getMouseStat();

		Real elapsedTime = OgreManager::getSingleton().getTimeSinceLastFrame();

		Vector3 _NextMovement = Vector3::ZERO;
		Ogre::Quaternion _Direction = Ogre::Quaternion::IDENTITY;

		InputManager* input = InputManager::getSingletonPtr();

		Ogre::Quaternion q;
		
		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

		//////////////////////////////////////////////////////////////////////////
		//Straight movements

		//Up
		if(input->getKeyboardObject()->isKeyDown(OIS::KC_W))
		{
			q = Ogre::Quaternion::IDENTITY;
			_NextMovement.z = 1;
		}
		//Down
		if(input->getKeyboardObject()->isKeyDown(OIS::KC_S))
		{
			q = Quaternion(Degree(180), Ogre::Vector3::UNIT_Y);
			_NextMovement.z = -1;
		}
		//Right
		if(input->getKeyboardObject()->isKeyDown(OIS::KC_D))
		{
			q = Quaternion(Degree(90), Ogre::Vector3::NEGATIVE_UNIT_Y);
			_NextMovement.x = -1;
		}
		//Left
		if(input->getKeyboardObject()->isKeyDown(OIS::KC_A))
		{
			q = Quaternion(Degree(90), Ogre::Vector3::UNIT_Y);
			_NextMovement.x = 1;
		}

		//////////////////////////////////////////////////////////////////////////
		//Diagonal movements
		
		//Up-Left
		if(input->getKeyboardObject()->isKeyDown(OIS::KC_W) && input->getKeyboardObject()->isKeyDown(OIS::KC_A))
		{
			q = Quaternion(Degree(45), Ogre::Vector3::UNIT_Y);
			_NextMovement.z = 1;
			_NextMovement.x = 1;
		}
		//Down-Left
		if(input->getKeyboardObject()->isKeyDown(OIS::KC_S) && input->getKeyboardObject()->isKeyDown(OIS::KC_A))
		{
			q = Quaternion(Degree(135), Ogre::Vector3::UNIT_Y);
			_NextMovement.z = -1;
			_NextMovement.x = 1;
		}
		//Down-Right
		if(input->getKeyboardObject()->isKeyDown(OIS::KC_S) && input->getKeyboardObject()->isKeyDown(OIS::KC_D))
		{
			q = Quaternion(Degree(135), Ogre::Vector3::NEGATIVE_UNIT_Y);
			_NextMovement.z = -1;
			_NextMovement.x = -1;
		}
		//Up-Right
		if(input->getKeyboardObject()->isKeyDown(OIS::KC_W) && input->getKeyboardObject()->isKeyDown(OIS::KC_D))
		{
			q = Quaternion(Degree(45), Ogre::Vector3::NEGATIVE_UNIT_Y);
			_NextMovement.z = 1;
			_NextMovement.x = -1;
		}

		if(input->getKeyboardObject()->isKeyDown(OIS::KC_LCONTROL)) {
			eventCrouching.notify(true);
		}

		if(_NextMovement.x == 0 && _NextMovement.z == 0) // || _NextMovement.z == 0
		{
			setWalkState(true);
		}
		else
		{
			enableMotion(true);
			setDisplacement(_NextMovement);
			setDirection(_Direction);
			
			if(render)
				render->setNextOrientation(q);
		}

		updateCharacter();
		if(render) {
			Ogre::Vector3 pos = getCharacterPosOgre();
			render->getNode()->setPosition(pos);
		}
	}

	void CCharacterController::setup() {
		
		mIsOnElevator = false;
		mPause = false;
		mApplyGravity = true;
		mMotion			= false;	
		mManager = NULL;
		mJump =  false;
		mV0 = 0.0f;
		mJumpTime = 0.0f;
		mWalk = false;
		mFall = false;
		mWalkTime = 0;
		mFallTime = 0;
		mStopWalk = false;
		mIsTouchingFloor = false;

		mIsFalling = true;
		//startJump(0);

		registerEvents();
		loadSettings();
		
		CPosition *pos = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
		COrientation *orient = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));

		createControllerManager(mMyAllocator); 
		NxVec3 initialPos = NxTools::convert(static_cast<Vector3>(*pos));
		initCharacterControllers( initialPos, 1, *mScene);

	}

	void CCharacterController::setPosition(Vector3 pos) {
		mManager->getController(0)->setPosition(NxExtendedVec3(pos.x, pos.y, pos.z));
	}

	void CCharacterController::setWalkState(bool state) {
		mStopWalk = state;
	}

	Ogre::Real CCharacterController::getVelocity() {
		return 0;
	}

	NxF32 CCharacterController::rayHitDistance(Vector3 cpos, Vector3 dir)
	{
		
		NxShape* characterShape = getCharacterActor(0)->getShapes()[0];

		NxRay worldRay;
		worldRay.orig = NxTools::convert(cpos);
		worldRay.dir	= NxTools::convert(dir);

		NxRaycastHit hit;
		characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, true);
		NxShape* shape = mScene->raycastClosestShape(worldRay, NX_ALL_SHAPES, hit);
		characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, false);

		if(!mPause)	
			mWorldRay = worldRay;

		//if(shape) {
		//		CPhysicsActor* actor = (CPhysicsActor*)(shape->getActor().userData);
		//		if(actor) {
		//			CAnimation* anim = static_cast<CAnimation*>(actor->getOwnerObject()->getComponent("CAnimation"));
		//			if(anim) {
		//				mElevator = anim; 
		//				mIsOnElevator = true;
		//			}
		//		}
		//}

		return shape ? hit.distance : 0; //NX_MAX_F32
	}

	NxF32 CCharacterController::rayHitGroundDistance()
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

		return shape ? hit.distance : 0;
	}

	void CCharacterController::setDisplacement(Ogre::Vector3 dispVector) {
		mNextMovement = dispVector;
	}
	Ogre::Vector3 CCharacterController::getDisplacement() {
		return mNextMovement;
	}

	void CCharacterController::setDirection(Ogre::Quaternion orientation) {
		mDirection = orientation;
	}
	Ogre::Quaternion CCharacterController::getDirection() {
		return mDirection;
	}
	void CCharacterController::enableMotion(bool _motion) {
			mMotion = _motion;
	}
	void CCharacterController::enableRotation(bool _rotation) {
		mRotating = _rotation;
	}
	bool CCharacterController::isRotating() {
		return mRotating;
	}
	bool CCharacterController::isMoving() {
		return mMotion;
	}
	
	void CCharacterController::addExternalForce(Vector3 force) {
			mExternalForces = force;
	}

	void CCharacterController::updateCharacter() {
		
		float elapsedTime = OgreManager::getSingleton().getTimeSinceLastFrame();
		NxVec3 disp = NxVec3(0,0,0);
		NxVec3 horizontalDisp = NxVec3(0,0,0);

		Real mJumpMovementForce = 0.8f;

		if(!mStopWalk)
			mWalkTime += elapsedTime * mDesc.acceleration; //acc
		else
			mWalkTime -= elapsedTime * mDesc.acceleration;

		int maxSpeed = 1;

		if(mWalkTime >= maxSpeed) {
			mWalkTime = maxSpeed;
		}

		if(mWalkTime <= 0) {
			mWalkTime = 0;
			mMotion = false;
		}
		
/*		mOgre->getDebugText()->addText("mNextMovement = " + Ogre::StringConverter::toString(mNextMovement));	
		mOgre->getDebugText()->addText("mWalkTime = " + Ogre::StringConverter::toString(mWalkTime));*/	

		Ogre::Vector3 tmpPos = (mDirection * (mNextMovement) ); // + mExternalForces 
		horizontalDisp = NxTools::convert(tmpPos);
		disp += horizontalDisp * (mDesc.speed * mWalkTime);

		disp = (disp ) * elapsedTime;

		NxF32 heightDelta;
		//mFallTime += elapsedTime * mDesc.jumpStrength;

		if(mJump) {
			heightDelta = getJumpHeight(elapsedTime);
			if(heightDelta!=0.0f) {
				disp.y+=heightDelta;
			}
			if(heightDelta < 0)
				mIsFalling = true;
		
		} else {
			//if(!mIsTouchingFloor) {
				heightDelta = getFallHeight(elapsedTime);
				if(heightDelta!=0.0f) {
					disp.y+=heightDelta;
				}
			//}
		}

		NxF32 sharpness = 1.0f;
		NxU32 collisionFlags;
		NxController* c = mManager->getController(0);
		
		//disp.z = 0;

		//OgreManager::getSingleton().getDebugText()->addText( Ogre::StringConverter::toString(Vector3(disp.x,disp.y,disp.z)) );
		//OgreManager::getSingleton().getDebugText()->addText( "isFalling() " + Ogre::StringConverter::toString(isFalling()) );
		//OgreManager::getSingleton().getDebugText()->addText( "isMoving() " + Ogre::StringConverter::toString(isMoving()) );
		//OgreManager::getSingleton().getDebugText()->addText( "isRotating() " + Ogre::StringConverter::toString(isRotating()) );
		
		//OgreManager::getSingleton().getDebugText()->addText( "mIsOverObject " + Ogre::StringConverter::toString(mIsOverObject) );
		
		mIsTouchingFloor = false;
		mIsTouchingCeiling = false;
		mIsTouchingSides = false;

		NxF32 d = rayHitDistance(getCharacterPosOgre(),Vector3(0,-1,0));

		OgreManager::getSingleton().getDebugText()->addText( "floot: " + Ogre::StringConverter::toString(d) );

		if(mIsOnElevator) {
			disp.y = 0;
			if(mElevator) {
				Ogre::Real h = mElevator->getVelocity().y;
				disp.y = h;
			}
		}

		c->move(disp, 1, 0.000001f, collisionFlags, sharpness);
		
		mIsOnAir = true;

		if(collisionFlags & NXCC_COLLISION_SIDES) {
			//OgreManager::getSingleton().getDebugText()->addText( "NXCC_COLLISION_SIDES: yep..." );
			stopJump();
			//mIsOverObject = false;
			mIsTouchingSides = true;
			mIsOnAir = false;
		}

		if(collisionFlags & NXCC_COLLISION_UP) {
			//OgreManager::getSingleton().getDebugText()->addText( "NXCC_COLLISION_UP: yep..." );
			stopJump();
			//mIsOverObject = false;
			mIsTouchingCeiling = true;
			mIsOnAir = false;
		}

		if(collisionFlags & NXCC_COLLISION_DOWN) {
			stopJump();
			stopFall();
			mIsTouchingFloor = true;
			mIsOnAir = false;
			if(mIsFalling) {
				eventHitGround.notify(true);
				mWalkTime = 0;
				mIsFalling = false;
			}
		}

		if(!(collisionFlags & NXCC_COLLISION_DOWN)) {
			if(!mJump && !mIsOnElevator) { //&& mIsFalling  && !mIsOnElevator
				startFall(0);
				mIsFalling = true;
			} else {
				if(mIsFalling) {
					eventStartFalling.notify(true);
				}
			}
		} else {
			mIsFalling = false;
		}
		
		updateControllers();

	}

	bool CCharacterController::isFalling() {
		return mIsFalling;
	}
	bool CCharacterController::isOnAir() {
		return mIsOnAir;
	}
	
	//bool CCharacterController::isOverObject() {
	//	return mIsOverObject;
	//}

	bool CCharacterController::isTouchingFloor() {
		return mIsTouchingFloor;
	}

	bool CCharacterController::isTouchingCeiling() {
		return mIsTouchingCeiling;
	}

	bool CCharacterController::isTouchingSides() {
		return mIsTouchingSides;
	}


	Ogre::Vector3 CCharacterController::getCharacterPosOgre() {

		NxVec3 pos = getCharacterPos();
		return Ogre::Vector3(pos.x,pos.y,pos.z);
	}

	void CCharacterController::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
