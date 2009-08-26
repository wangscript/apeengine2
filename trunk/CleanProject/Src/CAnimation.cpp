#include "CAnimation.h"

namespace Nebula {
	CAnimation::CAnimation()
	{
		mComponentID = "CAnimation";
	}

	CAnimation::CAnimation(const CAnimationDesc& desc)
	{
		mComponentID = "CAnimation";
		mDesc = desc;
		mCurrentAnimation = -1;
		mIsPaused = false;
		mNumberOfAnimations = -1;
		mAnimationSpeed = 1;
		mIsRunningAnimation = false;
		mLastPosition = Vector3::ZERO;
		mVelocity = Vector3::ZERO;
		mAnimationNode = OgreManager::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode(mDesc.name);
	}

	CAnimation::~CAnimation()
	{

	}
	
	AnimationState* CAnimation::getAnimationState(int animIndex) {
		if(mAnimStates[animIndex])
			return mAnimStates[animIndex];
		else
			return NULL;
	}

	Animation* CAnimation::getAnimation(int animIndex) {
		if(mAnimations[animIndex])
			return mAnimations[animIndex];
		else
			return NULL;
	}

	void CAnimation::addAnimationState(AnimationState* animation) {
		mAnimStates.push_back(animation);
	}
		
	void CAnimation::setAnimationSpeed(int animIndex, Real speed) {
		if(!mAnimVelocity.empty()) {
			//if(mAnimVelocity.size() < (animIndex+1) ) {
				mAnimVelocity[animIndex] = speed;
			//}
		}
	}

	Real CAnimation::getAnimationSpeed(int animIndex) {
		if(!mAnimVelocity.empty()) {
			//if(mAnimVelocity.size() < (animIndex+1) ) {
				return mAnimVelocity[animIndex];
			//}
		}
	}

	//Real getCurrentAnimationSpeed() {
		//	return mAnimationSpeed;
		//}

	void CAnimation::addAnimation(Animation* animation, bool enabled, bool loop) {
		
		//CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

		Animation* anim = OgreManager::getSingleton().getSceneManager()->createAnimation(animation->getName(), animation->getLength() );
		
		mAnimations.push_back(anim);

		anim->setDefaultInterpolationMode( animation->getDefaultInterpolationMode() );
		anim->setDefaultRotationInterpolationMode( animation->getDefaultRotationInterpolationMode() );
		anim->setInterpolationMode( animation->getInterpolationMode() );
		anim->setRotationInterpolationMode( animation->getRotationInterpolationMode() );
		
		const Animation::NodeTrackList& trackList = animation->_getNodeTrackList();
		Animation::NodeTrackList::const_iterator it = trackList.begin();
		Animation::NodeTrackList::const_iterator iend = trackList.end();
		
		for(; it != iend; ++it) {
			const Ogre::NodeAnimationTrack* track = it->second;
			
			NodeAnimationTrack* finalTrack = anim->createNodeTrack(track->getHandle(), mAnimationNode);

			unsigned short nk = track->getNumKeyFrames();
			for(unsigned short k = 0; k < nk; k++) {
				TransformKeyFrame* keyFinal = finalTrack->createNodeKeyFrame(k); 
				
				TransformKeyFrame* key = track->getNodeKeyFrame(k);

				keyFinal->setTranslate( key->getTranslate() );
				keyFinal->setRotation( key->getRotation() );
				keyFinal->setScale( key->getScale() );
			}

		}
	
		Ogre::AnimationState* animationState = OgreManager::getSingleton().getSceneManager()->createAnimationState(animation->getName());

		animationState->setLoop(loop);
		animationState->setEnabled(enabled);
		
		mAnimStates.push_back(animationState);

		//Default Velocity
		mAnimVelocity.push_back(1.0f);

		mNumberOfAnimations++;

		if(enabled)
			mCurrentAnimation = mNumberOfAnimations;
	}

