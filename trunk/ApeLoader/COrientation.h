#ifndef _CORIENTATION_H_
#define _CORIENTATION_H_

#include "GameComponent.h"
#include "Ogre.h"

using namespace Ogre;

class GameComponent;

class COrientation : public GameComponent {
public:
	
	Ogre::Quaternion Orientation;

	COrientation();
	COrientation(Ogre::Quaternion q);

	~COrientation();

	void update();
	void setup();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
private:
	static std::string mFamilyID;
	static std::string mComponentID;
};


#endif
