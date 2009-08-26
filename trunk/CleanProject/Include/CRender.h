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

#ifndef _CRENDER_H_
#define _CRENDER_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	class CPhysicsActor;
	class CCharacterController;
	class CPhysicsTrigger;

	struct NebulaDllPrivate CRenderDesc
	{
		CRenderDesc()
		{
			rotationSpeed = 1.0f;
		}
		
		std::string name;

		float rotationSpeed;
	};
	
	class NebulaDllPrivate CRender : public IGameComponent {
	public:
		CRender();
		CRender(const CRenderDesc&);
		~CRender();

		void update();
		void setup();
		
		void callLuaFunction(const std::string func );

		Real getDistanceToActor(CPhysicsActor* actor);
		Real getDistanceToCharacter(CCharacterController* character);
		Real getDistanceToTrigger(CPhysicsTrigger* trigger);

		Ogre::SceneNode* getNode() {
			return mNode;
		}

		void setNode(Ogre::SceneNode* node) {
			mNode = node;
		}

		float getRotationSpeed() {
			return mDesc.rotationSpeed;
		}

		void setRotationSpeed(float speed) {
			mDesc.rotationSpeed = speed;
		}
		void setOrientationDestination(Quaternion q);
		
		void setNextOrientation(Quaternion q) {
			mNextOrient = q;
		}

		Quaternion getNextOrientation() {
			return mNextOrient;
		}

		CRenderDesc& getDescription() {
			return mDesc;
		}

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}

		
	private:

		std::string mComponentID;
		Ogre::SceneNode* mNode;

		CRenderDesc mDesc;

		Ogre::Quaternion mOrientSrc;               // Initial orientation
		Ogre::Quaternion mOrientDest;              // Destination orientation

		Ogre::Quaternion mNextOrient;               // Initial orientation

		Ogre::Real mRotProgress;                   // How far we've interpolated
		Ogre::Real mRotFactor;                     // Interpolation step
		bool mRotating;


	};

} //end namespace

#endif

