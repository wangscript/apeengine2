#ifndef _PHYSICSACTOR_H_
#define _PHYSICSACTOR_H_

#include "NxOgre.h"
//#include "GameComponent.h"
#include "Ogre.h"
#include "Physics.h"
//#include "PhysicsActor.h"
#include "OgreRender.h"
//#include "PhysicsActor.h"

#include "CRender.h"
#include "CMesh.h"
#include "CRoom.h"

#include "GameObject.h"

using namespace Ogre;

class GameObject;
class CRender;
class CMesh;
class CRoom;
//class PhysicsActor;
class Physics;
//class GameComponent;
class OgreRender;


class PhysicsActor : public NxOgre::Actor, public NxOgre::RenderableSource {
public:
	PhysicsActor(Ogre::String bodyType, NxOgre::Shape* shape, Ogre::String entityName,Ogre::String meshName, Ogre::Vector3 position,Ogre::Quaternion orientation,Ogre::Real restitution,Ogre::Real  staticFriction ,Ogre::Real dynamicFriction, NxOgre::ActorParams ap, bool isTrigger = false);
	~PhysicsActor();

	

/*
	void onStartTouch(Actor*, Actor*, NxOgre::ContactStream*);
	void onEndTouch(Actor*, Actor*, NxOgre::ContactStream*);
	void onTouch(Actor*, Actor*, NxOgre::ContactStream*);
*/
	void update();
	void setup();
	void setModel(Ogre::String modelName,Ogre::Vector3 modelPosition, Ogre::Quaternion modelOrientation);

	// Required by the RenderableSource. (Tells where the Actor is)
	NxOgre::Pose getSourcePose(const NxOgre::TimeStep&) const;

	// To work out what exactly the class is, if the pointer is passed
	// around as an Actor.
	NxOgre::NxShortHashIdentifier getType() const;

	// Same as above, but uses a String. It is slower to check this way.
	NxOgre::NxString getStringType() const;

	// Just providing a courtesy function.
	SceneNode* getNode();

	enum
	{
		FactoryIdentifier = 1337 // Unique identifier for RenderableActorFactory.
	};

	void create(const NxOgre::NxString& name, const NxOgre::Pose& pose,
		NxOgre::Shape* shape, NxOgre::Scene* scene,
		const NxOgre::NodeRenderableParams& visualParams //const 
		); //const NxOgre::ActorParams& params

	void setOwnerObject(GameObject*);
	GameObject* getOwnerObject();

	NxOgre::Shape* mShape;

	Ogre::Entity *mEntity;

	Ogre::SceneNode* mNode;

	Ogre::Real mRestitution;
	Ogre::Real mStaticFriction;
	Ogre::Real mDynamicFriction;


private:

	GameObject* mOwnerGO;

	Physics* mPhysics;
	OgreRender* mOgre;

	//PhysicsActor* mActor;
	NxOgre::Body* mBody;
	NxOgre::Actor* mActor;

	Ogre::String mShapeType;
	Ogre::String mEntityName;
	Ogre::String mPhysicsMeshName;
	Ogre::String mMeshName;
	Ogre::String mIsStatic;
	Ogre::String mBodyType;
	//bool mIsBody;
	Ogre::String mMass;
	Vector3 mShapeSize;
	//Ogre::String mName;

	NxOgre::ActorGroup* mGroup;
		
	
	Ogre::Vector3 mInitPosition;

	Ogre::String mModelMesh;
	Ogre::Entity *mModelEntity;
	Ogre::Quaternion mModelOrientation;
	Ogre::Vector3 mModelPosition;

	Ogre::String mParentName;
	bool mIsRootActor;

protected:

	NxOgre::NodeRenderable*			mNodeRenderable;
	NxOgre::OgreNodeRenderable*		mOgreNodeRenderable;

};

#endif
