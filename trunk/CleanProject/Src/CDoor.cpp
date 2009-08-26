#include "CDoor.h"

namespace Nebula {
	CDoor::CDoor()
	{
		mComponentID = "CDoor";
	}

	CDoor::CDoor(const CDoorDesc& desc)
	{
		mComponentID = "CDoor";
		mDesc = desc;
	}

	CDoor::~CDoor()
	{

	}

	void CDoor::update() {

	}

	void CDoor::setup() {
		
	}

	void CDoor::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
