#include "CPhysicsActor.h"

namespace Nebula {

	CPhysicsActor::CPhysicsActor(const CPhysicsActorDesc& desc)
	{
		mComponentID = "CPhysicsActor";
		//mDesc = desc;
		
		mActor = NULL;
	}

	void CPhysicsActor::OnActorStartTouch(CPhysicsActor* actor) {
		callLuaFunction("OnActorStartTouch");
	}

	void CPhysicsActor::OnActorTouch(CPhysicsActor* actor) {
		callLuaFunction("OnActorTouch");
	}

	void CPhysicsActor::OnActorEndTouch(CPhysicsActor* actor) {
		callLuaFunction("OnActorEndTouch");
	}

	void CPhysicsActor::OnControllerStartTouch(CCharacterController* character) {
		callLuaFunction("OnControllerStartTouch");
	}

	void CPhysicsActor::OnControllerTouch(CCharacterController* character)	{
		callLuaFunction("OnControllerTouch");
	}

	void CPhysicsActor::OnControllerEndTouch(CCharacterController* character) {
		callLuaFunction("OnControllerEndTouch");
	}
	void CPhysicsActor::OnTriggerEnter(CPhysicsTrigger* trigger) {
		callLuaFunction("OnTriggerEnter");
	}

	void CPhysicsActor::OnTriggerStay(CPhysicsTrigger* trigger) {
		callLuaFunction("OnTriggerStay");
	}

	void CPhysicsActor::OnTriggerLeave(CPhysicsTrigger* trigger) {
		callLuaFunction("OnTriggerLeave");
	}

	void CPhysicsActor::update() {
		updateVisualRepresentation();
	}
	
	Real CPhysicsActor::getDistanceToActor(CPhysicsActor* actor) {
		Vector3 actorPos = NxTools::convert(actor->getNxActor()->getGlobalPosition());
		Vector3 thisActorPos = NxTools::convert(this->getNxActor()->getGlobalPosition());

		return thisActorPos.distance(actorPos);
	}

	Real CPhysicsActor::getDistanceToCharacter(CCharacterController* character) {
		Vector3 characterPos = character->getCharacterPosOgre();
		Vector3 thisActorPos = NxTools::convert(this->getNxActor()->getGlobalPosition());

		return thisActorPos.distance(characterPos);
	}

	Real CPhysicsActor::getDistanceToTrigger(CPhysicsTrigger* trigger) {
		Vector3 triggerPos = NxTools::convert(trigger->getNxActor()->getGlobalPosition());
		Vector3 thisActorPos = NxTools::convert(this->getNxActor()->getGlobalPosition());

		return thisActorPos.distance(triggerPos);
	}

