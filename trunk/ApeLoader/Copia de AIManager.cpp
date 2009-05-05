#include <algorithm>
#include <sstream>

#include "AIManager.h"
#include "OgreRender.h"

#include "EditableTerrain.h"

//#include "Pedestrian.cpp"

#include "OpenSteer/SimpleVehicle.h"

//#include "Pedestrian.h"

#include "ObjectManager.h"
#include "CRender.h"
#include "CMesh.h"
#include "CPosition.h"
#include "COrientation.h"
#include "CAI.h"
#include "CAnimation.h"

//class Pedestrian;

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

namespace {

	void printPlugIn (OpenSteer::PlugIn& pi) {std::cout << " " << pi << std::endl;} // XXX

} // anonymous namespace

void AIManager::initialize (void)
{
//	mouseX = 0;
//	mouseY = 0;
//	mouseInWindow = false;

	selectedPlugIn = NULL;
	selectedVehicle = NULL;
	mPopulation = 0;
	//int AIManager::phase = AIManager::overheadPhase;
	//enableAnnotation = true;

	//const int AIManager::overheadPhase = 0;
	//const int AIManager::updatePhase = 1;
	//const int AIManager::drawPhase = 2;

	// select the default PlugIn
	selectDefaultPlugIn ();
/*
	{
		// XXX this block is for debugging purposes,
		// XXX should it be replaced with something permanent?

		std::cout << std::endl << "Known plugins:" << std::endl;   // xxx?
		PlugIn::applyToAll (printPlugIn);                          // xxx?
		std::cout << std::endl;                                    // xxx?

		// identify default PlugIn
		if (!selectedPlugIn) errorExit ("no default PlugIn");
		std::cout << std::endl << "Default plugin:" << std::endl;  // xxx?
		std::cout << " " << *selectedPlugIn << std::endl;          // xxx?
		std::cout << std::endl;                                    // xxx?
	}
*/
	// initialize the default PlugIn
	openSelectedPlugIn ();
	resetSelectedPlugIn();
	

	//Ogre::Entity* mVehicleEnt;
	//mVehicleEnt = OgreRender::getSingleton().getSceneManager()->createEntity("ogrehead", "Actor_barrel1.mesh");
	//mVehicleEnt->setMaterialName("ogre"); //ogre2

	//mTargetNode = OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::Vector3::ZERO);
	//mTargetNode->attachObject(mVehicleEnt);
	//mTargetNode->setScale(0.01,0.01,0.01);
	//mTargetNode->setScale(0.01,0.01,0.01);

	//dynamic_cast<PedestrianPlugIn*>(selectedPlugIn)->reset();
	
	//Pedestrian& firstPedestrian = **crowd.begin();

	//for(int i = 1;i<50;i++)

	const OpenSteer::AVGroup& vehicles = allVehiclesOfSelectedPlugIn();
	for (OpenSteer::AVIterator i = vehicles.begin(); i != vehicles.end(); i++)
	{
		//addCharacter("pedestrian",(*i));
		addVehicle((*i));
	}
	//selectNextVehicle();
	
	selectedVehicle = NULL;

	//addCharacter("pedestrian");
	//addCharacter("pedestrian");

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

	entl->vehicle = v;

	mEntList.push_back(entl);

	mPopulation++;
}

