#ifndef _CAI_H_
#define _CAI_H_

#include "GameComponent.h"
#include "Ogre.h"
//#include "Pedestrian.h"

#include "OpenSteer/SimpleVehicle.h"

using namespace Ogre;

class GameComponent;

class CAI : public GameComponent { //, public Pedestrian
public:
	
	Ogre::SceneNode* mNode;
	OpenSteer::AbstractVehicle* mPedestrian;

	//static Ogre::Vector3 Position;
	//Ogre::Vector3 Position;

	//CAI(Pedestrian*); //ProximityDatabase& pd
	CAI(OpenSteer::AbstractVehicle*);
	

	//CAI(Ogre::Vector3 vec);
	void updateVehicle();

	~CAI();

	void setDefaultAnimation();
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