	bool CPhysicsActor::OnCharacterMouseMovedOverObject(CCharacterController* character, Ogre::Vector3 position) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMouseMovedOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position);
		}
		return true;
	}

	bool CPhysicsActor::OnCharacterMouseMovedEnterOverObject(CCharacterController* character, Ogre::Vector3 position) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMouseMovedEnterOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position);
		}
		return true;
	}

	bool CPhysicsActor::OnCharacterMouseMovedLeaveOverObject(CCharacterController* character, Ogre::Vector3 position) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMouseMovedLeaveOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position);
		}
		return true;
	}

	bool CPhysicsActor::OnCharacterMousePressedObject(CCharacterController* character, Ogre::Vector3 position, int mouseButton) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMousePressedObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position, mouseButton);
		}
		return true;
	}

	bool CPhysicsActor::OnCharacterMouseReleasedObject(CCharacterController* character, Ogre::Vector3 position, int mouseButton) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMouseReleasedObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position, mouseButton);
		}
		return true;
	}

	bool CPhysicsActor::isKinematic() {
		
		if(mActor) {
			return mActor->readBodyFlag(NX_BF_KINEMATIC);
		}

		return false;
	}
	
	bool CPhysicsActor::isStatic() {
		
		if(mActor) {
			return !mActor->isDynamic();
		}

		return false;
	}
	
	bool CPhysicsActor::isDynamic() {
		
		if(mActor) {
			return mActor->isDynamic();
		}

		return false;
	}

	void CPhysicsActor::updateVisualRepresentation() {
		
		if(!mActor)
			return;

		if(!mActor->isDynamic())
			return;

		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		CAnimation *anim = dynamic_cast<CAnimation*>(getOwnerObject()->getComponent("CAnimation"));

		if(render && !mActor->readBodyFlag(NX_BF_KINEMATIC)) {

			Ogre::SceneNode* node = render->getNode();
			if(node) {
				Ogre::Vector3 pos = NxTools::convert(mActor->getGlobalPosition());
				Ogre::Quaternion orient = NxTools::convert(mActor->getGlobalOrientationQuat());

				node->setPosition(pos);
				node->setOrientation(orient);
			}

		} else if (render && anim && mActor->readBodyFlag(NX_BF_KINEMATIC) ) {
			if(anim->isRunningAnimation()) {

				Ogre::Vector3 pos = render->getNode()->_getDerivedPosition();
				Ogre::Quaternion orient = render->getNode()->_getDerivedOrientation();
				
				mActor->moveGlobalPosition( NxTools::convert(pos) );
				mActor->moveGlobalOrientationQuat( NxTools::convert(orient) );
			}

		}

	}

	void CPhysicsActor::create() {

		if(mDesc.actorDesc.isValid()) {
			mActor = PhysicsManager::getSingleton().getScene()->createActor(mDesc.actorDesc);

			if(mActor) {
				mActor->userData = this;
				//if(mActor->isDynamic())
				//	mActor->raiseBodyFlag(NX_BF_KINEMATIC);
				//CElevator* elevator = static_cast<CElevator*>(getOwnerObject()->getComponent("CElevator"));
				//if(elevator) {
				//	mActor->raiseBodyFlag(NX_BF_KINEMATIC);
				//}
				CRender* render = static_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
				CDoor* door = static_cast<CDoor*>(getOwnerObject()->getComponent("CDoor"));
				CPosition* pos = static_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
				if(door && render) {
					mActor->raiseBodyFlag(NX_BF_KINEMATIC);
					//render->getNode()->setPosition(NxTools::convert(mActor->getGlobalPosition()));
					render->getNode()->setPosition(NxTools::convert(mActor->getGlobalPosition()));

					Vector3 p = static_cast<Ogre::Vector3>(*pos);
					render->getNode()->setPosition( p );

					//render->getNode()->setOrientation(NxTools::convert(mActor->getGlobalOrientationQuat()));

				}
			}

		} else {
			std::string msg = "*** Error with Actor description: " + getOwnerObject()->getID();
			CLog::Get().Write(LOG_APP,msg.c_str());
		}

	}

	void CPhysicsActor::setup() {
		
		//GuiManager::getSingleton().eventCharacterMouseMovedOverObject.attach(this,&CPhysicsActor::OnCharacterMouseMovedOverObject);
		//GuiManager::getSingleton().eventCharacterMouseMovedEnterOverObject.attach(this,&CPhysicsActor::OnCharacterMouseMovedEnterOverObject);
		//GuiManager::getSingleton().eventCharacterMouseMovedLeaveOverObject.attach(this,&CPhysicsActor::OnCharacterMouseMovedLeaveOverObject);
		//GuiManager::getSingleton().eventCharacterMousePressedObject.attach(this,&CPhysicsActor::OnCharacterMousePressedObject);
		//GuiManager::getSingleton().eventCharacterMouseReleasedObject.attach(this,&CPhysicsActor::OnCharacterMouseReleasedObject);


		create();
	}

	CPhysicsActor::~CPhysicsActor() {
		

		
	}

	void CPhysicsActor::callLuaFunction(const std::string func ) {
		GameObject* go = getOwnerObject();
		const std::string templateName = go->getTemplateName();
		if(templateName != "") {
			luabind::object componentState = getOwnerObject()->getTemplateObject();
			if(componentState) {
				luabind::object CallBack = componentState[func];
				if(CallBack)
					luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
			}
		}
	}

} //end namespace
