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

#ifndef _CPHYSICS_TRIGGER_H_
#define _CPHYSICS_TRIGGER_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	class CPhysicsActor;
	class CCharacterController;

	struct NebulaDllPrivate CPhysicsTriggerDesc
	{
		CPhysicsTriggerDesc()
		{

		}
		
		std::string name;
		
		bool isStatic;

		std::string meshFileName;

		Ogre::Vector3 initialPosition;
		//Ogre::Quaternion initialOrientation;

		NxActorDesc actorDesc;
		NxBodyDesc bodyDesc;

	};
	
	class NebulaDllPrivate CPhysicsTrigger : public IGameComponent {
	public:
		CPhysicsTrigger();
		CPhysicsTrigger(const CPhysicsTriggerDesc&);
		~CPhysicsTrigger();

		void update();
		void setup();

		void OnActorEnter(CPhysicsActor*);
		void OnActorStay(CPhysicsActor*);
		void OnActorLeave(CPhysicsActor*);

		void OnControllerEnter(CCharacterController* character);
		void OnControllerStay(CCharacterController* character);
		void OnControllerLeave(CCharacterController* character);

		CPhysicsTriggerDesc& getDescription() {
			return mDesc;
		}
		
		NxActor* getNxActor() {
			return mActor;
		}

		//void callLuaFunction(const std::string func );
		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:

		void create();

		std::string mComponentID;
		NxActor* mActor;
		CPhysicsTriggerDesc mDesc;
	};

} //end namespace

#endif
