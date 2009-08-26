#include "CSimpleSound.h"

namespace Nebula {

	CSimpleSound::CSimpleSound(const CSimpleSoundDesc& desc)
	{
		mComponentID = "CSimpleSound";
		mDesc = desc;
	}

	CSimpleSound::~CSimpleSound()
	{

	}

	void CSimpleSound::update() {

	}

	void CSimpleSound::setup() {
		
	}

	void CSimpleSound::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace

