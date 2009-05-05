#include "PhysicsActor.h"
#include "OgreRender.h"

PhysicsActor::PhysicsActor(const NxOgre::NxString& name, const NxOgre::Pose& pose,
		NxOgre::Shape* shape, NxOgre::Scene* scene,
		const NxOgre::NodeRenderableParams& visualParams, //const 
		const NxOgre::ActorParams& params) : NxOgre::Actor(name, scene, shape, pose, params)
	{

	//NodeRenderableParams renderParams;
	//renderParams.setToDefault();
	//visualParams.mGraphicsModel = vi.getVisualIdentifier();
	//visualParams.mGraphicsModelScale = NxVec3(1, 1, 1);
	//visualParams.mIdentifier = vi.getIdentifier();
	//visualParams.mIdentifierUsage = NxOgre::NodeRenderableParams::IU_Use;
	//visualParams.mMode = RenderableSource::RM_Interpolate; 

	// Create the NodeRenderable based of the Params. The outcome is
	// based on the Renderer used (specified in the Scene).
	
	Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(visualParams.mIdentifier, visualParams.mGraphicsModel);
	Ogre::SceneNode* sn = OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode(visualParams.mIdentifier);
	sn->attachObject(ent);

	mRenderable = mOwner->getSceneRenderer()->createNodeRenderable(visualParams);
	mNodeRenderable = static_cast<NxOgre::NodeRenderable*>(mRenderable);
	mVoidPointer->RenderPtr = this;

	// Set the Render mode to Interpolate. (Interpolation is handled
	// somewhere else, and is out of the scope of the TestActor).
	setRenderMode(RM_Interpolate);

	// You can use the NodeRenderable functions to mirror most or if
	// not all of the actual RenderSystem's NodeRenderable functions
	// but in some instances you can't. But you can cast it into another,
	// if you have to.
	if (mNodeRenderable->getHashType() == NxOgre::NxOgreClass_OgreNodeRenderable)
		mOgreNodeRenderable = static_cast<NxOgre::OgreNodeRenderable*>(mNodeRenderable);

	// Tell the Scene to render this Actor, every simulation.
	mOwner->getSceneRenderer()->registerSource(this);

	// Usually at this point, it may be best to use any NxOgre classes that
	// require you to watch collisions, join
	// to other actors, or anything else.

}


// Destructor. Clean anything you have custom in here.
PhysicsActor::~PhysicsActor() {
	mOwner->getSceneRenderer()->unregisterSource(this);
	if (mRenderable) {
		delete mRenderable;
		mRenderable = 0;
	}
}

// Required by the RenderableSource. (Tells where the Actor is)
NxOgre::Pose PhysicsActor::getSourcePose(const NxOgre::TimeStep&) const {
	return getGlobalPose();
}

// To work out what exactly the class is, if the pointer is passed
// around as an Actor.
NxOgre::NxShortHashIdentifier PhysicsActor::getType() const {
	return 12345;
}

// Same as above, but uses a String. It is slower to check this way.
NxOgre::NxString PhysicsActor::getStringType() const {
	return "PhysicsActor";
}

// Just providing a courtesy function.
SceneNode* PhysicsActor::getNode() {
	return mOgreNodeRenderable->getNode();
}
