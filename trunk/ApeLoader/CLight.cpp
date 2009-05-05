#include "CLight.h"

const std::string CLight::mFamilyID = "CLight";
const std::string CLight::mComponentID = "CLight";

CLight::CLight() :	mObjMan(0),
					mOgre(0),
					mLight(0)

{
	mOgre = OgreRender::getSingleton().getSingletonPtr();
	mObjMan = ObjectManager::getSingleton().getSingletonPtr();

	std::string name;
	name = "CLightComponent" + StringConverter::toString(mObjMan->getNextCompIndex());

	mLight = mOgre->getSceneManager()->createLight(name);
	mLight->setType(Light::LT_POINT);
}
CLight::CLight(Ogre::Light::LightTypes lightType)
{
	mOgre = OgreRender::getSingleton().getSingletonPtr();
	mObjMan = ObjectManager::getSingleton().getSingletonPtr();

	std::string name;
	name = "CLightComponent" + StringConverter::toString(mObjMan->getNextCompIndex());

	mLight = mOgre->getSceneManager()->createLight(name);
	mLight->setType(lightType);
	mLight->setDirection(Vector3(0.0f, -0.5f, 1.0f));
}
CLight::CLight(Ogre::Light* light)
{
	mOgre = OgreRender::getSingleton().getSingletonPtr();
	mObjMan = ObjectManager::getSingleton().getSingletonPtr();

	std::string name;
	name = "CLightComponent" + StringConverter::toString(mObjMan->getNextCompIndex());

	mLight = mOgre->getSceneManager()->createLight(name);
	
	Ogre::ColourValue DiffColor = light->getDiffuseColour();
	Ogre::ColourValue specColor = light->getSpecularColour();

	mLight->setType(light->getType());
	mLight->setAttenuation(light->getAttenuationRange(),light->getAttenuationConstant(),light->getAttenuationLinear(),light->getAttenuationQuadric());
	mLight->setDiffuseColour(light->getDiffuseColour());
	mLight->setSpecularColour(light->getSpecularColour());

	if(light->getType() == Ogre::Light::LT_SPOTLIGHT) {
		mLight->setSpotlightInnerAngle(Ogre::Degree(light->getSpotlightInnerAngle()));
		mLight->setSpotlightOuterAngle(Ogre::Degree(light->getSpotlightOuterAngle()));
	}
	
	if(light->getType() == Ogre::Light::LT_SPOTLIGHT || light->getType() == Ogre::Light::LT_DIRECTIONAL) {
		Ogre::Vector3 dir = light->getDirection();
		mLight->setDirection(dir);
	}




	//mLight->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	//mLight->setType(Ogre::Light::LT_SPOTLIGHT);
	//if(mLight->getType() == Ogre::Light::LT_SPOTLIGHT) {
	//	mLight->setSpotlightInnerAngle(Ogre::Degree(75));
	//	mLight->setSpotlightOuterAngle(Ogre::Degree(85));

	//}
	//mLight->setAttenuation(1430, 1, 1, 1); 
	//Ogre::Vector3 dir = light->getDirection();
	//mLight->setDirection(dir);

}

CLight::~CLight()
{
	mOgre->getSceneManager()->destroyLight(mLight);
}

void CLight::update() {

}

void CLight::setup() {
	//This is to keep track of objects, when i cast rays on them, i get the name of the owner
	//std::string objectName;
	//objectName = getOwnerObject()->getID().c_str();

	//mLight->setUserAny( Ogre::Any(objectName) );
	
}
