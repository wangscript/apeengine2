#include "COrientation.h"

namespace Nebula {

	COrientation::COrientation() : Ogre::Quaternion(Quaternion::IDENTITY)
	{
		mComponentID = "COrientation";
	}

	COrientation::COrientation(const COrientationDesc& desc) : Ogre::Quaternion(Quaternion::IDENTITY)
	{
		mComponentID = "COrientation";
		mDesc = desc;
	}

	COrientation::~COrientation()
	{

	}

	void COrientation::update() {

	}

	void COrientation::setup() {
		
	}

	void COrientation::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
