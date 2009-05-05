#ifndef _CPHYSICSACTOR_H_
#define _CPHYSICSACTOR_H_

#include "GameComponent.h"
#include "Ogre.h"
#include "NxOgre.h"
//#include "UserAllocator.h"

using namespace Ogre;
//using namespace NxOgre;

//class UserAllocator;

class PhysicsActor : public NxOgre::Actor, public NxOgre::RenderableSource  {

public:

	PhysicsActor(const NxOgre::NxString& name, const NxOgre::Pose& pose,
		NxOgre::Shape* shape, NxOgre::Scene* scene,
		const NxOgre::NodeRenderableParams& visualParams, //const 
		const NxOgre::ActorParams& params);

	// Destructor. Clean anything you have custom in here.
	~PhysicsActor();

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

protected:

	NxOgre::NodeRenderable*			mNodeRenderable;
	NxOgre::OgreNodeRenderable*		mOgreNodeRenderable;

};

#endif