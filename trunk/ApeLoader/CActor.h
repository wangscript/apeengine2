#ifndef _CACTOR_H_
#define _CACTOR_H_

#include "NxOgre.h"
#include "GameComponent.h"
#include "Ogre.h"
#include "Physics.h"
#include "PhysicsActor.h"
#include "OgreRender.h"
#include "CRender.h"
#include "CMesh.h"
#include "CRoom.h"
#include "CWeapon.h"

using namespace Ogre;

class GameComponent;
class Physics;
class PhysicsActor;
class OgreRender;
class CRender;
class CMesh;
class CRoom;
class CWeapon;

class CActor : public GameComponent {
public:
	
	std::map<const std::string, PhysicsActor*> mActors; 
	unsigned int mNumActors;

	PhysicsActor* mPhysicsActor;

	//CActor::CActor(Ogre::String bodyType, Ogre::String shapeType, Vector3 shapeSize,Ogre::String entityName,Ogre::String meshName, Ogre::String isStatic,Ogre::String mass);
	
	CActor::CActor(Ogre::String bodyType, Ogre::String entityName,Ogre::String meshName, Ogre::Vector3 position,Ogre::Quaternion orientation,Ogre::String actorParams);

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
		if(mIsStatic != "")
			return true;
		else
			return false;
	}

	
	bool isBody() {
		return (mBodyType == "Body");
	}
	

	Ogre::String getParamValue (Ogre::String paramName,Ogre::String param);
	void linkActors();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
/*
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
*/
private:
	static const std::string mFamilyID;
	static const std::string mComponentID;


	Physics* mPhysics;
	OgreRender* mOgre;

	//PhysicsActor* mActor;
	NxOgre::Body* mBody;
	NxOgre::Actor* mActor;

	std::string mRootActor;

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
	NxOgre::CompoundShape* mShape;

	Ogre::Vector3 mPosition;
	Ogre::Quaternion mOrientation;

	

protected:
	

//	NxOgre::NodeRenderable*			mNodeRenderable;
//	NxOgre::OgreNodeRenderable*		mOgreNodeRenderable;

};

#endif
