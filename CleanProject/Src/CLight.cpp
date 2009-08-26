#include "CLight.h"

namespace Nebula {

	CLight::CLight()
	{
		mComponentID = "CLight";
	}

	CLight::CLight(const CLightDesc& desc)
	{
		mComponentID = "CLight";
		mDesc = desc;
		
		//mLight = 

	}

	CLight::~CLight()
	{

	}

	void CLight::update() {

	}

	void CLight::setup() {
		
		
		mLight = OgreManager::getSingleton().getSceneManager()->createLight(mDesc.name);

		mLight->setType(mDesc.lightType);

		mLight->setAttenuation(mDesc.attenuationRange,mDesc.attenuationConstant,mDesc.attenuationLinear,mDesc.attenuationQuadratic);

		mLight->setDiffuseColour(mDesc.diffuseColour);
		mLight->setSpecularColour(mDesc.specularColour);

		if(mLight->getType() == Ogre::Light::LT_SPOTLIGHT) {
			mLight->setSpotlightInnerAngle(mDesc.innerAngle);
			mLight->setSpotlightOuterAngle(mDesc.outterAngle);
		}

		if(mLight->getType() == Ogre::Light::LT_SPOTLIGHT || mLight->getType() == Ogre::Light::LT_DIRECTIONAL) {
			mLight->setDirection(mDesc.direction);
			//mLight->set
		}
		
		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		if(render) {
			render->getNode()->attachObject(mLight);
			
			CPosition *pos = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
			COrientation *orient = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));
			//CMesh *mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));

			//render->getNode()->setPosition(static_cast<Vector3>(*pos));
			//render->getNode()->setOrientation(static_cast<Quaternion>(*orient));

		}
	}

	void CLight::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace