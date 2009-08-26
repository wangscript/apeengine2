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

#ifndef _CMESH_H_
#define _CMESH_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	class CCharacterController;
	class CPhysicsActor;
	class CPhysicsTrigger;

	struct NebulaDllPrivate CMeshDesc
	{
		CMeshDesc()
		{

		}

		std::string name;
		std::string fileName;
		std::string textureFileName;
		std::string textureTileU;
		std::string textureTileV;

		std::string materialName;
	};
	
	class NebulaDllPrivate CMesh : public IGameComponent {
	public:
		CMesh();
		CMesh(const CMeshDesc&);
		~CMesh();

		bool OnCharacterMouseMovedOverObject(CCharacterController* character, Ogre::Vector3 position);
		bool OnCharacterMouseMovedEnterOverObject(CCharacterController* character, Ogre::Vector3 position);
		bool OnCharacterMouseMovedLeaveOverObject(CCharacterController* character, Ogre::Vector3 position);
		bool OnCharacterMousePressedObject(CCharacterController* character, Ogre::Vector3 position, int mouseButton);
		bool OnCharacterMouseReleasedObject(CCharacterController* character, Ogre::Vector3 position, int mouseButton);

		Real getDistanceToActor(CPhysicsActor* actor);
		Real getDistanceToCharacter(CCharacterController* character);
		Real getDistanceToTrigger(CPhysicsTrigger* trigger);

		void update();
		void setup();
		
		void setMeshAmbientColour(Ogre::ColourValue colourValue);

		//Get the entity of the component
		Ogre::Entity* getEntity() {
			return mEntity;
		}

		//Set the entity of the component
		void setEntity(Ogre::Entity* ent) {
			mEntity = ent;
		}
		
		//Name of the entity (ObjectName + "_Mesh")
		std::string getName() {
			return mDesc.name;
		}

		//Name of the mesh file.
		std::string getMeshFileName() {
			return mDesc.fileName;
		}

		//Set the name of the mesh file
		void setMeshFileName(std::string meshFileName) {
			mDesc.fileName = meshFileName;
		}

		Ogre::SceneNode* getOffsetNode() {
			return mOffsetNode;
		}

		void updateMaterial();
		
		CMeshDesc& getDescription() {
			return mDesc;
		}
		
		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;
		Ogre::Entity* mEntity;
		Ogre::SceneNode* mOffsetNode;

		CMeshDesc mDesc;
	};

} //end namespace

#endif
