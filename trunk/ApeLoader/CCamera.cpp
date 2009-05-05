#include "CCamera.h"

/*static*/ 
const std::string CCamera::mFamilyID = "CCamera";
const std::string CCamera::mComponentID = "CCamera";

CCamera::CCamera(CameraView view) : 	mMesh(0),
										mCharacter(0),
										mCRender(0),
										mMainNode(0),
										//mPlayerNode(0),
										mCameraNode(0),
										mCameraPitchNode(0),
										mOgre(0)

{
	//mPosition = vec;
	mCamView = view;
	mOgre = OgreRender::getSingletonPtr();
}
CCamera::~CCamera()
{

}
void CCamera::initialize() {

}
Ogre::SceneNode* CCamera::getMainNode() {
	return mMainNode;
}
Ogre::SceneNode* CCamera::getCameraNode() {
	return mCameraNode;
}
Ogre::SceneNode* CCamera::getCameraPitchNode() {
	return mCameraPitchNode;
}

void CCamera::setup() {
	mCharacter = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));
	mMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	mCAnim = dynamic_cast<CAnimation*>(getOwnerObject()->getComponent("CAnimation"));
	mCRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

	Vector3 mPos = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"))->Position;
	mPosition = Vector3::ZERO;

	//mMouseFilter = new TransformationHistory();
	//mMouseFilter.Init(1,100);

	mZoom = 40;
	//mCharacter->isRotating()
	mMouseSpeed = 0.05f;

	mSmoothCameraMovement = false;
	mUseMouseFilter	= true;
	//mMouseSpeed = 0.10;
	mMouseXRel = 0;
	mMouseYRel = 0;
	mMouseZRel = 0;
	//mNodeOffset = Ogre::Vector3(0,-17,0); //-22
	mNodeOffset = Ogre::Vector3(0,-1.0,0); //-22
	//mCameraOffset = Vector3(0,35,0); //head offset position
	mCameraOffset = Vector3(0,0.2,0); //head offset position
	
	mFilter.SetHistoryBufferLength(20); //20
	mFilter.SetWeightModifier(1.0f); //0.9f

	mZoomFilter.SetHistoryBufferLength(20);
	mZoomFilter.SetWeightModifier(0.9f);

	mMainNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode("MainNode");
	
	ParticleUniverse::ParticleSystemManager* mPartMan = OgreRender::getSingleton().getParticleManager()->getSingletonPtr();

	std::vector<Ogre::String> names;
	mPartMan->particleSystemTemplateNames(names);
	std::vector<Ogre::String>::iterator it;
	std::vector<Ogre::String>::iterator itEnd = names.end();
	//CEGUI::ListboxTextItem* item;
	for (it = names.begin(); it != itEnd; ++it)
	{
		Ogre::String n = (*it);
		//mListBox->addItem(item);
	}

	pos = new Vector3();
	vel = new Vector3();
	quat = new Quaternion();
	
	*pos = Vector3(0,0,0);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//mPlayerNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode("playerCharNode");
	//mItemHolder = mPlayerNode->createChildSceneNode("itemHolderNode");
	//mWeaponHolder = mPlayerNode->createChildSceneNode("weaponHolderNode");
	//mWeaponHolder->translate(22,60,-15);

	//OgreRender::getSingleton().mWeaponNode = mWeaponHolder;

	//Ogre::SceneNode* sn = mPlayerNode->createChildSceneNode("playerCharNodeChild");
	//
	//mCharacterMeshNode = sn->createChildSceneNode("playerCharNodeChil2");
	//mCharacterMeshNode->attachObject(mMesh->getEntity());

	////Panda
	//sn->rotate(Quaternion(Degree(180), Vector3::UNIT_Y));
	//mPlayerNode->setScale(0.3,0.3,0.3);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	//Viking
	//sn->rotate(Quaternion(Degree(90), Vector3::NEGATIVE_UNIT_X));
	//mPlayerNode->setScale(4.0,4.0,4.0);

	mCameraNode = mMainNode->createChildSceneNode("CameraNode");
	mCameraNode->translate(mCameraOffset);
	mCameraPitchNode = mCameraNode->createChildSceneNode("CameraPitchNode");
	mOgre->getCamera()->setPosition(0,0,0);
	
	//agregado!
	//if(!mSmoothCameraMovement)
	//	mCameraPitchNode->attachObject (mOgre->getCamera());

	mCameraPitchNode->translate(Vector3(0, 0, 100));
	//mCameraNode->attachObject(SoundManager::getSingleton().getManager()->getListener());
	
	mRotating = false;
	mPosition = mPos;
	mMainNode->setPosition(mPosition);
	
	camDestNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode("camDestNode");
	camDestNodePitch = camDestNode->createChildSceneNode("camDestNodePitch");

	if(mSmoothCameraMovement)
		camDestNodePitch->attachObject (mOgre->getCamera());	

	camDestNode->setPosition(mCameraPitchNode->_getDerivedPosition());

	Ogre::Light *light = mOgre->getSceneManager()->createLight("flashLight");
	light->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	light->setType(Ogre::Light::LT_SPOTLIGHT);
	if(light->getType() == Ogre::Light::LT_SPOTLIGHT) {
		light->setSpotlightInnerAngle(Ogre::Degree(75));
		light->setSpotlightOuterAngle(Ogre::Degree(85));

	}
	light->setAttenuation(1430, 1, 1, 1); // meter range.  the others our shader ignores
	light->setDirection(Ogre::Vector3(0, 0, -1));
	Ogre::SceneNode* fn = mCameraPitchNode->createChildSceneNode("flashLightNode");
	//fn->translate(Vector3(0, 0, -25));
	//fn->translate(Vector3(0, 0, 425));
	fn->translate(Vector3(2, 0, 0)); //10

	fn->attachObject(light);
	fn->setVisible(false);
	//camDestNodePitch->attachObject(light);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	mCamRotating = true;
	mCamRotFactor = 1.0f / 60.0f;
	//mCamOrientSrc = mCAnim->mPlayerNode->getOrientation();
	mCamOrientDest = mCameraPitchNode->getOrientation() * mOrientSrc;           // We want dest orientation, not a relative rotation (quat)
	mCamRotProgress = 0;

	mRotProgress = 0;

}

