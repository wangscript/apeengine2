#include "CElevator.h"

namespace Nebula {
	CElevator::CElevator()
	{
		mComponentID = "CElevator";
	}

	CElevator::CElevator(const CElevatorDesc& desc)
	{
		mComponentID = "CElevator";
		mDesc = desc;
	}

	CElevator::~CElevator()
	{

	}

	void CElevator::update() {

	}

	void CElevator::setup() {
		
	}

	void CElevator::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
