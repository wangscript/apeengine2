#include "Ogre.h"
#include "OgreMaxScene.hpp"
#include "NxOgre.h"
#include "GameObject.h"
#include "PhysicsActor.h"

#include <iostream>

using namespace OgreMax;
using namespace Ogre;
using namespace std;

class PhysicsActor;

class OgreMaxSceneCallbacks : public OgreMaxSceneCallback
{
protected:
	NxOgre::World* NxWorld; //This one creates the scene
	NxOgre::Scene* NxScene; //The scene which things get's all physics.
	Ogre::Vector3 mScenePosition;

	std::map<const std::string, GameObject*> mDefaultNodes;
	std::map<const std::string, GameObject*> mChildNodes;
	
	std::map<const std::string, PhysicsActor*> mActors; 

	//gos = mObjMan->getGOs();

public:
	OgreMaxSceneCallbacks (NxOgre::Scene* s);
	OgreMaxSceneCallbacks (Ogre::Vector3 initPos);

	/*Custom*/
	virtual NxOgre::Convex* getConvex (Ogre::String &param);
	virtual NxOgre::TriangleMesh* getTriangle (Ogre::String &param);
	//virtual Ogre::String getFirstParam (Ogre::String param);
	
	virtual NxOgre::Shape* getShape (Ogre::String MeshName,Ogre::String mShapeType,Ogre::Vector3 mShapeSize);
	Ogre::String getMeshName (Ogre::String param);

	virtual Ogre::String getParamValue (Ogre::String paramName,Ogre::String param);

	//virtual void rotateActor (NxOgre::Actor* actor, Ogre::String params);
	//virtual void CreateWorld (Ogre::String allParams);
	NxOgre::Scene* getScene () {return NxScene;}

	bool generateNXS(Ogre::String &param);

	/*Ogre Max*/
	virtual void LoadingSceneFile(const OgreMaxScene* scene, const Ogre::String& fileName, Ogre::String& resourceGroupName);
	virtual void LoadedUserData (const OgreMax::OgreMaxScene *scene, const Ogre::String &userDataReference, const Ogre::String &userData);
	virtual void CreatedEntity (const OgreMax::OgreMaxScene* scene, Ogre::Entity* entity);
	virtual void CreatedLight(const OgreMax::OgreMaxScene* scene, Ogre::Light* light);
	virtual void CreatedCamera(const OgreMaxScene* scene, Ogre::Camera* camera);
	virtual void FinishedLoad (const OgreMax::OgreMaxScene* scene, bool success);
};