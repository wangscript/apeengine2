#include "CAI.h"
#include "AIManager.h"
#include "CRender.h"
#include "CAnimation.h"

/*static*/ 
const std::string CAI::mFamilyID = "CAI";
const std::string CAI::mComponentID = "CAI";

//CAI::CAI(Pedestrian* mPed) //ProximityDatabase& pd  : Pedestrian(pd)
CAI::CAI(OpenSteer::AbstractVehicle* mPed)
{


	//this = (newPedestrian);
	//Position = Vector3(0,0,0);
	mPedestrian = mPed;

	//mPedestrian->reset();
	//mPedestrian->setPosition(Vec3(0,0,0));
	//mPedestrian->setRadius(6.0);
	//mPedestrian->set
	//mPedestrian->setMaxSpeed(740); //240
	//mPedestrian->setMass(0.01); //0.01
	
	//Vec3 p = mPedestrian->position();
	//mPedestrian->set
	//mPedestrian->setRadius();
}

CAI::~CAI()
{

}

void CAI::update() {
/*
	if(mNode) {
		
		Ogre::Vector3 p = Ogre::Vector3(mPedestrian->position().x,mPedestrian->position().y,mPedestrian->position().z);
		p.y = EditableTerrain::getSingleton().getTerrainHeightAt(p.x,p.z);
		//p.y = 100;
		mNode->setPosition(p);

		Ogre::Vector3 forwDir = Ogre::Vector3(mPedestrian->forward().x, mPedestrian->forward().y, mPedestrian->forward().z);
		//forwDir.normalise();
		

		mNode->setDirection(forwDir, Ogre::SceneNode::TS_WORLD, Ogre::Vector3::UNIT_Z);

		CAnimation* mCAnim = dynamic_cast<CAnimation*>(getOwnerObject()->getComponent("CAnimation"));
		if(mCAnim)
			mCAnim->updateAnimation();	

	}
*/
	updateVehicle();
}

void CAI::updateVehicle() {

	if(mNode) {

		Ogre::Vector3 p = Ogre::Vector3(mPedestrian->position().x,mPedestrian->position().y,mPedestrian->position().z);
		p.y = EditableTerrain::getSingleton().getTerrainHeightAt(p.x,p.z);
		//p.y = 100;
		mNode->setPosition(p);

		Ogre::Vector3 forwDir = Ogre::Vector3(mPedestrian->forward().x, mPedestrian->forward().y, mPedestrian->forward().z);
		forwDir.normalise();


		mNode->setDirection(forwDir, Ogre::SceneNode::TS_WORLD, Ogre::Vector3::UNIT_Z);

		CAnimation* mCAnim = dynamic_cast<CAnimation*>(getOwnerObject()->getComponent("CAnimation"));
		if(mCAnim)
			mCAnim->updateAnimation();	

	}

}

void CAI::setup() {
	//mNode = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"))->mNode;
	


}

void CAI::setDefaultAnimation() {
	CAnimation* mCAnim = dynamic_cast<CAnimation*>(getOwnerObject()->getComponent("CAnimation"));
	if(mCAnim) {
		mCAnim->setAnimState(START_WALK);	
		mCAnim->updateAnimation();
		Ogre::Real initTime = mCAnim->getAnim(START_WALK)->getAnimation()->getLength();
		mCAnim->getAnim(START_WALK)->getAnimation()->setTimePosition(Ogre::Math::RangeRandom(0,initTime));

	}
}