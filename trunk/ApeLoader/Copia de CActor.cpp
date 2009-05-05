#include "CActor.h"

/*static*/ 
const std::string CActor::mFamilyID = "CActor";
const std::string CActor::mComponentID = "CActor";

//Ogre::String shapeType,	Ogre::String meshFileName, bool isDynamic, bool isBody,	Real mass, Vector3 shapeSize, Ogre::String name
CActor::CActor(Ogre::String bodyType, NxOgre::Shape* shape, Ogre::String entityName,Ogre::String meshName, Ogre::Vector3 position,Ogre::Quaternion orientation,Ogre::String actorParams)  : NxOgre::Actor(entityName, Physics::getSingleton().getScene(),shape, position, actorParams)
{

	//Position = Vector3(600,300,280);
	//Position = Vector3(0,0,0);
	mPhysics = Physics::getSingleton().getSingletonPtr();
	mOgre = OgreRender::getSingleton().getSingletonPtr();

	mShape = shape;

	this->setGlobalOrientation(orientation);

	//mShapeType = shapeType;
	//mIsStatic = isStatic;
	//mMass = mass;
	//mShapeSize = shapeSize;
	mMeshName = meshName;
	//mPhysicsMeshName = meshName + ".nxs";
	mEntityName = entityName;
	//mBodyType = bodyType;
}
/*
CActor::~CActor()
{

}
*/

void CActor::update() {

	
	//aReal time = mOgre->getTimeSinceLastFrame();
	//aTimeStep ts;
	//ats.Delta = time;
	//amActor->render(ts);
	
}

