#include "CActor.h"

/*static*/ 
const std::string CActor::mFamilyID = "CActor";
const std::string CActor::mComponentID = "CActor";

CActor::CActor(Ogre::String bodyType, Ogre::String entityName,Ogre::String meshName, Ogre::Vector3 position,Ogre::Quaternion orientation,Ogre::String actorParams)
{

	mPhysics = Physics::getSingleton().getSingletonPtr();
	mOgre = OgreRender::getSingleton().getSingletonPtr();

	//mShape = shape;
	mMeshName = meshName;
	mEntityName = entityName;
	
	mIsStatic = getParamValue("static",actorParams);
	mBodyType = bodyType;
	
	mPosition = position;
	mOrientation = orientation;	
}

Ogre::String CActor::getParamValue (Ogre::String paramName,Ogre::String param)
{
	string::size_type loc = param.find(paramName);

	if( loc != string::npos ) {
		Ogre::String paramValue;

		paramValue = param.substr(loc + paramName.length() + 1,paramName.length() - (loc + paramName.length()) );
		Ogre::String res = "";

		if(loc == 0) {
			paramValue = param.substr(paramName.length() + 1,param.length() - paramName.length() + 1);

		}

		Ogre::String::iterator i, iend;
		iend = paramValue.end();
		for (i = paramValue.begin(); i != iend; ++i)
		{
			if (*i != '\n' && (*i != '\r'))
				res += (*i);
			else
				break;
		}

		return res;
	}
	else
	{
		return "";
	}

	//Get rid of junk (with safty check)
	if (param.empty())
		throw Ogre::Exception (100, "Param empty.", "PhysicsCallback::getLastParam (Ogre::String param)");

	//Return
	return "";
}


