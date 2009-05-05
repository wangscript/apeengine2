#ifndef _CPARTICLE_H_
#define _CPARTICLE_H_

#include "GameComponent.h"
#include "Ogre.h"

#include "CMesh.h"
#include "CRender.h"

#include "ParticleUniverseSystem.h"
#include "ParticleUniverseSystemManager.h"

//class CMesh:
class GameComponent;
class CMesh;
class CRender;

using namespace Ogre;

class CParticle : public GameComponent {
public:
	CParticle(std::string particleScriptName, std::string particleNodeName);
	~CParticle();

	void update();
	void setup();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}

private:
	
	Ogre::String mParticleName;

	ParticleUniverse::ParticleSystem* mParticle;

	static const std::string mFamilyID;
	static const std::string mComponentID;
};

#endif
