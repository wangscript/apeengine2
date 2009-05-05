#include "PhysicsActor.h"

#include "ZoneManager.h"

PhysicsActor::PhysicsActor(Ogre::String bodyType, NxOgre::Shape* shape, Ogre::String entityName,Ogre::String meshName, Ogre::Vector3 position,Ogre::Quaternion orientation,Ogre::Real restitution,Ogre::Real  staticFriction ,Ogre::Real dynamicFriction,NxOgre::ActorParams ap, bool isTrigger)  : NxOgre::Actor(entityName, Physics::getSingleton().getScene(),shape, position,ap)
{

	mPhysics = Physics::getSingleton().getSingletonPtr();
	mOgre = OgreRender::getSingleton().getSingletonPtr();

	mShape = shape;
	
	if(isTrigger) {
		//mShape->getNxShape()->setFlag(NX_TRIGGER_ENABLE,true);
		//this->set
	}

	//if(!this->isDynamic())
	
	this->setGlobalOrientation(orientation);
	
	//mModelOrientation = orientation;

	this->setGlobalPosition(position);
	
	//mGroup = Physics::getSingleton().getScene()->getActorGroup("dynamic_group");
	//mGroup->setCallback(this);
	//mShape->getNxShape()->se
	//mGroup->setCollisionCallback(segGrupo, NX_NOTIFY_ALL, true);
	
	if(!isDynamic()) {
		this->setGroup(Physics::getSingleton().getScene()->getActorGroup("static_group"));
		//Physics::getSingleton().getScene()->getActorGroup("dynamic_group")->setCallback(this);
	} else {
		this->setGroup(Physics::getSingleton().getScene()->getActorGroup("dynamic_group"));
		//Physics::getSingleton().getScene()->getActorGroup("dynamic_group")->setCallback(this);
	}



	//this->setGroup(1);
	//this->mShape->getNxShape()->
	
	//Physics::getSingleton().getScene()->getNxScene()->getGro

	//if(this->isDynamic())
	//	this->raiseActorFlag(NxActorFlag::NX_AF_DISABLE_COLLISION);
	mRestitution = restitution;
	mStaticFriction = staticFriction;
	mDynamicFriction = dynamicFriction;

	mMeshName = meshName;
	mEntityName = entityName;
	mInitPosition = position;
	//mModelMesh = modelMesh;
}
/*
void PhysicsActor::onStartTouch(Actor*, Actor*, NxOgre::ContactStream*) {
	
}
void PhysicsActor::onEndTouch(Actor*, Actor*, NxOgre::ContactStream*) {
	
}
void PhysicsActor::onTouch(Actor*, Actor*, NxOgre::ContactStream*) {
	
}
*/
void PhysicsActor::update() {
		
}

void PhysicsActor::setModel(Ogre::String modelName,Ogre::Vector3 modelPosition, Ogre::Quaternion modelOrientation) {
	mMeshName = modelName;
	mModelOrientation = modelOrientation;
	mModelPosition = modelPosition;
}


void PhysicsActor::setup() {

/*
	CPosition *mCPosition = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
	COrientation *mCOrientation = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));
	CMesh *mCMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	CRender *mCRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	CRoom *mCRoom = dynamic_cast<CRoom*>(getOwnerObject()->getComponent("CRoom"));
*/
	if(this->getNxActor()->isDynamic()) {
		NxOgre::NodeRenderableParams visualParams;
		visualParams.setToDefault();
		visualParams.mGraphicsModel = mMeshName;
		visualParams.mGraphicsModelScale = NxVec3(1, 1, 1);
		visualParams.mIdentifier = mEntityName; // vi.getIdentifier();
		visualParams.mIdentifierUsage = NxOgre::NodeRenderableParams::IU_Use;
		visualParams.mMode = NxOgre::RenderableSource::RM_Interpolate; 

		create(mEntityName + "newBody1",mInitPosition,mShape,mPhysics->getScene(),visualParams);

		/*
		NxMaterial* mat = Physics::getSingleton().getScene()->getNxScene()->getMaterialFromIndex(mShape->getNxShape()->getMaterial());
		mat->setDynamicFriction(1.0f);
		mat->setStaticFriction(1.0f);
		*/

	} else {
		mNode = (PCZSceneNode*)OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode(mEntityName);
		mNode->setPosition(mModelPosition);
	}


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

void PhysicsActor::create(const NxOgre::NxString& name, const NxOgre::Pose& pose,
						   NxOgre::Shape* shape, NxOgre::Scene* scene,
						   const NxOgre::NodeRenderableParams& visualParams //const 
						   ) //const NxOgre::ActorParams& params
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

	/*
	SceneNode::ChildNodeIterator it = OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->getChildIterator();
	Ogre::LogManager::getSingleton().logMessage("##### Root -" );
	while(it.hasMoreElements())
	{
		Node* obj = it.getNext();
		Ogre::LogManager::getSingleton().logMessage("##### PhysicsActor-> Child -" + obj->getName() );
	} 
	*/

	//OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->getChild()
	Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(visualParams.mIdentifier, visualParams.mGraphicsModel);
	//Ogre::Entity* entModel = OgreRender::getSingleton().getSceneManager()->createEntity(visualParams.mIdentifier,mModelMesh);
	
	SceneNode* rootNode = OgreRender::getSingleton().getSceneManager()->getRootSceneNode();

	SceneNode* sn;
	//SceneNode* sn;

	//Ogre::SceneNode*  
	//(PCZSceneNode*)
	sn = rootNode->createChildSceneNode(visualParams.mIdentifier);
	//sn = (ZoneManager::getSingleton().getRootSceneNode()->createChildSceneNode(visualParams.mIdentifier));
	
	//PCZSceneManager* pczsm = ZoneManager::getSingletonPtr();
	//sn = (SceneNode*)pczsm->createSceneNode(visualParams.mIdentifier);
//pczsm->
	//sn = (OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode(visualParams.mIdentifier));

	//PCZSceneNode* entNode;
	//Comentado
	SceneNode* entNode;

	//Ogre::SceneNode* 
	//comentado
	entNode = sn->createChildSceneNode(visualParams.mIdentifier + "_Child");
	
	//entNode->setOrientation(mModelOrientation * Quaternion(Degree(90), Vector3::NEGATIVE_UNIT_Y) );
	//entNode->setOrientation(mModelOrientation);

	//Comentado
	entNode->attachObject(ent);
	
	mEntity = ent;

	//Comentado
	mNode = entNode; //entNode;
	//mNode = sn; //entNode;

	sn->setOrientation(mModelOrientation);

	//mNode->setOrientation(mModelOrientation);

	//if(mModelEntity)
	//sn->attachObject(ent);

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

void PhysicsActor::setOwnerObject(GameObject* owner) {
	mOwnerGO = owner;
}

GameObject* PhysicsActor::getOwnerObject() {
	return mOwnerGO;
}

