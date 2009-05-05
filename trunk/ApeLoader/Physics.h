#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "NxOgre.h"
#include "Ogre.h"
//#include "EditableTerrain.h"
//#include "Receiver.h"
//#include "NxScene.h"
//#include "UserAllocator.h"
//#include "ErrorStream.h"

#include "CCharacter.h"
//#include "Character.h"

#include "OgreRender.h"
#include "NxOgreConverter.h"

#include "CActor.h"

//class Nxscene;
//class UserAllocator;
//class ErrorStream;
class CActor;
class Character;
//class EditableTerrain;
class OgreRender;

using namespace Ogre;
//using namespace NxOgre;

class Physics : public Ogre::Singleton<Physics>, public NxOgre::GroupCallback::InheritedCallback, public NxUserTriggerReport
{
public:
	Physics(); //OgreRender* ogre,EditableTerrain* terrain
	~Physics();
	
	static Physics& getSingleton(void);
	static Physics* getSingletonPtr(void);

	void onStartTouch(NxOgre::Actor*, NxOgre::Actor*, NxOgre::ContactStream*);
	void onEndTouch(NxOgre::Actor*, NxOgre::Actor*, NxOgre::ContactStream*);
	void onTouch(NxOgre::Actor*, NxOgre::Actor*, NxOgre::ContactStream*);

	void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);	
	
	void initialize();
	//void makeConnections();

	PhysicsActor* getActorFromCrosshair();
	void createScene(); //Create Scene's objects
	//void createTerrainActor(); //Create the actor entity of the terrain, ETM must be loaded first
	void simulate(const Ogre::Real &time); //Simulate one frame
	void startSimulation(); //Start the simulation
	void stopSimulation(); //Stop the simulation
	void shutdown(); //Shutdown system
	void resetScene(); //Empty current scene
	void setDefaultConfig(); //Set default global parameters 
	void addUserCharacter(Character* character);
	Character* Physics::getUserCharacter();

	NxOgre::World* getWorld();
	NxOgre::Scene* getScene();
	
	//void OnOgreRender_Created(OgreRender* ogre);
	//void OnEditableTerrain_Created(EditableTerrain* terrain);
	//void OnEditableTerrain_Generated(bool generate);

private:

	float mGravity;
	float mSkin;
	float mRestitution;
	float mStaticFriction;
	float mDynamicFriction;

	unsigned int mActorsCount;

	bool mIsInitialized;
	bool mIsRunningSim;
	bool mIsTerrainActorLoaded;

	NxOgre::World* mWorld;
	NxOgre::Scene* mScene;

	//NxRay mWorldRay;
//	Character* mCharacter;

	//ET::TerrainManager* mTerrainMgr;
	//Ogre::SceneManager* mSceneMgr;
	OgreRender* mOgre;
	//EditableTerrain* mTerrain;
	//EditableTerrain* mEditableTerrain;
};

#endif
