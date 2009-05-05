#include <algorithm>
#include <sstream>

#include "AIManager.h"
#include "OgreRender.h"

#include "EditableTerrain.h"

//#include "Pedestrian.cpp"

//#include "OpenSteer/OpenSteerDemo.h" 

//#include "OpenSteer/SimpleVehicle.h"

//#include "Pedestrian.h"

#include "opensteer/Vec3.h"

#include "ObjectManager.h"
#include "CRender.h"
#include "CMesh.h"
#include "CPosition.h"
#include "COrientation.h"
#include "CAI.h"
#include "CAnimation.h"

//class Pedestrian;

//class Vec3;

//AIManager::AIManager() { }
//AIManager::~AIManager() { }

template<> AIManager* Ogre::Singleton<AIManager>::ms_Singleton = 0;

AIManager* AIManager::getSingletonPtr(void)
{
	return ms_Singleton;
}
AIManager& AIManager::getSingleton(void)
{  
	return ( *ms_Singleton );  
}

AIManager::AIManager()
{
	//AIManager::initialize();
	//AIManager::selectNextPlugIn();
	//AIManager::selectNextVehicle();

}

AIManager::~AIManager()
{
	
}

void AIManager::initialize (void)
{
	//selectedPlugIn = NULL;
	//selectedVehicle = NULL;
	//mPopulation = 0;

	//selectDefaultPlugIn ();

	//openSelectedPlugIn ();
	//resetSelectedPlugIn();
	//
	//const OpenSteer::AVGroup& vehicles = allVehiclesOfSelectedPlugIn();
	//for (OpenSteer::AVIterator i = vehicles.begin(); i != vehicles.end(); i++)
	//{
	//	addVehicle((*i));
	//}
	//
	//selectedVehicle = NULL;

	OpenSteer::OpenSteerDemo::initialize();
	OpenSteer::OpenSteerDemo::selectNextPlugIn();
	OpenSteer::OpenSteerDemo::selectNextVehicle();

	const OpenSteer::AVGroup& vehicles = OpenSteer::OpenSteerDemo::allVehiclesOfSelectedPlugIn();
	for (OpenSteer::AVIterator i = vehicles.begin(); i != vehicles.end(); i++)
	{
		//addVehicle((*i));
		addCharacter("pedestrian",(*i));
	}

}


// ----------------------------------------------------------------------------
// main update function: step simulation forward and redraw scene
/*
PedestrianPlugIn* AIManager::getPedestrianPlugIn() {
	return dynamic_cast<PedestrianPlugIn*>(selectedPlugIn);
}
*/

void AIManager::addVehicle(OpenSteer::AbstractVehicle* v) {

	EntityList* entl = new EntityList();
	entl->ent = OgreRender::getSingleton().getSceneManager()->createEntity(Ogre::StringConverter::toString(mPopulation) + "_ent", "Actor_barrel1.mesh");
	entl->ent->setMaterialName("ogre2"); //ogre2

	//Ogre::SceneNode* sn;
	entl->node = OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::StringConverter::toString(mPopulation),Ogre::Vector3::ZERO);
	entl->node->attachObject(entl->ent);
	//mTargetNode->setScale(0.01,0.01,0.01);
	entl->node->setScale(0.1,0.1,0.1);

	entl->node->setPosition(Ogre::Vector3(v->position().x,v->position().y,v->position().z));

	//v->setMass(Ogre::Math::RangeRandom(1,5));
	//v->setMaxSpeed(Ogre::Math::RangeRandom(1,6));
	//v->setMaxForce(Ogre::Math::RangeRandom(0,2));
	//v->setRadius(Ogre::Math::RangeRandom(0.2,0.8));

	v->setPosition(OpenSteer::Vec3(0,0,0));

	entl->vehicle = v;

	mEntList.push_back(entl);

	mPopulation++;
}

void AIManager::updateVehicles() {

	std::vector<EntityList*>::const_iterator i;
	for(i=mEntList.begin(); i!=mEntList.end(); ++i){

		OpenSteer::Vec3 vPos = (*i)->vehicle->position();
		OpenSteer::Vec3 vForw = (*i)->vehicle->forward();

		Ogre::Vector3 p = Ogre::Vector3(vPos.x,vPos.y,vPos.z);
		p.y = EditableTerrain::getSingleton().getTerrainHeightAt(p.x,p.z);

		(*i)->node->setPosition(Ogre::Vector3(p.x,p.y,p.z));
		Ogre::Vector3 forwDir = Ogre::Vector3(vForw.x, vForw.y, vForw.z);
		forwDir.normalise();
		(*i)->node->setDirection(forwDir, Ogre::SceneNode::TS_WORLD, Ogre::Vector3::UNIT_Z);  

	}


}


