#include "CRoom.h"

/*static*/ 
const std::string CRoom::mFamilyID = "CRoom";
const std::string CRoom::mComponentID = "CRoom";

CRoom::CRoom(Vector3 roomSize,Ogre::String name, Ogre::String cameraName) : mRoomZone(0)
{
	//Position = Vector3(600,300,280);
	//Position = Vector3(0,0,0);
	mRoomSize = roomSize;
	mName = name;
	mCameraName = cameraName;
}
CRoom::~CRoom()
{

}

void CRoom::update() {

}

void CRoom::createBoxTrigger(Ogre::Vector3 boxSize)
{

	CPosition *mCPosition = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
	COrientation *mCOrientation = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));

	// Our trigger is a cube
	NxBodyDesc triggerBody;
	NxBoxShapeDesc dummyShape;
	NxBoxShapeDesc BoxDesc;
	BoxDesc.dimensions		= NxVec3(boxSize.x/4, boxSize.y/4, boxSize.z/4);
	BoxDesc.shapeFlags		|= NX_TRIGGER_ENABLE;
	BoxDesc.shapeFlags |= NX_BF_KINEMATIC;

	NxActorDesc ActorDesc;

	ActorDesc.shapes.pushBack(&BoxDesc);
	ActorDesc.globalPose.t = NxVec3(mCPosition->Position.x,mCPosition->Position.y,mCPosition->Position.z);
	
	//NxQuat q = NxQuat(NxReal(mCOrientation->Orientation.x),NxReal(mCOrientation->Orientation.y),NxReal(mCOrientation->Orientation.z),NxReal(mCOrientation->Orientation.w));

	//ActorDesc.globalPose.M.fromQuat(q);

	NxScene* scene = Physics::getSingleton().getScene()->getNxScene();

	mActor = scene->createActor(ActorDesc);	// This is just a quick-and-dirty way to identify the trigger for rendering
	
	NxReal angle = mCOrientation->Orientation.w;
	NxVec3 vec = NxVec3(mCOrientation->Orientation.x,mCOrientation->Orientation.y,mCOrientation->Orientation.z);

	//NxQuat q = NxQuat(angle,vec);
	//mActor->setGlobalOrientationQuat(q);

	//NxVec3 pos = NxVec3(mCPosition->Position.x,mCPosition->Position.y,mCPosition->Position.z);
	//mActor->setGlobalPosition(pos);
	mActor->userData = (void*)this->getOwnerObject();
	
	//scene->setUserTriggerReport(this);
}

//void CRoom::onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status)
//{
//	// other actor is a trigger too?
//	//if ((NxI32)(otherShape.getActor().userData) < 0)
//	//	return;
//
//	NxActor& triggerActor = triggerShape.getActor();
//	//NxI32 triggerNumber = -(NxI32)triggerActor.userData;
//	//NxI32 triggerIndex = triggerNumber - 1;
//
//	if(status & NX_TRIGGER_ON_ENTER)
//	{
//		// A body entered the trigger area for the first time
//		//	gNbTouchedBodies[triggerIndex]++;
//		OgreRender::getSingleton().getDebugText()->addText("On_Enter: " + Ogre::StringConverter::toString(triggerShape.getName()));
//	}
//	if(status & NX_TRIGGER_ON_LEAVE)
//	{
//		// A body left the trigger area
//		//	gNbTouchedBodies[triggerIndex]--;
//		OgreRender::getSingleton().getDebugText()->addText("On_Leave: " + Ogre::StringConverter::toString(triggerShape.getName()));
//	}
//	//NX_ASSERT(gNbTouchedBodies[triggerIndex]>=0);	//Shouldn't go negative
//}

void CRoom::setup() {
	//CPosition *mCPosition = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
	//COrientation *mCOrientation = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));
	
	//NxOgre::ActorParams ap("static: yes");
	//mActor = new PhysicsActor("Body",new NxOgre::Cube(mRoomSize.x/2,mRoomSize.y/2,mRoomSize.z/2),mName,"cube.1m.mesh",mCPosition->Position,mCOrientation->Orientation,0,0,0,ap); //lastParams

	//mActor->setGlobalOrientation(mCOrientation->Orientation);
	//mActor->setGlobalPosition(mCPosition->Position);
	//mActor->raiseActorFlag(NxActorFlag::NX_AF_DISABLE_COLLISION);
	//mActor->setGroup(Physics::getSingleton().getScene()->getActorGroup("static_group"));


	createBoxTrigger(mRoomSize);
}
