#ifndef _AIManager_H
#define _AIManager_H

#include "Ogre.h"
//#include "OpenSteer/OpenSteerDemo.h" 

#include "OpenSteer/Vec3.h"
//#include "OpenSteer/Clock.h"
#include "OpenSteer/PlugIn.h"
//#include "OpenSteer/Camera.h"
#include "OpenSteer/Utilities.h"

//#include "Pedestrian.h"

class PedestrianPlugIn;

using namespace Ogre;
using namespace OpenSteer;

class EntityList {
public:
	EntityList() {};


	Ogre::Entity* ent;
	Ogre::SceneNode* node;
	OpenSteer::AbstractVehicle* vehicle;
};
//std::map

class AIManager : public Ogre::Singleton<AIManager> 
{
public:
	AIManager();
	~AIManager();

	static AIManager& getSingleton(void);
	static AIManager* getSingletonPtr(void);
	

	//Ogre::SceneNode* mTargetNode;
	
	//void updateTargetNode();
	
	void addCharacter(Ogre::String name,OpenSteer::AbstractVehicle* pedestrian);
	
	//PedestrianPlugIn* getPedestrianPlugIn();
	//void update();

	//Clock clock;

	// camera automatically tracks selected vehicle
	//OpenSteer::Camera camera;

	// ------------------------------------------ addresses of selected objects

	// currently selected plug-in (user can choose or cycle through them)
	PlugIn* selectedPlugIn;

	// currently selected vehicle.  Generally the one the camera follows and
	// for which additional information may be displayed.  Clicking the mouse
	// near a vehicle causes it to become the Selected Vehicle.
	AbstractVehicle* selectedVehicle;

	// -------------------------------------------- initialize, update and exit

	// initialize OpenSteerDemo
	//     XXX  if I switch from "totally static" to "singleton"
	//     XXX  class structure this becomes the constructor
	void initialize (void);

	// main update function: step simulation forward and redraw scene
	void updateSimulationAndRedraw (float currentTime, float elapsedTime);

	// exit OpenSteerDemo with a given text message or error code
	void errorExit (const char* message);
	void exit (int exitCode);

	// ------------------------------------------------------- PlugIn interface

	// select the default PlugIn
	void selectDefaultPlugIn (void);

	// select the "next" plug-in, cycling through "plug-in selection order"
	void selectNextPlugIn (void);

	// handle function keys an a per-plug-in basis
	void functionKeyForPlugIn (int keyNumber);

	// return name of currently selected plug-in
	const char* nameOfSelectedPlugIn (void);

	// open the currently selected plug-in
	void openSelectedPlugIn (void);

	// do a simulation update for the currently selected plug-in
	void updateSelectedPlugIn (const float currentTime,
		const float elapsedTime);

	// redraw graphics for the currently selected plug-in
	void redrawSelectedPlugIn (const float currentTime,
		const float elapsedTime);

	// close the currently selected plug-in
	void closeSelectedPlugIn (void);

	// reset the currently selected plug-in
	void resetSelectedPlugIn (void);

	const AVGroup& allVehiclesOfSelectedPlugIn(void);

	// ---------------------------------------------------- OpenSteerDemo phase

	//bool phaseIsDraw     (void) {return phase == drawPhase;}
	//bool phaseIsUpdate   (void) {return phase == updatePhase;}
	//bool phaseIsOverhead (void) {return phase == overheadPhase;}

	//float phaseTimerDraw     (void) {return phaseTimers[drawPhase];}
	//float phaseTimerUpdate   (void) {return phaseTimers[updatePhase];}
	// XXX get around shortcomings in current implementation, see note
	// XXX in updateSimulationAndRedraw
	//static float phaseTimerOverhead(void){return phaseTimers[overheadPhase];}
	//float phaseTimerOverhead (void)
	//{
	//	return (clock.getElapsedRealTime() -
	//		(phaseTimerDraw() + phaseTimerUpdate()));
	//}

	// ------------------------------------------------------ delayed reset XXX

	// XXX to be reconsidered
	void queueDelayedResetPlugInXXX (void);
	void doDelayedResetPlugInXXX (void);

	// ------------------------------------------------------ vehicle selection

	// select the "next" vehicle: cycle through the registry
	void selectNextVehicle (void);

	// select vehicle nearest the given screen position (e.g.: of the mouse)
	void selectVehicleNearestScreenPosition (int x, int y);

