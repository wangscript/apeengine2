#include "CPhysicsTrigger.h"

namespace Nebula {
	CPhysicsTrigger::CPhysicsTrigger()
	{
		mComponentID = "CPhysicsTrigger";
	}

	CPhysicsTrigger::CPhysicsTrigger(const CPhysicsTriggerDesc& desc)
	{
		mComponentID = "CPhysicsTrigger";
		mDesc = desc;



	}

	CPhysicsTrigger::~CPhysicsTrigger()
	{

	}

	void CPhysicsTrigger::OnActorEnter(CPhysicsActor* actor){
		//callLuaFunction("OnActorEnter");
	}
	void CPhysicsTrigger::OnActorStay(CPhysicsActor* actor){
		//callLuaFunction("OnActorStay");
	}
	void CPhysicsTrigger::OnActorLeave(CPhysicsActor* actor){
		//callLuaFunction("OnActorLeave");
	}
	void CPhysicsTrigger::OnControllerEnter(CCharacterController* character) {
		//callLuaFunction("OnControllerEnter");
	}
	void CPhysicsTrigger::OnControllerStay(CCharacterController* character){
		//callLuaFunction("OnControllerStay");
	}
	void CPhysicsTrigger::OnControllerLeave(CCharacterController* character){
		//callLuaFunction("OnControllerLeave");
	}

	void CPhysicsTrigger::update() {

	}

	void CPhysicsTrigger::setup() {
		create();
	}

	void CPhysicsTrigger::create() {

		if(mDesc.actorDesc.isValid()) {
			mActor = PhysicsManager::getSingleton().getScene()->createActor(mDesc.actorDesc);
			
			if(mActor) {
				mActor->userData = this;
			}

		} else {
			std::string msg = "*** Error with Actor description: " + getOwnerObject()->getID();
			CLog::Get().Write(LOG_APP,msg.c_str());
		}

	}

	void CPhysicsTrigger::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