void CCamera::setMouseRelativePosition(const int _x,const int _y,const int _z) {
	mMouseXRel = _x;
	mMouseYRel = _y;
	mMouseZRel = _z;

}
void CCamera::setCameraAimView(CameraAimView view) {
	mCamAimView = view;
}

void CCamera::setCameraView(CameraView view) {
/*
	mMainNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode("MainNode");
	mPlayerNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode("PlayerNode");
	mPlayerNode->attachObject(mMesh->getEntity());
	mPlayerNode->setScale(0.1,0.1,0.1);
	mCameraNode = mMainNode->createChildSceneNode("CameraNode");
	mCameraPitchNode = mCameraNode->createChildSceneNode("CameraPitchNode");
	mOgre->getCamera()->setPosition(0,0,0);
	mCameraPitchNode->attachObject (mOgre->getCamera());
	mCameraPitchNode->translate(Vector3(0, 0, 100));
*/
	if(view == VIEW_THIRD_PERSON_FREE)  {
		mCamView = view;
		//mCAnim->mPlayerNode->setVisible(true);
		//mCameraPitchNode->setPosition(mMainNode->getPosition());
		//mCameraNode->setPosition(mMainNode->getPosition());
		//mCameraPitchNode->setPosition(mMainNode->getPosition());
		//mCameraPitchNode->translate(Vector3(0, 0, 100));
	}
	if(view == VIEW_THIRD_PERSON_SIDE)  {
		mCamView = view;
		
		//mCameraPitchNode->attachObject (mOgre->getCamera());
		//mCameraPitchNode->detachObject(mOgre->getCamera()->getName());
		if(mCharacter) {
			if(mCharacter->getCurrentRoom()) {
				mOgre->getCamera()->setOrientation(mCharacter->getCurrentRoom()->mCamera->getDerivedOrientation() );
				mOgre->getCamera()->setPosition(mCharacter->getCurrentRoom()->mCamera->getDerivedPosition() );
			}
		}


		//mCameraPitchNode->setPosition(mMainNode->getPosition());
		//mCameraPitchNode->setPosition(mMainNode->getPosition());
		//mCAnim->mPlayerNode->setVisible(false);
		//mCameraPitchNode->translate(Vector3(0,-4,0));
		//mCameraNode->setPosition(mMainNode->getPosition());
	}
}
void CCamera::update() {

}
Ogre::SceneNode* CCamera::getPlayerNode() {
	return mCAnim->mPlayerNode;
}
Ogre::SceneNode* CCamera::getItemHolderNode() {
	//return mCAnim->mItemHolder;
	return NULL;
}
Ogre::SceneNode* CCamera::getWeaponHolderNode() {
	//return mCAnim->mWeaponHolder;
	return NULL;
}

