#include "CRender.h"

namespace Nebula {
	CRender::CRender()
	{
		mComponentID = "CRender";
	}

	CRender::CRender(const CRenderDesc& desc)
	{
		mComponentID = "CRender";
		mDesc = desc;
		mRotating = false;
	}

	CRender::~CRender()
	{

	}
	
	Real CRender::getDistanceToActor(CPhysicsActor* actor) {
		Vector3 actorPos = NxTools::convert(actor->getNxActor()->getGlobalPosition());
		Vector3 thisActorPos;

		if(mNode)
			thisActorPos = mNode->_getDerivedPosition();
		else
			return 0;
		
		return thisActorPos.distance(actorPos);
	}

	Real CRender::getDistanceToCharacter(CCharacterController* character) {
		Vector3 characterPos = character->getCharacterPosOgre();
		Vector3 thisActorPos;
		
		if(mNode)
			thisActorPos = mNode->_getDerivedPosition();
		else
			return 0;

		Ogre::Real dist = thisActorPos.distance(characterPos);

		return dist;
	}

	Real CRender::getDistanceToTrigger(CPhysicsTrigger* trigger) {
		Vector3 triggerPos = NxTools::convert(trigger->getNxActor()->getGlobalPosition());
		Vector3 thisActorPos;
		
		if(mNode)
			thisActorPos = mNode->_getDerivedPosition();
		else
			return 0;

		return thisActorPos.distance(triggerPos);
	}

	void CRender::setOrientationDestination(Quaternion q) {
		mOrientDest = q;
	}

	void CRender::update() {
		
		//OgreManager::getSingleton().getDebugText()->addText( getOwnerObject()->getID() + " - Render Update" );

		CCharacterController* mChar = dynamic_cast<CCharacterController*>(getOwnerObject()->getComponent("CCharacterController"));
		if(mChar) {
			if(mChar->isMoving()) {
				if(!mRotating)
				{
					mRotating = true;
					mOrientDest = mNextOrient; // mNextOrient;
					//mOrientDest = mChar->getDirection();
					//mOrientDest.->rotate(Quaternion(Degree(90), Ogre::Vector3::UNIT_Y),Ogre::SceneNode::TransformSpace::TS_WORLD);
				}
			}
		}

		if(mRotating)
		{
			

			mRotProgress += OgreManager::getSingleton().getTimeSinceLastFrame() * getRotationSpeed(); // mRotFactor;
			//mRotProgress += (OgreManager::getSingleton().getTimeSinceLastFrame() * getRotationSpeed() );
			if(mRotProgress>1)
			{
				mRotating = false;
				mRotProgress = 0;
				//mOrientSrc = mOrientDest;
			}
			else
			{
				Quaternion delta = Quaternion::Slerp(mRotProgress, mOrientSrc, mOrientDest, true);
				//Quaternion delta = Quaternion::nlerp(mRotProgress, mOrientSrc, mOrientDest, true);
				//delta.rotate(Quaternion(Degree(90), Ogre::Vector3::UNIT_Y),Ogre::SceneNode::TransformSpace::TS_WORLD);
				mNode->setOrientation(delta);
				mOrientSrc = delta;
			}
		} 

		if(mChar) {
			//OgreManager::getSingleton().getDebugText()->addText( "mOrientSrc " + Ogre::StringConverter::toString(mOrientSrc) );
			//OgreManager::getSingleton().getDebugText()->addText( "mOrientDest " + Ogre::StringConverter::toString(mOrientDest) );
			//OgreManager::getSingleton().getDebugText()->addText( "mNode " + Ogre::StringConverter::toString(mNode->getOrientation()));
			
		}

	}

	void CRender::setup() {
		CPosition *pos = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
		COrientation *orient = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));

		//Ogre::SceneNode* node = OgreManager::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode(mDesc.name + "_root");
		//mNode = node->createChildSceneNode(mDesc.name);

		mNode = OgreManager::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode(mDesc.name);

		mNode->setPosition(static_cast<Vector3>(*pos));
		mNode->setOrientation(static_cast<Quaternion>(*orient));
		
		mRotating = false;
		//mRotFactor = 0; // 1.0f / frames;
		mOrientSrc = mNode->getOrientation();
		mOrientDest = mNode->getOrientation();
		//mOrientDest = quat * mOrientSrc;           // We want dest orientation, not a relative rotation (quat)
		mRotProgress = 0;

	}

	void CRender::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace

