#ifndef _CPOSITION_H_
#define _CPOSITION_H_

#include "GameComponent.h"
#include "Ogre.h"

using namespace Ogre;

class GameComponent;

class CPosition : public GameComponent {
public:
	
	//static Ogre::Vector3 Position;
	Ogre::Vector3 Position;

	CPosition();
	CPosition(Ogre::Vector3 vec);
	
	~CPosition();

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
};

#endif
