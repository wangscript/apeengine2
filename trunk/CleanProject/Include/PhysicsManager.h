/*!
	@file
	@author		Pablo Nuñez
	@date		13/2009
	@module
*//*
	This file is part of the Nebula Engine.
	
	Nebula Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Nebula Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Nebula Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PHYSICS_MANAGER_H
#define _PHYSICS_MANAGER_H

#include "EnginePrerequisites.h"

enum GameGroup
{
	GROUP_NON_COLLIDABLE,
	GROUP_COLLIDABLE_NON_PUSHABLE,
	GROUP_COLLIDABLE_PUSHABLE,
};

#define COLLIDABLE_MASK	(1<<GROUP_COLLIDABLE_NON_PUSHABLE) | (1<<GROUP_COLLIDABLE_PUSHABLE)

class UserAllocator;

namespace Nebula {

	using namespace Ogre;

	class ITask;
	class GameObject;

	class NebulaDllPrivate PhysicsManager : public ITask,
		                                    public Ogre::Singleton<PhysicsManager>, 
											public NxUserTriggerReport,
											public NxUserContactReport
											//public NxUserControllerHitReport
	{
	public:

		PhysicsManager();
		~PhysicsManager();
		
		static PhysicsManager& getSingleton(void);
		static PhysicsManager* getSingletonPtr(void);

		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();

		//Actors
		void onContactNotify(NxContactPair& pair, NxU32 events);

		//Triggers
		void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);	

		bool initialize();

		bool createScene(); //Create Scene's objects
		void simulate(const Ogre::Real &time); //Simulate one frame
		void startSimulation(); //Start the simulation
		void stopSimulation(); //Stop the simulation
		void shutdown(); //Shutdown system
		void resetScene(); //Empty current scene
		void setDefaultConfig(); //Set default global parameters 
		
		UserAllocator* getUserAllocator();

		Real castRayGetHitDistance(Vector3 startPosition, Vector3 direction, bool omitTriggers,bool omitActors, bool omitStatic, bool omitDynamic, bool omitCharacters);
		GameObject* castRayGetClosest(Vector3 startPosition, Vector3 direction, bool omitTriggers, bool omitActors, bool omitStatic, bool omitDynamic, bool omitCharacters);

		NxScene* getScene();
		NxPhysicsSDK* getSDK();

	private:
		ErrorStream mErrorStream;
		UserAllocator* mUserAllocator;

		NxRay mWorldRay;

		float mGravity;
		float mSkin;
		float mRestitution;
		float mStaticFriction;
		float mDynamicFriction;

		bool mIsInitialized;
		bool mIsSceneCreated;
		bool mIsRunningSim;

		NxPhysicsSDK* mSDK;
		NxScene* mScene;

		float mCurrentTime;
	};

} //end namespace

#endif