	// ---------------------------------------------------------- mouse support

	// Find the AbstractVehicle whose screen position is nearest the
	// current the mouse position.  Returns NULL if mouse is outside
	// this window or if there are no AbstractVehicles.
	AbstractVehicle* vehicleNearestToMouse (void);

	// Find the AbstractVehicle whose screen position is nearest the
	// given window coordinates, typically the mouse position.  Note
	// this will return NULL if there are no AbstractVehicles.
	AbstractVehicle* findVehicleNearestScreenPosition (int x, int y);

	// for storing most recent mouse state
	//int mouseX;
	//int mouseY;
	//bool mouseInWindow;

	// ------------------------------------------------------- camera utilities

	// set a certain initial camera state used by several plug-ins
	//void init2dCamera (AbstractVehicle& selected);
	//void init2dCamera (AbstractVehicle& selected,
	//	float distance,
	//	float elevation);
	//void init3dCamera (AbstractVehicle& selected);
	//void init3dCamera (AbstractVehicle& selected,
	//	float distance,
	//	float elevation);

	// set initial position of camera based on a vehicle
	//void position3dCamera (AbstractVehicle& selected);
	//void position3dCamera (AbstractVehicle& selected,
	//	float distance,
	//	float elevation);
	//void position2dCamera (AbstractVehicle& selected);
	//void position2dCamera (AbstractVehicle& selected,
	//	float distance,
	//	float elevation);

	// camera updating utility used by several (all?) plug-ins
	//void updateCamera (const float currentTime,
	//	const float elapsedTime,
	//	const AbstractVehicle& selected);

	// some camera-related default constants
	//const float camera2dElevation;
	//const float cameraTargetDistance;
	//const Vec3 cameraTargetOffset;

	// ------------------------------------------------ graphics and annotation

	// do all initialization related to graphics
	//void initializeGraphics (void);

	// ground plane grid-drawing utility used by several plug-ins
	//void gridUtility (const Vec3& gridTarget);

	// draws a gray disk on the XZ plane under a given vehicle
	//void highlightVehicleUtility (const AbstractVehicle& vehicle);

	// draws a gray circle on the XZ plane under a given vehicle
	//void circleHighlightVehicleUtility (const AbstractVehicle& vehicle);

	// draw a box around a vehicle aligned with its local space
	// xxx not used as of 11-20-02
	//void drawBoxHighlightOnVehicle (const AbstractVehicle& v,
	//	const Vec3 color);

	// draws a colored circle (perpendicular to view axis) around the center
	// of a given vehicle.  The circle's radius is the vehicle's radius times
	// radiusMultiplier.
	//void drawCircleHighlightOnVehicle (const AbstractVehicle& v,
	//	const float radiusMultiplier,
	//	const Vec3 color);

	// graphical annotation: master on/off switch
	//bool annotationIsOn (void) {return enableAnnotation;}
	//void setAnnotationOn (void) {enableAnnotation = true;}
	//void setAnnotationOff (void) {enableAnnotation = false;}
	//bool toggleAnnotationState (void)
	//{return (enableAnnotation = !enableAnnotation);}

	// ----------------------------------------------------------- console text

	// print a line on the console with "OpenSteerDemo: " then the given ending
	void printMessage (const char* message);
	void printMessage (const std::ostringstream& message);

	// like printMessage but prefix is "OpenSteerDemo: Warning: "
	void printWarning (const char* message);
	void printWarning (const std::ostringstream& message);

	// print list of known commands
	void keyboardMiniHelp (void);

	// ---------------------------------------------------------------- private

	void updateVehicles();
	void addVehicle(OpenSteer::AbstractVehicle* v);

	std::vector<EntityList*> mEntList;

private:
	//bool enableAnnotation;
	
	unsigned int mPopulation;

	//int phase;
	//int phaseStack[];
	//int phaseStackIndex;
	//float phaseTimers[];
	//float phaseTimerBase;
	//const int phaseStackSize;
	//void pushPhase (const int newPhase);
	//void popPhase (void);
	//void initPhaseTimers (void);
	//void updatePhaseTimers (void);

	// XXX apparently MS VC6 cannot handle initialized static const members,
	// XXX so they have to be initialized not-inline.
	// static const int drawPhase = 2;
	// static const int updatePhase = 1;
	// static const int overheadPhase = 0;
	//const int drawPhase;
	//const int updatePhase;
	//const int overheadPhase;


};


#endif