	void CAnimation::playAnimation(int animIndex) {
		if(mCurrentAnimation != -1)
			mAnimStates[mCurrentAnimation]->setEnabled(false);

		mCurrentAnimation = animIndex;
		mAnimStates[mCurrentAnimation]->setEnabled(true);
		
		mIsRunningAnimation = true;
		mIsPaused = false;

		CPhysicsActor *actor = dynamic_cast<CPhysicsActor*>(getOwnerObject()->getComponent("CPhysicsActor"));
		if(actor) {
			actor->getNxActor()->raiseBodyFlag(NX_BF_KINEMATIC);
		}

		OnAnimationStarted();
	}

	void CAnimation::stopAnimation(int animIndex) {
		mAnimStates[animIndex]->setEnabled(false);
		mAnimStates[animIndex]->setTimePosition(0);
		mIsPaused = false;
		mIsRunningAnimation = false;
		mCurrentAnimation = -1;
	}

	void CAnimation::pauseAnimation() {
		mIsPaused = true;

		mIsRunningAnimation = false;
	}
	
	void CAnimation::setAnimationTimePosition(int animIndex, Real time) {
		mAnimStates[animIndex]->setTimePosition(time);
	}

	void CAnimation::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

	void CAnimation::update() {
		updateNode();
	}

	void CAnimation::setup() {
		
		if(mAnimationNode) {
			mLastPosition = mAnimationNode->_getDerivedPosition();
		}

		

	}

	void CAnimation::OnAnimationStarted() {
		callLuaFunction("OnAnimationStarted");
	}

	void CAnimation::OnAnimationEnded() {
		callLuaFunction("OnAnimationEnded");
	}

	void CAnimation::OnAnimationUpdated() {
		callLuaFunction("OnAnimationUpdated");
	}

	void CAnimation::setAnimationNode(SceneNode* node) {
		mAnimationNode = node;
	}
	
	SceneNode* CAnimation::getAnimationNode() {
		return mAnimationNode;
	}

	void CAnimation::updateNode() {

		bool isRunning = false;

		if(!mAnimStates.empty()) {
			
			CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

			Real time = OgreManager::getSingleton().getTimeSinceLastFrame();

			if(!mIsPaused && mCurrentAnimation != -1) {
				mAnimStates[mCurrentAnimation]->addTime(time * mAnimVelocity[mCurrentAnimation]);
				OnAnimationUpdated();
				
				if( mAnimStates[mCurrentAnimation]->getTimePosition() == mAnimStates[mCurrentAnimation]->getLength()) {
					OnAnimationEnded();
					mIsRunningAnimation = false;
					//if(!mAnimStates[mCurrentAnimation]->getLoop()) {
					//	mCurrentAnimation = -1;
					//	mIsRunningAnimation = false;
					//}
				} else {
					mIsRunningAnimation = true;
					//isRunning = true;
				}

				if(render && mAnimationNode) {
					Vector3 position = mAnimationNode->_getDerivedPosition();
					Quaternion orientation = mAnimationNode->_getDerivedOrientation();
					Vector3 scale = mAnimationNode->getScale();
					
					if(position != mLastPosition) {
						if(mLastPosition != Vector3::ZERO && position != Vector3::ZERO) {
							mVelocity = position - mLastPosition;
							isRunning = true;
						}

						render->getNode()->setPosition(position);
						render->getNode()->setOrientation(orientation);
						render->getNode()->setScale(scale);

						CCamera *cam = dynamic_cast<CCamera*>(getOwnerObject()->getComponent("CCamera"));
						if(cam) {
							if(cam->isCameraEnabled()) {
								OgreManager::getSingleton().getCamera()->setOrientation(orientation);
								OgreManager::getSingleton().getCamera()->setPosition(position);
							} else {
								cam->getCamera()->setOrientation(orientation);
								cam->getCamera()->setPosition(position);
							}
						}
						

						mLastPosition = position;
					}

					if(!isRunning)
						mVelocity = 0;

				}

			} else {
				mIsRunningAnimation = false;
			}

		}
		//OgreManager::getSingleton().getDebugText()->addText( getOwnerObject()->getID() + " - mVelocity: " + Ogre::StringConverter::toString(mVelocity) );
		//OgreManager::getSingleton().getDebugText()->addText( getOwnerObject()->getID() + " - isRunning: " + Ogre::StringConverter::toString(isRunning) );

	}



} //end namespace