void CActor::setup() {
	//PhysicsActor* mActor = new PhysicsActor()

	CPosition *mCPosition = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
	COrientation *mCOrientation = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));
	CMesh *mCMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	CRender *mCRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	CRoom *mCRoom = dynamic_cast<CRoom*>(getOwnerObject()->getComponent("CRoom"));

	/*
	NxOgre::Shape* shape;
	//shape = getShape(mPhysicsMeshName,mShapeType,mShapeSize);

	Ogre::String firstParams = mEntityName + ";" + mMeshName;
	Ogre::String lastParams;

	if(mMass != "")
		lastParams = "mass:" + mMass;

	if(mIsStatic == "yes") {
		if(lastParams != "")
			lastParams += ",";

		lastParams += "static:yes";
	}
*/
	//NxOgre::Body* mActor;
	
	//if(mBodyType == "Body") {
	if(this->getNxActor()->isDynamic()) {
		/*
		mBody = Physics::getSingleton().getScene()->createBody(firstParams,shape,mCPosition->Position,lastParams);
		mBody->setGlobalOrientation(mCOrientation->Orientation);
		
		Ogre::Entity *mEnt = (Entity*) static_cast<NxOgre::OgreNodeRenderable*>(mBody->getRenderable())->getNode()->getAttachedObject(0);				
		Ogre::SceneNode *mSN = static_cast<NxOgre::OgreNodeRenderable*>(mBody->getRenderable())->getNode();
		mCRender->setNode(mSN);
		mCMesh->mEntity = mEnt;
		mBodyType = "Body";
		*/

		//mBody->getNxActor()->userData = getOwnerObject();

		//VoidPointer* vp = static_cast<VoidPointer>(nx_actor->userData);
		//Actor* actor = vp->toActor();
		

		//NxOgre::ActorParams ap;
		//ap.setToDefault();
		//ap.
		
		//VisualIdentifier vi = VisualIdentifier(;
		
/*
		NodeRenderableParams renderParams;
		renderParams.setToDefault();
		renderParams.mGraphicsModel = vi.getVisualIdentifier();
		renderParams.mGraphicsModelScale = NxVec3(1, 1, 1);
		renderParams.mIdentifier = ""; // vi.getIdentifier();
		renderParams.mIdentifierUsage = renderParams.IU_Use;
		renderParams.mMode = RenderableSource::RM_Interpolate; 
*/

		NxOgre::NodeRenderableParams visualParams;
		visualParams.setToDefault();
		visualParams.mGraphicsModel = mMeshName;
		visualParams.mGraphicsModelScale = NxVec3(1, 1, 1);
		visualParams.mIdentifier = mEntityName; // vi.getIdentifier();
		visualParams.mIdentifierUsage = NxOgre::NodeRenderableParams::IU_Use;
		visualParams.mMode = NxOgre::RenderableSource::RM_Interpolate; 

		create(mEntityName + "newBody1",mCPosition->Position,mShape,mPhysics->getScene(),visualParams);

		//this->get
		//NxActor* act = mScene->getNxScene()->createActor(actorDesc);

		//(Actor*)(this)->
		
		NxMaterial* mat = Physics::getSingleton().getScene()->getNxScene()->getMaterialFromIndex(mShape->getNxShape()->getMaterial());
		mat->setDynamicFriction(1.0f);
		mat->setStaticFriction(1.0f);

		
		//NxShape* const* shape = act->getShapes();
		//NxMaterial* mat = mScene->getNxScene()->getMaterialFromIndex((*shape)->getMaterial());

		//this->
		/*
		PhysicsActor* pa = new PhysicsActor(mEntityName + "newBody1",mCPosition->Position,shape,mPhysics->getScene(),visualParams,lastParams);
		*/

	} else {
		/*
		mActor = Physics::getSingleton().getScene()->createActor(firstParams,shape,mCPosition->Position,lastParams);
		mActor->setGlobalOrientation(mCOrientation->Orientation);
		mBodyType = "Actor";
		*/
		//Ogre::SceneNode *mSN = static_cast<NxOgre::OgreNodeRenderable*>(mActor->getRenderable())->getNode();
		//mCRender->setNode(mSN);
		//mCMesh->mEntity = mEnt;

	}


}
/*
NxOgre::Shape* CActor::getShape (Ogre::String mMeshName,Ogre::String mShapeType,Ogre::Vector3 mShapeSize)
{
	if (mShapeType == "EditableMesh")
	{
		return getTriangle(mMeshName);
	}
	if (mShapeType == "Box")
	{
		return new NxOgre::Cube(mShapeSize.x,mShapeSize.y,mShapeSize.z);
	}

	if (mShapeType == "Sphere")
	{
		return new NxOgre::Sphere(mShapeSize.x);
	}
	if (mShapeType == "Capsule")
	{
		return new NxOgre::Capsule(mShapeSize.x,mShapeSize.y);
	}
	Ogre::LogManager::getSingleton().logMessage("||WARNING! Default shape used. ||");
	return new NxOgre::Cube (10);
}
*/
/*
NxOgre::Convex* CActor::getConvex(Ogre::String &param)
{
	//Ogre::String meshName = getMeshName(param);
	Ogre::String outFile = param;
	Ogre::String mpath = "file://../../media/models/" + outFile;

	try {
		NxOgre::Resources::ResourceSystem::getSingleton()->addMeshAs(mpath,outFile); 
	} catch (exception& e) {
		Ogre::LogManager::getSingleton().logMessage("||ERROR - addMeshAs() - path:" + mpath + " - outFile: " + outFile);
	}

	//Ogre::String path = "../../media/models/Penalty/" + meshName + "nxs";
	NxOgre::Convex* _mesh;
	try {
		_mesh = new NxOgre::Convex(NxOgre::Resources::ResourceSystem::getSingleton()->getMesh(outFile));
	} catch(exception& e) {
		//return false;
		Ogre::LogManager::getSingleton().logMessage("||ERROR - getMesh() - Convex mesh. FileName:" + mpath + " - Mesh Name: " + outFile);
	}
	return _mesh;
}
NxOgre::TriangleMesh* CActor::getTriangle(Ogre::String &param)
{

	//Ogre::String meshName = getMeshName(param);
	Ogre::String outFile = param;
	Ogre::String mpath = "file://../../media/models/" + outFile;

	try {
		NxOgre::Resources::ResourceSystem::getSingleton()->addMeshAs(mpath,outFile); 
	} catch (exception& e) {
		Ogre::LogManager::getSingleton().logMessage("||ERROR - addMeshAs() - path:" + mpath + " - outFile: " + outFile);
	}

	//Ogre::String path = "../../media/models/Penalty/" + meshName + "nxs";
	NxOgre::TriangleMesh* _mesh;
	try {
		_mesh = new NxOgre::TriangleMesh(NxOgre::Resources::ResourceSystem::getSingleton()->getMesh(outFile));
	} catch(exception& e) {
		//return false;
		Ogre::LogManager::getSingleton().logMessage("||ERROR - getMesh() - Triangle mesh. FileName:" + mpath + " - Mesh Name: " + outFile);
	}
	return _mesh;
}
*/
// Destructor. Clean anything you have custom in here.
CActor::~CActor() {
	mOwner->getSceneRenderer()->unregisterSource(this);
	if (mRenderable) {
		delete mRenderable;
		mRenderable = 0;
	}
}

// Required by the RenderableSource. (Tells where the Actor is)
NxOgre::Pose CActor::getSourcePose(const NxOgre::TimeStep&) const {
	return getGlobalPose();
}

// To work out what exactly the class is, if the pointer is passed
// around as an Actor.
NxOgre::NxShortHashIdentifier CActor::getType() const {
	return 12345;
}

// Same as above, but uses a String. It is slower to check this way.
NxOgre::NxString CActor::getStringType() const {
	return "PhysicsActor";
}

// Just providing a courtesy function.
SceneNode* CActor::getNode() {
	return mOgreNodeRenderable->getNode();
}

void CActor::create(const NxOgre::NxString& name, const NxOgre::Pose& pose,
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

