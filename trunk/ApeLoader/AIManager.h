#ifndef _AIManager_H
#define _AIManager_H

#include "Ogre.h"
#include "OpenSteer/OpenSteerDemo.h" 
#include "OpenSteer/AbstractVehicle.h"

using namespace Ogre;
//using namespace OpenSteer;

class AbstractVehicle;

//class OpenSteerDemo;

class EntityList {
public:
	EntityList() {};


	Ogre::Entity* ent;
	Ogre::SceneNode* node;
	OpenSteer::AbstractVehicle* vehicle;
};

class AIManager : public Ogre::Singleton<AIManager> 
{
public:
	AIManager();
	~AIManager();

	static AIManager& getSingleton(void);
	static AIManager* getSingletonPtr(void);
	
	void addCharacter(Ogre::String name,OpenSteer::AbstractVehicle* pedestrian);

	void initialize (void);

	// main update function: step simulation forward and redraw scene
	void updateSimulationAndRedraw (float currentTime, float elapsedTime);

	void updateVehicles();
	void addVehicle(OpenSteer::AbstractVehicle* v);

	std::vector<EntityList*> mEntList;

private:
	//bool enableAnnotation;
	
	unsigned int mPopulation;


};


#endif
