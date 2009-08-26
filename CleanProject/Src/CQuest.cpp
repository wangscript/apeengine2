#include "CQuest.h"

namespace Nebula {
	CQuest::CQuest()
	{
		mComponentID = "CQuest";
	}

	CQuest::CQuest(const CQuestDesc& desc)
	{
		mComponentID = "CQuest";
		mDesc = desc;
	}

	CQuest::~CQuest()
	{

	}

	void CQuest::update() {

	}

	void CQuest::setup() {
		
	}

	void CQuest::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