void AIManager::updateVehicles() {

	std::vector<EntityList*>::const_iterator i;
	for(i=mEntList.begin(); i!=mEntList.end(); ++i){

		Vec3 vPos = (*i)->vehicle->position();
		Vec3 vForw = (*i)->vehicle->forward();

		(*i)->node->setPosition(Ogre::Vector3(vPos.x,vPos.y,vPos.z));
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

	Vec3 p = pedestrian->position();

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
	updateSelectedPlugIn (currentTime,elapsedTime);

	//updateSelectedPlugIn (clock.getTotalSimulationTime (),
	//	clock.getElapsedSimulationTime ());

	// redraw selected PlugIn (based on real time)
	//redrawSelectedPlugIn (clock.getTotalRealTime (),
	//                      clock.getElapsedRealTime ());
}


// ----------------------------------------------------------------------------
// exit OpenSteerDemo with a given text message or error code


void AIManager::errorExit (const char* message)
{
	printMessage (message);
#ifdef _MSC_VER
	MessageBox(0, message, "OpenSteerDemo Unfortunate Event", MB_ICONERROR);
#endif
	exit (-1);
}


void AIManager::exit (int exitCode)
{
	::exit (exitCode);
}


// ----------------------------------------------------------------------------
// select the default PlugIn


void AIManager::selectDefaultPlugIn (void)
{
	PlugIn::sortBySelectionOrder ();
	selectedPlugIn = PlugIn::findDefault ();
	
	
	
	//selectedPlugIn->handleFunctionKeys()

}


// ----------------------------------------------------------------------------
// select the "next" plug-in, cycling through "plug-in selection order"


void AIManager::selectNextPlugIn (void)
{
	closeSelectedPlugIn ();
	selectedPlugIn = selectedPlugIn->next ();
	openSelectedPlugIn ();
}


// ----------------------------------------------------------------------------
// handle function keys an a per-plug-in basis


void AIManager::functionKeyForPlugIn (int keyNumber)
{
	selectedPlugIn->handleFunctionKeys (keyNumber);
}


// ----------------------------------------------------------------------------
// return name of currently selected plug-in


const char* 
AIManager::nameOfSelectedPlugIn (void)
{
	return (selectedPlugIn ? selectedPlugIn->name() : "no PlugIn");
}


// ----------------------------------------------------------------------------
// open the currently selected plug-in


void AIManager::openSelectedPlugIn (void)
{
//	camera.reset ();
	selectedVehicle = NULL;
	selectedPlugIn->open ();
}


// ----------------------------------------------------------------------------
// do a simulation update for the currently selected plug-in


void AIManager::updateSelectedPlugIn (const float currentTime,
												const float elapsedTime)
{
	// switch to Update phase
	//pushPhase (updatePhase);

	// service queued reset request, if any
	doDelayedResetPlugInXXX ();

	// if no vehicle is selected, and some exist, select the first one
	if (selectedVehicle == NULL)
	{
		const AVGroup& vehicles = allVehiclesOfSelectedPlugIn();
		//if (vehicles.size() > 0) selectedVehicle = vehicles.front();
	}

	// invoke selected PlugIn's Update method
	selectedPlugIn->update (currentTime, elapsedTime);

	// return to previous phase
	// popPhase ();
}


// ----------------------------------------------------------------------------
// redraw graphics for the currently selected plug-in


void AIManager::redrawSelectedPlugIn (const float currentTime,
												const float elapsedTime)
{
	// switch to Draw phase
	//pushPhase (drawPhase);

	// invoke selected PlugIn's Draw method
	//selectedPlugIn->redraw (currentTime, elapsedTime);

	// draw any annotation queued up during selected PlugIn's Update method
	//drawAllDeferredLines ();
	//drawAllDeferredCirclesOrDisks ();

	// return to previous phase
	//popPhase ();
}


// ----------------------------------------------------------------------------
// close the currently selected plug-in


void AIManager::closeSelectedPlugIn (void)
{
	selectedPlugIn->close ();
	selectedVehicle = NULL;
}


// ----------------------------------------------------------------------------
// reset the currently selected plug-in


void AIManager::resetSelectedPlugIn (void)
{
	selectedPlugIn->reset ();
}


namespace {

	// ----------------------------------------------------------------------------
	// XXX this is used by CaptureTheFlag
	// XXX it was moved here from main.cpp on 12-4-02
	// XXX I'm not sure if this is a useful feature or a bogus hack
	// XXX needs to be reconsidered.


	bool gDelayedResetPlugInXXX = false;

} // anonymous namespace


void 
AIManager::queueDelayedResetPlugInXXX (void)
{
	gDelayedResetPlugInXXX = true;
}


void AIManager::doDelayedResetPlugInXXX (void)
{
	if (gDelayedResetPlugInXXX)
	{
		resetSelectedPlugIn ();
		gDelayedResetPlugInXXX = false;
	}
}


// ----------------------------------------------------------------------------
// return a group (an STL vector of AbstractVehicle pointers) of all
// vehicles(/agents/characters) defined by the currently selected PlugIn


const OpenSteer::AVGroup& AIManager::allVehiclesOfSelectedPlugIn (void)
{
	return selectedPlugIn->allVehicles ();
}


// ----------------------------------------------------------------------------
// select the "next" vehicle: the one listed after the currently selected one
// in allVehiclesOfSelectedPlugIn


void AIManager::selectNextVehicle (void)
{
	if (selectedVehicle != NULL)
	{


		// get a container of all vehicles
		const AVGroup& all = allVehiclesOfSelectedPlugIn ();
		const AVIterator first = all.begin();
		const AVIterator last = all.end();

		// find selected vehicle in container
		const AVIterator s = std::find (first, last, selectedVehicle);

		// normally select the next vehicle in container
		selectedVehicle = *(s+1);
		
		//selectedVehicle->setMass(0.1f);
		//selectedVehicle->setMaxSpeed(20);
		//selectedVehicle->setPosition(Vec3(0,0,0));

		//selectedVehicle->setPosition(Vec3(0,0,0));
		//selectedVehicle->setRadius(6.0);
		//mPedestrian->set
		//selectedVehicle->setMaxSpeed(240); //240
		//selectedVehicle->setMass(1.0); //0.01


		// if we are at the end of the container, select the first vehicle
		if (s == last-1) selectedVehicle = *first;

		// if the search failed, use NULL
		if (s == last) selectedVehicle = *first;
	}
}


void AIManager::selectVehicleNearestScreenPosition (int x, int y)
{
	selectedVehicle = findVehicleNearestScreenPosition (x, y);
}


OpenSteer::AbstractVehicle* AIManager::vehicleNearestToMouse (void)
{
//	return (mouseInWindow ? 
//		findVehicleNearestScreenPosition (mouseX, mouseY) :
	return NULL;
}



OpenSteer::AbstractVehicle* AIManager::findVehicleNearestScreenPosition (int x, int y)
{
	// find the direction from the camera position to the given pixel
	const Vec3 direction = OpenSteer::Vec3(0,0,0); // directionFromCameraToScreenPosition (x, y);

	// iterate over all vehicles to find the one whose center is nearest the
	// "eye-mouse" selection line
	float minDistance = FLT_MAX;       // smallest distance found so far
	AbstractVehicle* nearest = NULL;   // vehicle whose distance is smallest
	const AVGroup& vehicles = allVehiclesOfSelectedPlugIn();
	for (AVIterator i = vehicles.begin(); i != vehicles.end(); i++)
	{

	}

	return nearest;
}






void AIManager::printMessage (const char* message)
{
	std::cout << "OpenSteerDemo: " <<  message << std::endl << std::flush;
}


void AIManager::printMessage (const std::ostringstream& message)
{
	printMessage (message.str().c_str());
}


void AIManager::printWarning (const char* message)
{
	std::cout << "OpenSteerDemo: Warning: " <<  message << std::endl << std::flush;
}


void AIManager::printWarning (const std::ostringstream& message)
{
	printWarning (message.str().c_str());
}


// ------------------------------------------------------------------------
// print list of known commands
//
// XXX this list should be assembled automatically,
// XXX perhaps from a list of "command" objects created at initialization


void AIManager::keyboardMiniHelp (void)
{
	printMessage ("");
	printMessage ("defined single key commands:");
	printMessage ("  r      restart current PlugIn.");
	printMessage ("  s      select next vehicle.");
	printMessage ("  c      select next camera mode.");
	printMessage ("  f      select next preset frame rate");
	printMessage ("  Tab    select next PlugIn.");
	printMessage ("  a      toggle annotation on/off.");
	printMessage ("  Space  toggle between Run and Pause.");
	printMessage ("  ->     step forward one frame.");
	printMessage ("  Esc    exit.");
	printMessage ("");

	// allow PlugIn to print mini help for the function keys it handles
	selectedPlugIn->printMiniHelpForFunctionKeys ();
}

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