#include "CEventZone.h"

namespace Nebula {
	CEventZone::CEventZone()
	{
		mComponentID = "CEventZone";
	}

	CEventZone::CEventZone(const CEventZoneDesc& desc)
	{
		mComponentID = "CEventZone";
		mDesc = desc;
	}

	CEventZone::~CEventZone()
	{

	}

	void CEventZone::update() {

	}

	void CEventZone::setup() {
		
	}

	void CEventZone::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
