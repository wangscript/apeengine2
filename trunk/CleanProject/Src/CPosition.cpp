#include "CPosition.h"

namespace Nebula {
	CPosition::CPosition()
	{
		mComponentID = "CPosition";
	}

	CPosition::CPosition(const CPositionDesc& desc) : Ogre::Vector3(Ogre::Vector3::ZERO)
	{
		mComponentID = "CPosition";
		mDesc = desc;
	}

	CPosition::~CPosition()
	{

	}

	void CPosition::update() {

	}

	void CPosition::setup() {
		
	}

	void CPosition::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
