#ifndef _CACTOR_H_
#define _CACTOR_H_

#include "NxOgre.h"
#include "GameComponent.h"
#include "Ogre.h"
#include "Physics.h"
//#include "PhysicsActor.h"
#include "OgreRender.h"
//#include "PhysicsActor.h"

#include "CRender.h"
#include "CMesh.h"
#include "CRoom.h"


using namespace Ogre;

class CRender;
class CMesh;
class CRoom;
//class PhysicsActor;
class Physics;
class GameComponent;
class OgreRender;


class CActor : public GameComponent, public NxOgre::Actor, public NxOgre::RenderableSource {
public:
	

	//CActor::CActor(Ogre::String bodyType, Ogre::String shapeType, Vector3 shapeSize,Ogre::String entityName,Ogre::String meshName, Ogre::String isStatic,Ogre::String mass);
	
	CActor::CActor(Ogre::String bodyType, NxOgre::Shape* shape, Ogre::String entityName,Ogre::String meshName, Ogre::Vector3 position,Ogre::Quaternion orientation,Ogre::String actorParams);

	//CActor::CActor(Ogre::String bodyType, Ogre::String shapeType, Vector3 shapeSize,Ogre::String entityName,Ogre::String meshName, Ogre::String isStatic,Ogre::String mass);

	/*
	const NxOgre::NxString& name, const NxOgre::Pose& pose,
		NxOgre::Shape* shape, NxOgre::Scene* scene,
		const NxOgre::NodeRenderableParams& visualParams, //const 
		const NxOgre::ActorParams& params
	*/

	~CActor();

	void update();
	void setup();

	bool isStatic() {
		return (mIsStatic == "yes");
	}
	bool isBody() {
		return (mBodyType == "Body");
	}

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}

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

private:
	static const std::string mFamilyID;
	static const std::string mComponentID;


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

	Ogre::Entity *mEntity;
	Ogre::SceneNode* mNode;
	NxOgre::Shape* mShape;

protected:

	NxOgre::NodeRenderable*			mNodeRenderable;
	NxOgre::OgreNodeRenderable*		mOgreNodeRenderable;

};

#endif
