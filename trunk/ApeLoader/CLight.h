#ifndef _CLIGHT_H_
#define _CLIGHT_H_

#include "GameComponent.h"

#include "Ogre.h"
#include "ObjectManager.h"
#include "OgreRender.h"

using namespace Ogre;

class GameComponent;
class ObjectManager;
class OgreRender;

class CLight : public GameComponent {
public:
	CLight();
	CLight(Ogre::Light::LightTypes lightType);
	CLight(Ogre::Light* light);
		
	Ogre::Light *mLight;

	~CLight();

	void update();
	void setup();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
private:
	static const std::string mFamilyID;
	static const std::string mComponentID;

	ObjectManager* mObjMan;
	OgreRender* mOgre;
};

#endif