void AIManager::addCharacter(Ogre::String name,OpenSteer::AbstractVehicle* pedestrian) {
	
	//PedestrianPlugIn* pp = dynamic_cast<PedestrianPlugIn*>(selectedPlugIn); //->nextPD()
	
	//Pedestrian* pedestrian = pp->addPedestrianToCrowd();
	
	//pedestrian->
	
	Ogre::String uniqueName = name + Ogre::StringConverter::toString(mPopulation); //pp->population

	GameObject* go = new GameObject(uniqueName);

	Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(uniqueName,"Black_Mama_Skin.mesh");
	//Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(uniqueName,"Actor_barrel1.mesh");

	ent->setCastShadows(false);
	
	//CMesh* _CMesh = new CMesh("Black_Mama_Skin.mesh",uniqueName); //Ticket Collector.mesh Actor_barrel1.mesh
	CMesh* _CMesh = new CMesh(ent); //Ticket Collector.mesh Actor_barrel1.mesh
	
	CAnimation* _CAnim = new CAnimation();
	//CCharacter* _CCharacter = new CCharacter("nin");
	//CCamera* _CCamera = new CCamera(CCamera::VIEW_THIRD_PERSON_FREE);
	//CPlayerInput* _CPlayerInput = new CPlayerInput();
	CRender* _CRender = new CRender(uniqueName + "_Node");
	//CCharacterSound* _CharSound = new CCharacterSound();
	CPosition* _CPos = new CPosition(Vector3(pedestrian->position().x,pedestrian->position().y,pedestrian->position().z));
	COrientation* _COrient = new COrientation();
	CAI* _CAI = new CAI(pedestrian); //*pp->pd

	OpenSteer::Vec3 p = pedestrian->position();

	//go->setComponent(_CPlayerInput);
	go->setComponent(_CRender);
	//go->setComponent(_CCamera);
	//go->setComponent(_CCharacter);
	//go->setComponent(_CAnim);
	go->setComponent(_COrient);
	go->setComponent(_CPos);
	go->setComponent(_CMesh);
	//go->setComponent(_CharSound);
	go->setComponent(_CAI);
	go->setComponent(_CAnim);
	go->setup();

	_CAI->setDefaultAnimation();
	//_CRender->mNode->setScale(0.2f,1.0f,0.2f);
	_CRender->mNode->setScale(0.3,0.3,0.3);
	_CRender->mNode->attachObject(ent);

	ObjectManager::getSingleton().addObject(go);

	mPopulation++;
}

void AIManager::updateSimulationAndRedraw (float currentTime, float elapsedTime)
{
	// update global simulation clock
	//clock.update ();

	//  start the phase timer (XXX to accurately measure "overhead" time this
	//  should be in displayFunc, or somehow account for time outside this
	//  routine)
	//initPhaseTimers ();

	// run selected PlugIn (with simulation's current time and step size)
	//updateSelectedPlugIn (currentTime,elapsedTime);

	OpenSteer::OpenSteerDemo::updateSimulationAndRedraw( 0,elapsedTime);

	//updateVehicles();


	//updateSelectedPlugIn (clock.getTotalSimulationTime (),
	//	clock.getElapsedSimulationTime ());

	// redraw selected PlugIn (based on real time)
	//redrawSelectedPlugIn (clock.getTotalRealTime (),
	//                      clock.getElapsedRealTime ());
}


// ----------------------------------------------------------------------------
// exit OpenSteerDemo with a given text message or error code



/*
void AIManager::updateTargetNode() {

	//mTargetNode
	if(selectedVehicle != NULL) {

		//OpenSteer::AbstractVehicle* vehicle = OpenSteer::OpenSteerDemo::selectedVehicle;

		//vehicle->position()
		Ogre::Vector3 p = Ogre::Vector3(selectedVehicle->position().x,selectedVehicle->position().y,selectedVehicle->position().z);
		
		p.y = EditableTerrain::getSingleton().getTerrainHeightAt(p.x,p.z);

		mTargetNode->setPosition(p);

		//Ogre::Vector3 mForwardVector = Ogre::Vector3::UNIT_Z;
		Ogre::Vector3 forwDir = Ogre::Vector3(selectedVehicle->forward().x, 
											  selectedVehicle->forward().y, 
											  selectedVehicle->forward().z);
		forwDir.normalise();



		mTargetNode->setDirection(forwDir, Ogre::SceneNode::TS_WORLD, Ogre::Vector3::UNIT_Z);  
	}
}
*/