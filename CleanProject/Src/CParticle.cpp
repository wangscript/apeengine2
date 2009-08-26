#include "CParticle.h"

namespace Nebula {
	CParticle::CParticle()
	{
		mComponentID = "CParticle";
	}

	CParticle::CParticle(const CParticleDesc& desc)
	{
		mComponentID = "CParticle";
		mDesc = desc;

		mParticle = ParticleManager::getSingleton().getParticleManager()->createParticleSystem(mDesc.name,mDesc.particleScriptName,OgreManager::getSingleton().getSceneManager());

	}

	CParticle::~CParticle()
	{

	}

	void CParticle::update() {
//		mParticle->_update(OgreManager::getSingleton().getTimeSinceLastFrame());
	}

	void CParticle::setup() {
		CRender* render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	
		if(render)
			render->getNode()->attachObject(mParticle);
	
		mParticle->start();
		
		
	}

	void CParticle::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
