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

#ifndef __OGREMAX_MANAGER__
#define __OGREMAX_MANAGER__

#include "EnginePrerequisites.h"

class NxTriangleMesh;
class NxConvexMesh;

namespace Nebula {

	using namespace Ogre;
	using namespace OgreMax;

	class GameObject;

	//using namespace OgreMax::Types;
	//class CPhysicsActorDesc;
	class FileResource;
	enum MeshType;
	
	class Ogre::Animation;
	class Ogre::AnimationState;
	class Ogre::AnimationTrack;
	//class Ogre::SceneNode;

	struct ChildShape
	{
		ChildShape()
		{
			//shape = 0;
			//shapeDesc = 0;
		}

		std::string name;
		
		std::string parentName;
	
		std::string shapeType;
		std::string shapeFileType;
		std::string path;
		Ogre::Vector3 shapeSize;
		Ogre::Vector3 position;
		Ogre::Quaternion orientation;
		Ogre::Real mass;
		Ogre::Real density;
		Ogre::Real skinWidth;
		Ogre::Real restitution;
		Ogre::Real dynamicFriction;
		Ogre::Real staticFriction;

	};
	
	struct ChildAnimation
	{
		ChildAnimation()
		{

		}

		std::string name;
		
		std::string parentName;

		Ogre::AnimationState* animState;
		Ogre::AnimationTrack* animationTrack;
		Ogre::Animation* animation;
		Ogre::SceneNode* node;

		bool loop;
		bool enabled;
		Ogre::Animation::InterpolationMode translationMode;
		Ogre::Animation::RotationInterpolationMode rotationMode;
		Real length;

	};

	struct ChildCamera
	{
		ChildCamera()
		{

		}

		std::string name;
		
		std::string parentName;

		Ogre::Camera* camera;

	};

	class NebulaDllPrivate OgreMaxManager : public OgreMaxSceneCallback, 
						   public Ogre::Singleton<OgreMaxManager>,
						   public ITask
	{
	private:
		//NxOgre::World* NxWorld; //This one creates the scene
		//NxOgre::Scene* NxScene; //The scene which things get's all physics.
		Ogre::Vector3 mScenePosition;
		OgreMaxScene* mOgreMaxScene;
		
		std::string mSceneName;
		std::string mSceneFileName;
		std::string mSceneDirName;

		//std::map<const std::string, GameObject*> mChildGameObjectsList;
		
		std::map<const std::string, ChildShape> mChildShapeList;
		std::map<const std::string, ChildAnimation> mChildAnimationList;
		std::map<const std::string, ChildCamera> mChildCameraList;

		//std::map<const std::string&, GameObject*> mParentGameObjectsList;

		void setCamerasToObjects(OgreMaxScene* maxScene);
		void setChildShapesToParents(OgreMaxScene* maxScene);

		/*Ogre Max*/
		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();

		//Set Lua bindings
		void setBindings();

	public:
		OgreMaxManager ();

		static OgreMaxManager& getSingleton(void);
		static OgreMaxManager* getSingletonPtr(void);
		
		//////////////////////////////////////////////////////////////////////////
		NxTriangleMesh* getTriangleMesh(const std::string& path);
		NxConvexMesh* getConvexMesh(const std::string& path);

		MeshType getMeshTypeFromResource(FileResource* resource);

		NxShapeDesc* getShapeDesc(Ogre::Vector3 parentPos, std::string shapeType,std::string shapeFileType,std::string path, Ogre::Vector3 shapeSize,Ogre::Vector3 position, Ogre::Quaternion orientation, Ogre::Real mass, Ogre::Real density, Ogre::Real skinWidth, Ogre::Real restitution, Ogre::Real dynamicFriction, Ogre::Real staticFriction);

		//////////////////////////////////////////////////////////////////////////

		virtual Ogre::String getParamValue (Ogre::String paramName,Ogre::String param);

		virtual bool loadSceneFile(const std::string& fileName);
		virtual void LoadingSceneFile(const OgreMaxScene* scene, const Ogre::String& fileName, Ogre::String& resourceGroupName);
		virtual void LoadedUserData (const OgreMaxScene *scene, const Ogre::String &userDataReference, const Ogre::String &userData);
		
		virtual void CreatedEntity (const OgreMaxScene* scene, Ogre::Entity* entity);
		virtual void CreatedLight(const OgreMaxScene* scene, Ogre::Light* light);
		virtual void CreatedCamera(const OgreMaxScene* scene, Ogre::Camera* camera);
		virtual void CreatedNodeAnimation(const OgreMaxScene* scene, Ogre::SceneNode* Node, Ogre::Animation* animation);
		virtual void CreatedNodeAnimationTrack(const OgreMaxScene* scene, Ogre::SceneNode* node, Ogre::AnimationTrack* animationTrack, bool enabled, bool looping);
		virtual void CreatedNodeAnimationState(const OgreMaxScene* scene, Ogre::SceneNode* node, Ogre::AnimationState* animationState);
		
		virtual void UpdatedLoadProgress(const OgreMaxScene* scene, Ogre::Real progress);
		virtual void FinishedLoad (const OgreMaxScene* scene, bool success);
		

		//virtual bool loadSceneFile(const std::string& fileName);
	};

} //end namespace

#endif