#include "CCharacterAnimation.h"

namespace Nebula {

	CCharacterAnimation::CCharacterAnimation(const CCharacterAnimationDesc& desc)
	{
		mComponentID = "CCharacterAnimation";
		mDesc = desc;

		//mIsHoldingItem = false;
		//mHasItemHolderBone = false;

		//mItemHolderBone = NULL;
		//mItemAttached = NULL;

		//mOffsetItemPosition = Vector3::ZERO;
		//mOffsetItemOrientation = Quaternion::IDENTITY;

	}

	CCharacterAnimation::~CCharacterAnimation()
	{
		//callLuaFunction("Exit");
		//callLuaFunction("OnComponentDestroy");
	}

	void CCharacterAnimation::addItemHolderBone(std::string boneName) {
		CMesh* mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));

		if(mesh) {
			Ogre::Bone* bone = mesh->getEntity()->getSkeleton()->getBone(boneName);
			if(bone) {
				//mItemHolderBone = bone;
				//mHasItemHolderBone = true;

				ItemHolderBone holder;
				holder.bone = bone;
				holder.boneName = boneName;
				holder.isHoldingItem = false;
				holder.isItem = false;
				holder.isWeapon = false;
				holder.itemName = "";
				holder.object = NULL;

				mItemHolderBones[boneName] = holder;

			}
		}
	}
    
	GameObject* CCharacterAnimation::getObjectAttachedToBone(std::string bone) {
		if(!mItemHolderBones.empty()) {
			if(mItemHolderBones[bone].object) {
				return mItemHolderBones[bone].object;
			}
		}
	}

	void CCharacterAnimation::attachItemToBone(std::string boneName, GameObject* object) {
		if(object && !mItemHolderBones.empty()) {

			//if(mItemHolderBones[boneName]) {
				
				mItemHolderBones[boneName].isHoldingItem = false;
				mItemHolderBones[boneName].isItem = false;
				mItemHolderBones[boneName].isWeapon = false;
				mItemHolderBones[boneName].itemName = object->getID();
				mItemHolderBones[boneName].object = object;

				// Billboard
				//CMesh* mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
				//mBillBoardSet = OgreManager::getSingleton().getSceneManager()->createBillboardSet("b1");
				//mBillBoardSet->setDefaultDimensions(0.25, 1.25);
				//mBillBoardSet->setMaterialName("Examples/Flare");
				//mBillBoardSet->createBillboard(0,0,0, ColourValue::Green);
				//mTagPoint = mesh->getEntity()->attachObjectToBone(boneName, mBillBoardSet);
				//// Trail
				//RibbonTrail* trail = OgreManager::getSingleton().getSceneManager()->createRibbonTrail("rib");
				//trail->setMaterialName("Examples/LightRibbonTrail");
				//trail->setTrailLength(10);
				//trail->setMaxChainElements(40);
				//trail->setInitialColour(0, 0.2, 1.0, 0.3);
				//trail->setColourChange(0, 0.5, 0.5, 0.5, 0.5);
				//trail->setInitialWidth(0, 0.1);
				//trail->addNode(mTagPoint);
				////OgreManager::getSingleton().getSceneManager()->getRootSceneNode()->attachObject(trail);
				//CRender *render = dynamic_cast<CRender*>(object->getComponent("CRender"));
				//if(render) {
				//	render->getNode()->attachObject(trail);
				//}

				CPhysicsActor *actor = dynamic_cast<CPhysicsActor*>(object->getComponent("CPhysicsActor"));
				if(actor) {
					actor->getNxActor()->raiseBodyFlag(NX_BF_KINEMATIC);
					actor->getNxActor()->raiseActorFlag(NX_AF_DISABLE_COLLISION);

				}

				CWeapon *weapon = dynamic_cast<CWeapon*>(object->getComponent("CWeapon"));
				if(weapon) {
					mItemHolderBones[boneName].isWeapon = true;
					mItemHolderBones[boneName].isHoldingItem = true;
				} else {
					CItem *item = dynamic_cast<CItem*>(object->getComponent("CItem"));
					if(item) {
						mItemHolderBones[boneName].isItem = true;
						mItemHolderBones[boneName].isHoldingItem = true;
					}
				}


			//}

		}
	}

	void CCharacterAnimation::detachItemFromBone(GameObject* object) {
		if(object && !mItemHolderBones.empty()) {
			std::string boneName = getBoneAttachedToObject(object);
			if(boneName != "") {
				CPhysicsActor *actor = dynamic_cast<CPhysicsActor*>(object->getComponent("CPhysicsActor"));
				//CCharacterController* character = dynamic_cast<CPhysicsActor*>(getOwnerObject()->getComponent("CPhysicsActor"));
				CRender* render = dynamic_cast<CRender*>(object->getComponent("CRender"));
				CMesh* characterMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));

				if(render && actor && characterMesh) {
					Vector3 worldPosition = OgreManager::getSingleton().getBoneWorldPosition(characterMesh->getEntity(),mItemHolderBones[boneName].bone);
					Quaternion worldOrientation = OgreManager::getSingleton().getBoneWorldOrientation(characterMesh->getEntity(),mItemHolderBones[boneName].bone);
					
					render->getNode()->setOrientation( worldOrientation );
					render->getNode()->setPosition( worldPosition );

					actor->getNxActor()->setGlobalPosition( NxTools::convert(worldPosition) );
					actor->getNxActor()->setGlobalOrientationQuat( NxTools::convert(worldOrientation) );

					actor->getNxActor()->clearBodyFlag(NX_BF_KINEMATIC);
					actor->getNxActor()->clearActorFlag(NX_AF_DISABLE_COLLISION);

				}

				mItemHolderBones[boneName].isHoldingItem = false;
				mItemHolderBones[boneName].isItem = false;
				mItemHolderBones[boneName].isWeapon = false;
				mItemHolderBones[boneName].itemName = "";
				mItemHolderBones[boneName].object = NULL; 

			}
		}
	}

	std::string CCharacterAnimation::getBoneAttachedToObject(GameObject* object) {
		if(object && !mItemHolderBones.empty()) {
			std::map<const std::string, ItemHolderBone>::iterator boneIter;
			for(boneIter = mItemHolderBones.begin(); boneIter != mItemHolderBones.end(); boneIter++) {
				if(boneIter->second.object->getID() == object->getID()) {
					return boneIter->second.boneName;
				}
			}
		}
		return "";
	}

	void CCharacterAnimation::updateAttachedItems() {

		CRender *characterRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		CMesh *characterMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));

		std::map<const std::string, ItemHolderBone>::iterator boneIter;
		for(boneIter = mItemHolderBones.begin(); boneIter != mItemHolderBones.end(); boneIter++) {

			//CPhysicsActor *objectActor = dynamic_cast<CPhysicsActor*>(boneIter->second.object->getComponent("CPhysicsActor"));
			CRender *objectRender = NULL;
			if(boneIter->second.object)
				objectRender = dynamic_cast<CRender*>(boneIter->second.object->getComponent("CRender"));
			
			if(objectRender) {
				
				Ogre::Bone* bone = boneIter->second.bone;

				Vector3 bonePos = bone->_getDerivedPosition();
				Quaternion boneOrient = bone->_getDerivedOrientation();

				//Force animation and node updates to prevent lag
				characterMesh->getEntity()->_updateAnimation();
				characterRender->getNode()->_update(true, true);

				Vector3 worldPosition = OgreManager::getSingleton().getBoneWorldPosition(characterMesh->getEntity(),bone);
				Quaternion worldOrientation = OgreManager::getSingleton().getBoneWorldOrientation(characterMesh->getEntity(),bone);

				objectRender->getNode()->setPosition( worldPosition ); //+ (boneOrient * mOffsetItemPosition)
				objectRender->getNode()->setOrientation( worldOrientation ); // * mOffsetItemOrientation boneOrient
				
				//actor->getNxActor()->moveGlobalPosition( NxTools::convert(wPos) );
				//actor->getNxActor()->moveGlobalOrientationQuat( NxTools::convert(boneOrient) );

				//OgreManager::getSingleton().getDebugText()->addText( getOwnerObject()->getID() + " - bonePos: " + Ogre::StringConverter::toString(wPos) );
			}

		}

	}

	void CCharacterAnimation::setBindings() {

	}

	void CCharacterAnimation::setAnimationState(const float anim) {
		m_frikiState->setValue(anim);
	}
	
	float CCharacterAnimation::getCurrentAnimationState() {
		return 0;
	}
	
	bool CCharacterAnimation::isPlayingAnimation() {
		
		return false;
	}

	void CCharacterAnimation::triggerListener( const tecnofreak::ITrigger* trigger )
	{
		mTriggerFunctors[trigger->getName()].notifyLua();
	}

	void CCharacterAnimation::createLuaTriggerFunctor(const std::string triggerName, const luabind::object& obj) { //const luabind::object obj
		
		LuaTriggerFunctor triggerFunc;
		triggerFunc.setLuaFunction(obj);
		mTriggerFunctors[triggerName] = triggerFunc;
	}

	void CCharacterAnimation::registerEvents() {

		CCharacterController* mChar = dynamic_cast<CCharacterController*>(getOwnerObject()->getComponent("CCharacterController"));

		if(mChar) {
			mChar->eventStartThrow.attach(this,&CCharacterAnimation::OnStartThrow);
			mChar->eventStartAttack.attach(this,&CCharacterAnimation::OnStartAttack);
			mChar->eventStartFalling.attach(this,&CCharacterAnimation::OnStartFalling);
			mChar->eventHitGround.attach(this,&CCharacterAnimation::OnHitGround);
			mChar->eventStartMoving.attach(this,&CCharacterAnimation::OnStartMoving);
			mChar->eventStopMoving.attach(this,&CCharacterAnimation::OnStopMoving);
			mChar->eventMaxSpeedReached.attach(this,&CCharacterAnimation::OnMaxSpeedReached);
			mChar->eventJumped.attach(this,&CCharacterAnimation::OnJumped);
		}

	}

	bool CCharacterAnimation::OnStartFalling( const bool& animState) {
		callLuaFunction("OnStartFalling");
		return true;
	}
	bool CCharacterAnimation::OnHitGround( const bool& animState) {
		callLuaFunction("OnHitGround");
		return true;
	}

	bool CCharacterAnimation::OnStartMoving( const bool& animState) {
		callLuaFunction("OnStartMoving");
		return true;
	}

	bool CCharacterAnimation::OnStopMoving( const bool& animState) {
		callLuaFunction("OnStopMoving");
		return true;
	}
	bool CCharacterAnimation::OnMaxSpeedReached( const bool& animState ) {
		callLuaFunction("OnMaxSpeedReached");
		return true;
	}
	bool CCharacterAnimation::OnJumped( const bool& animState ) {
		callLuaFunction("OnJumped");
		return true;
	}
	
	bool CCharacterAnimation::OnStartThrow( CPhysicsActor* actor ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnStartThrow"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),actor->getOwnerObject()); // this
		}

		return true;
	}

	bool CCharacterAnimation::OnStartAttack( const bool& animState ) {

		callLuaFunction("OnStartAttack");

		return true;
	}

	

	void CCharacterAnimation::update() {
		updateAnimation();
		updateAttachedItems();
	}

	void CCharacterAnimation::setup() {
		
		setBindings();

		setupAnimationSystem();

		registerEvents();
		
	}

	void CCharacterAnimation::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

	void CCharacterAnimation::setupAnimationSystem() {
	
		CMesh* mCMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
		CRender* mCRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

		if(mCMesh && mCRender) {

			m_frikiAnimationSystem = new AnimationSystem( mCMesh->getEntity() );
			m_frikiAnimationSystem->loadAnimationTree( mDesc.diagramFileName,"General" );
			m_frikiAnimationSystem->loadAnimationInfo( mDesc.animationFileName,"General" );

			m_listener = new TriggerFunctor< CCharacterAnimation >( this, &CCharacterAnimation::triggerListener );
			m_frikiAnimationSystem->addSubscriber( m_listener );

			m_frikiState = m_frikiAnimationSystem->getParameter( "Animation State" );

		}
	}

	void CCharacterAnimation::updateAnimation() {
		
		Ogre::Real time = OgreManager::getSingleton().getTimeSinceLastFrame();
		m_frikiAnimationSystem->update( time );
	}

} //end namespace