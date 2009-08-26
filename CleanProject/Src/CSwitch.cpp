#include "CSwitch.h"

namespace Nebula {
	CSwitch::CSwitch()
	{
		mComponentID = "CSwitch";
	}

	CSwitch::CSwitch(const CSwitchDesc& desc)
	{
		mComponentID = "CSwitch";
		mDesc = desc;
	}

	CSwitch::~CSwitch()
	{

	}

	void CSwitch::update() {

	}

	void CSwitch::setup() {
		
	}

	void CSwitch::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