void CActor::update() {

	
}
void CActor::linkActors() {


	//PhysicsActor* rootActor;

	std::map<const std::string, PhysicsActor*>::iterator GOActorsIter;

	mShape = NULL;

	mShape = new NxOgre::CompoundShape();

	Ogre::Real mass;
	Ogre::Real linearDamping;
	Ogre::Real angularDamping;
	Ogre::Real restitution;
	Ogre::Real dynamicFriction;
	Ogre::Real staticFriction;

	GOActorsIter = mActors.begin();
	while(GOActorsIter != mActors.end()) {
		Vector3 partPos = NxTools::convert(GOActorsIter->second->getGlobalPositionAsNxVec3());
		Vector3 actorPos = mPosition;
		Vector3 offsetPos = partPos - actorPos;

		//Vector3 p = NxTools::convert(GOActorsIter->second->mShape->mParams.mLocalPose.t);
		Ogre::String desc = "offset:" + Ogre::StringConverter::toString(offsetPos.x) + " " + Ogre::StringConverter::toString(offsetPos.y) + " " + Ogre::StringConverter::toString(offsetPos.z);
		
		NxOgre::ShapeParams sp;
		sp.setToDefault();
		sp.mLocalPose.t = NxTools::convert(offsetPos);
		sp.mLocalPose.M.fromQuat(GOActorsIter->second->getGlobalOrientationAsNxQuat());
		
		//NxMaterial* mat = Physics::getSingleton().getScene()->getNxScene()->getMaterialFromIndex(cube->getNxShape()->getMaterial());

		NxMaterialDesc matShapeDesc;

		//NxMaterial *tmpMaterial = Physics::getSingleton().getScene()->getNxScene()->getMaterialFromIndex(GOActorsIter->second->mShape->getNxShape()[0].getMaterial());

		matShapeDesc.restitution = GOActorsIter->second->mRestitution;
		matShapeDesc.staticFriction = GOActorsIter->second->mStaticFriction;
		matShapeDesc.dynamicFriction = GOActorsIter->second->mDynamicFriction;
				

		NxMaterial *newMaterial=Physics::getSingleton().getScene()->getNxScene()->createMaterial(matShapeDesc); 

		sp.mMass = GOActorsIter->second->getMass();
		
		linearDamping = GOActorsIter->second->getLinearDamping();
		angularDamping = GOActorsIter->second->getAngularDamping();
		mass = GOActorsIter->second->getMass();

		NxMaterial *tmpMaterial = Physics::getSingleton().getScene()->getNxScene()->getMaterialFromIndex(GOActorsIter->second->mShape->getNxShape()[0].getMaterial());
		dynamicFriction = tmpMaterial->getDynamicFriction();
		staticFriction = tmpMaterial->getStaticFriction();
		restitution = tmpMaterial->getRestitution();

		sp.mMaterial = newMaterial->getMaterialIndex();

		if(GOActorsIter->second->mShape->getNxShape()->isBox()) {
			NxOgre::Cube* cube = (NxOgre::Cube*)GOActorsIter->second->mShape;
			NxVec3 dim = cube->getDimensions();	
			
			//cube->getMaterial()
			//mat = Physics::getSingleton().getScene()->getNxScene()->getMaterialFromIndex(cube->getNxShape()->getMaterial());			

			mShape->add(new NxOgre::Cube(NxTools::convert(dim),sp)); // new Cube(1,1,1,sp)
		}

		if(GOActorsIter->second->mShape->getNxShape()->isCapsule()) {
			NxOgre::Capsule* cap = (NxOgre::Capsule*)GOActorsIter->second->mShape;
			NxVec3 dim;
			
			dim.x = GOActorsIter->second->mShape->getNxShape()->isCapsule()->getHeight();
			dim.y = GOActorsIter->second->mShape->getNxShape()->isCapsule()->getRadius();

			//mat = Physics::getSingleton().getScene()->getNxScene()->getMaterialFromIndex(cap->getNxShape()->getMaterial());

			mShape->add(new NxOgre::Capsule(dim.y,dim.x,sp)); // new Cube(1,1,1,sp)
			
		}

		if(GOActorsIter->second->mShape->getNxShape()->isSphere()) {
			NxOgre::Sphere* sphere = (NxOgre::Sphere*)GOActorsIter->second->mShape;
			NxVec3 dim;

			dim.x = GOActorsIter->second->mShape->getNxShape()->isSphere()->getRadius();

			//mat = Physics::getSingleton().getScene()->getNxScene()->getMaterialFromIndex(sphere->getNxShape()->getMaterial());

			mShape->add(new NxOgre::Sphere(dim.x,sp)); // new Cube(1,1,1,sp)
			
		}
		
		//mat->setDynamicFriction(1.0f);
		//mat->setStaticFriction(1.0f);
		
		GOActorsIter->second->_destroyActor();

		GOActorsIter++;
	}

	/*
	SceneNode::ChildNodeIterator it = OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->getChildIterator();
	Ogre::LogManager::getSingleton().logMessage("##### Root -" );
	while(it.hasMoreElements())
	{
		Node* obj = it.getNext();
		Ogre::LogManager::getSingleton().logMessage("##### CActor-> Child -" + obj->getName() );
	} 
	*/

	NxOgre::ActorParams ap("mass:" + Ogre::StringConverter::toString(mass));


	mPhysicsActor = new PhysicsActor("Body",mShape,mEntityName,mMeshName,mPosition,mOrientation,restitution,staticFriction,dynamicFriction,ap); //lastParams

	mPhysicsActor->setLinearDamping(linearDamping);
	mPhysicsActor->setAngularDamping(angularDamping);

	//mPhysicsActor->
	mPhysicsActor->setModel(mMeshName,mPosition,mOrientation);
	mPhysicsActor->setup();
	mPhysicsActor->setOwnerObject(this->getOwnerObject());

	CWeapon* weapon = dynamic_cast<CWeapon*>(this->getOwnerObject()->getComponent("CWeapon"));
	if(weapon) {
		weapon->updateNode();
	}
}
void CActor::setup() {
	//PhysicsActor* mActor = new PhysicsActor()

	CPosition *mCPosition = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
	COrientation *mCOrientation = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));
	CMesh *mCMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	CRender *mCRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	CRoom *mCRoom = dynamic_cast<CRoom*>(getOwnerObject()->getComponent("CRoom"));


}

// Destructor. Clean anything you have custom in here.
CActor::~CActor() {
	/*
	mOwner->getSceneRenderer()->unregisterSource(this);
	if (mRenderable) {
		delete mRenderable;
		mRenderable = 0;
	}
	*/
}
