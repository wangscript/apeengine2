#include "CRoom.h"

namespace Nebula {
	CRoom::CRoom()
	{
		mComponentID = "CRoom";
	}

	CRoom::CRoom(const CRoomDesc& desc)
	{
		mComponentID = "CRoom";
		mDesc = desc;
	}

	CRoom::~CRoom()
	{

	}

	void CRoom::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}
	
	void CRoom::toggleLights(bool val) {
		isLightOn = val;
	}

	void CRoom::update() {

	}

	void CRoom::setup() {
		//CMesh *mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
		//if(mesh) {
		//	mesh->getEntity()->setVisible(false);
		//}
		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		if(render) {
			render->getNode()->setVisible(false);
		}

	}

} //end namespace

