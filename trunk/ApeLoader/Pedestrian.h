// ----------------------------------------------------------------------------
//
//
// OpenSteer -- Steering Behaviors for Autonomous Characters
//
// Copyright (c) 2002-2003, Sony Computer Entertainment America
// Original author: Craig Reynolds <craig_reynolds@playstation.sony.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
//
// ----------------------------------------------------------------------------
//
//
// An autonomous "pedestrian":
// follows paths, avoids collisions with obstacles and other pedestrians
//
// 10-29-01 cwr: created
//
//
// ----------------------------------------------------------------------------

#ifndef _PEDESTRIAN_H_
#define _PEDESTRIAN_H_

#include <iomanip>
#include <sstream>
#include "OpenSteer/Pathway.h"
#include "OpenSteer/SimpleVehicle.h"
//#include "OpenSteer/OpenSteerDemo.h"
#include "OpenSteer/Proximity.h"

#include "AIManager.h"

using namespace OpenSteer;


typedef AbstractProximityDatabase<AbstractVehicle*> ProximityDatabase;
typedef AbstractTokenForProximityDatabase<AbstractVehicle*> ProximityToken;


// ----------------------------------------------------------------------------


class Pedestrian : public SimpleVehicle
{
public:

	// type for a group of Pedestrians
	typedef std::vector<Pedestrian*> groupType;

	// constructor
	Pedestrian (ProximityDatabase& pd); //ProximityDatabase& pd

	// destructor
	virtual ~Pedestrian ();

	// reset all instance state
	void reset (void);

	// per frame simulation update
	void update (const float currentTime, const float elapsedTime);

	// compute combined steering force: move forward, avoid obstacles
	// or neighbors if needed, otherwise follow the path and wander
	Vec3 determineCombinedSteering (const float elapsedTime);


	// draw this pedestrian into scene
	void draw (void);


	// called when steerToFollowPath decides steering is required
	void annotatePathFollowing (const Vec3& future,
		const Vec3& onPath,
		const Vec3& target,
		const float outside);

	// called when steerToAvoidCloseNeighbors decides steering is required
	// (parameter names commented out to prevent compiler warning from "-W")
	void annotateAvoidCloseNeighbor (const AbstractVehicle& other,
		const float);

	// (parameter names commented out to prevent compiler warning from "-W")
	void annotateAvoidNeighbor (const AbstractVehicle& threat,
		const float /*steer*/,
		const Vec3& ourFuture,
		const Vec3& threatFuture);

	// xxx perhaps this should be a call to a general purpose annotation for
	// xxx "local xxx axis aligned box in XZ plane" -- same code in in
	// xxx CaptureTheFlag.cpp
	void annotateAvoidObstacle (const float minDistanceToCollision);

	// switch to new proximity database -- just for demo purposes
	void newPD (ProximityDatabase& pd);

	// a pointer to this boid's interface object for the proximity database
	ProximityToken* proximityToken;

	// allocate one and share amoung instances just to save memory usage
	// (change to per-instance allocation to be more MP-safe)
	static AVGroup neighbors;

	// path to be followed by this pedestrian
	// XXX Ideally this should be a generic Pathway, but we use the
	// XXX getTotalPathLength and radius methods (currently defined only
	// XXX on PolylinePathway) to set random initial positions.  Could
	// XXX there be a "random position inside path" method on Pathway?
	PolylinePathway* path;

	// direction for path following (upstream or downstream)
	int pathDirection;
};



// ----------------------------------------------------------------------------
// create path for PlugIn 
//
//
//        | gap |
//
//        f      b
//        |\    /\        -
//        | \  /  \       ^
//        |  \/    \      |
//        |  /\     \     |
//        | /  \     c   top
//        |/    \g  /     |
//        /        /      |
//       /|       /       V      z     y=0
//      / |______/        -      ^
//     /  e      d               |
//   a/                          |
//    |<---out-->|               o----> x
//



// ----------------------------------------------------------------------------
// OpenSteerDemo PlugIn


class PedestrianPlugIn : public PlugIn
{
public:

	const char* name (void) {return "Pedestrians";}

	float selectionOrderSortKey (void) {return 0.02f;}

	virtual ~PedestrianPlugIn() {}// be more "nice" to avoid a compiler warning

	void open (void);

	void update (const float currentTime, const float elapsedTime);

	void redraw (const float currentTime, const float elapsedTime);


	void serialNumberAnnotationUtility (const AbstractVehicle& selected,
		const AbstractVehicle& nearMouse);

	/*
	void drawPathAndObstacles (void)
	{
	// draw a line along each segment of path
	const PolylinePathway& path = *getTestPath ();
	for (int i = 0; i < path.pointCount; i++)
	if (i > 0) drawLine (path.points[i], path.points[i-1], gRed);

	// draw obstacles
	drawXZCircle (gObstacle1.radius, gObstacle1.center, gWhite, 40);
	drawXZCircle (gObstacle2.radius, gObstacle2.center, gWhite, 40);
	}
	*/
	void close (void);

	void reset (void);

	void handleFunctionKeys (int keyNumber);

	void printMiniHelpForFunctionKeys (void);


	Pedestrian* addPedestrianToCrowd (void);

	void removePedestrianFromCrowd (void);


	// for purposes of demonstration, allow cycling through various
	// types of proximity databases.  this routine is called when the
	// OpenSteerDemo user pushes a function key.
	void nextPD (void);


	const AVGroup& allVehicles (void) {return (const AVGroup&) crowd;}

	// crowd: a group (STL vector) of all Pedestrians
	Pedestrian::groupType crowd;
	typedef Pedestrian::groupType::const_iterator iterator;

	Vec3 gridCenter;

	// pointer to database used to accelerate proximity queries
	ProximityDatabase* pd;

	// keep track of current flock size
	int population;

	// which of the various proximity databases is currently in use
	int cyclePD;
};

#endif




