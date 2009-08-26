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

#ifndef _PHYSICSACTOR_H_
#define _PHYSICSACTOR_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	class CPhysicsTrigger;
	class CCharacterController;

	struct NebulaDllPrivate CPhysicsActorDesc
	{
		CPhysicsActorDesc()
		{

		}
		
		// name of the PhysX Actor object name, Wich is: GameObjectName + "_Mesh" | "_SceneNode" | "_Actor" )
		std::string name; 
		
		bool isStatic;
		
		//std::string meshFileName;

		Ogre::Vector3 initialPosition;
		//Ogre::Quaternion initialOrientation;

		NxActorDesc actorDesc;
		NxBodyDesc bodyDesc;
	};

	class NebulaDllPrivate CPhysicsActor : public IGameComponent {
	public:
		CPhysicsActor(const CPhysicsActorDesc&); 
		~CPhysicsActor();

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}

		CPhysicsActorDesc& getDescription() {
			return mDesc;
		}
		
		NxActor* getNxActor() {
			return mActor;
		}
	
		bool isKinematic();
		bool isStatic();
		bool isDynamic();

		Real getDistanceToActor(CPhysicsActor* actor);
		Real getDistanceToCharacter(CCharacterController* character);
		Real getDistanceToTrigger(CPhysicsTrigger* trigger);

		void callLuaFunction(const std::string func );

		void update();
		void setup();

		void OnActorStartTouch(CPhysicsActor*);
		void OnActorTouch(CPhysicsActor*);
		void OnActorEndTouch(CPhysicsActor*);
		
		void OnControllerStartTouch(CCharacterController*);
		void OnControllerTouch(CCharacterController*);
		void OnControllerEndTouch(CCharacterController*);

		void OnTriggerEnter(CPhysicsTrigger*);
		void OnTriggerStay(CPhysicsTrigger*);
		void OnTriggerLeave(CPhysicsTrigger*);

		void create();

		bool OnCharacterMouseMovedOverObject(CCharacterController* character, Ogre::Vector3 position);
		bool OnCharacterMouseMovedEnterOverObject(CCharacterController* character, Ogre::Vector3 position);
		bool OnCharacterMouseMovedLeaveOverObject(CCharacterController* character, Ogre::Vector3 position);
		bool OnCharacterMousePressedObject(CCharacterController* character, Ogre::Vector3 position, int mouseButton);
		bool OnCharacterMouseReleasedObject(CCharacterController* character, Ogre::Vector3 position, int mouseButton);

	private:
		std::string mComponentID;
		
		void updateVisualRepresentation();

		CPhysicsActorDesc mDesc;
		NxActor* mActor;


	};

} //end namespace

#endif