Real CCamera::getCameraHitDistance() {
	Vector3 rayDir = mCameraPitchNode->_getDerivedOrientation() * Vector3::UNIT_Z;
	Vector3 pos = mMainNode->_getDerivedPosition();
	
	Real dist = (Real)mCharacter->rayHitDistance(pos,rayDir);
	
	if(dist > 0) {
		Real d2 = 0;	
		d2 = pos.distance(mCameraPitchNode->_getDerivedPosition());
		if(d2 > dist)
			d2 = -(d2 - dist); //+8 to lift it a little from the floor
		else
			d2 = 0;
		//mOgre->getDebugText()->addText("Dist inc=" + Ogre::StringConverter::toString(d2));
		return d2;
		//mCameraPitchNode->translate(0,0,d2);
	}
	return 0.0f;
}

void CCamera::updateCamera() {

	Real elapsedTime = mOgre->getTimeSinceLastFrame();
	
	
	if(mCharacter->isMoving()) {
		if(!mRotating) {
			mRotating = true;
			mOrientSrc = mCAnim->mPlayerNode->getOrientation();

			Vector3 localY = mCAnim->mPlayerNode->getOrientation() * Vector3::NEGATIVE_UNIT_Z;

			Quaternion quat;
			if(mCamAimView == AIM_VIEW_NORMAL)
				quat = localY.getRotationTo(mMainNode->getOrientation() * Vector3::NEGATIVE_UNIT_Z);
			else
				quat = localY.getRotationTo(mCharacter->getDirection() * mCharacter->getDisplacement());
				//quat = mOrientSrc * mCharacter->getDirection();
			
			
			mOrientDest = quat;

			mDestYaw = Degree(quat.getYaw());
			mYawInc = (mDestYaw < Degree(0)) ? Degree(-mCharacter->getTurnReactionSpeed() * elapsedTime) : Degree(mCharacter->getTurnReactionSpeed() * elapsedTime) ;
			mYaw = Degree(0);

		}

		if(mCamView == CameraView::VIEW_THIRD_PERSON_FREE || CameraView::VIEW_THIRD_PERSON_SIDE) {
			if(mRotating)
			{
				//This is where i make the character to have a delay turning his body into an arbitrary direction.(see mTurnReactionSpeed)
				
				//if(mCamAimView == AIM_VIEW_NORMAL) {
					mYaw += Degree(mYawInc);
					if( (mYawInc < Degree(0)) ? (mYaw < mDestYaw) : (mYaw > mDestYaw) )
						mRotating = false;
					else
						mCAnim->mPlayerNode->yaw(mYawInc);
				//} else {
					
				//}

				/*
				mRotProgress += elapsedTime;
				Quaternion delta = Quaternion::Slerp(mRotProgress,mOrientSrc, mOrientDest, true);
				mPlayerNode->setOrientation(delta);

				if( (mPlayerNode->getOrientation().getYaw() < Degree(0)) ? (mPlayerNode->getOrientation().getYaw() < mDestYaw) : (mPlayerNode->getOrientation().getYaw() > mDestYaw) )
					mRotating = false;
				*/
			} 

		}

	}
	

	Ogre::Vector3 v = Vector3(mCharacter->getCharacterPos().x,
							  mCharacter->getCharacterPos().y,
							  mCharacter->getCharacterPos().z);

	mMainNode->setPosition(v);

	//-----------------------------------------------------------------------------
	//Prevent the camera from getting behind or inside objects
	//if(mCamView != VIEW_FIRST_PERSON) {
		//Real hitDist = getCameraHitDistance();
		//if(hitDist < 0)
			

		//mOgre->getDebugText()->addText("hit dist=" + Ogre::StringConverter::toString(hitDist));

	//}
	//-----------------------------------------------------------------------------

	v.y = v.y + mNodeOffset.y;
	mCAnim->mPlayerNode->setPosition(v);

	//-----------------------------------------------------------------------------
	//Set mouse displacement
	Real mXRel = (Real)(-mMouseXRel ) * mMouseSpeed;
	Real mYRel = (Real)(-mMouseYRel ) * mMouseSpeed;
	Real mZRel = (Real)(-mMouseZRel ) * mMouseSpeed;
	mZoom = Real(mZRel * mMouseSpeed * 45); // * mMouseSpeed
	//-----------------------------------------------------------------------------

	mCameraPitchNode->translate(0,0,mZoom);

	Vector3 orig = camDestNode->_getDerivedPosition(); 
	Vector3 dest = mCameraPitchNode->_getDerivedPosition();
	//mOgre->getDebugText()->addText(Ogre::StringConverter::toString(dest - orig));

	Vector3 distanceVector;
	distanceVector = dest - orig;
	if( (distanceVector.x) >= 0.1f || (distanceVector.x) <= -0.1f && (distanceVector.y) >= 0.1f || (distanceVector.y) <= -0.1f && (distanceVector.z) >= 0.1f || (distanceVector.z) <= -0.1f ) {
		//if(getCameraHitDistance() >= 0)
			camDestNode->setPosition(dest);
	}

	if( (distanceVector) != Vector3::ZERO ) {
		mCameraTime += elapsedTime * 0.08f; //0.05f
		if(mSmoothCameraMovement)
			//if(getCameraHitDistance() >= 0)
				camDestNode->translate((dest - orig) * mCameraTime * elapsedTime ); // * 0.5f
	} else {
		mCameraTime = 0;
	}

	//-----------------------------------------------------------------------------
	//Filter mouse movement
	if(mUseMouseFilter) {
	//	mXRel *= elapsedTime * mMouseSpeed;
	//	mYRel *= elapsedTime * mMouseSpeed;
		//mFilter.SetWeightModifier(1.1f - elapsedTime); //0.9f
		//mFilter.SetWeightModifier(mMouseXRel);
	//	mFilter.updateTime(elapsedTime);
	//	mFilter.Apply(mXRel,mYRel);
	}
	//-----------------------------------------------------------------------------

	Degree mRotX = Degree(mXRel);
	Degree mRotY = Degree(mYRel);

	if(mCamView == VIEW_FIRST_PERSON) {
		mMainNode->yaw(mRotX);
		mCameraPitchNode->pitch(mRotY);
	} else {
		
		Ogre::Quaternion currentPitch;
		Ogre::Quaternion currentYaw;
		Ogre::Quaternion finalRotation;
		
		
		
		if (mRotX != Degree(0)) {
			//X
			
			if(mSmoothCameraMovement) {
				mMainNode->yaw(mRotX);
				camDestNode->yaw(mRotX);
			} else {
				mMainNode->yaw(mRotX);
			}

			//currentYaw = camDestNode->_getDerivedOrientation();
			//currentYaw = (currentYaw * Quaternion(Degree(mRotX), Vector3::UNIT_Y)); 
			
			//camDestNode->setOrientation(currentYaw);	
			
			
		}
		if (mRotY != Degree(0)) {
			//currentPitch = camDestNodePitch->_getDerivedOrientation();
			//currentPitch = (currentPitch * Quaternion(Degree(mRotY), Vector3::UNIT_X)); 
			
			if(mSmoothCameraMovement) {
				camDestNodePitch->pitch(mRotY);

			} else {
				mCameraPitchNode->pitch(mRotY);
			}

			//mCameraPitchNode->pitch(mRotY);

			//camDestNodePitch->setOrientation(currentPitch);	
		}

		
	}

	//-----------------------------------------------------------------------------
	//Limiting pitch movement...
	Degree viewPitch = Degree(mCameraNode->getOrientation().getPitch());
	if (viewPitch < Degree(-90)) {
		mCameraNode->setOrientation(Quaternion::IDENTITY);
		mCameraNode->pitch(Degree(-90));
	}
	if (viewPitch >  Degree(90)) {
		mCameraNode->setOrientation(Quaternion::IDENTITY);
		mCameraNode->pitch(Degree(90));
	}

	Degree camViewPitch = Degree(camDestNodePitch->getOrientation().getPitch());
	if (camViewPitch < Degree(-90)) {
		camDestNodePitch->setOrientation(Quaternion::IDENTITY);
		camDestNodePitch->pitch(Degree(-90));
	}
	if (camViewPitch >  Degree(90)) {
		camDestNodePitch->setOrientation(Quaternion::IDENTITY);
		camDestNodePitch->pitch(Degree(90));
	}
	//-----------------------------------------------------------------------------

	//if(mCurrentView == CAMERA_THIRD_PERSON_AIM) {
	//	mPlayerNode->yaw(mRotX);
	//}

	//mAnimationState->addTime(time * 1.5);


}
