#ifndef _CANIMATION_H_
#define _CANIMATION_H_

#include "GameComponent.h"
#include "Ogre.h"
#include "OgreRender.h"
#include "CCharacter.h"
#include "ApeManager.h"
#include "CMesh.h"

#include <map>

using namespace Ogre;

class OgreRender;
class CMesh;
class ApeManager;
class CCharacter;
class GameComponent;

namespace AnimState
{
	enum animState {
		NONE,
		START_WALK,
		STOP_WALK,
		LOOP_WALK,
		START_JUMP,
		IDLE
	}; 
}

using namespace AnimState;

class ApeAnimation  {
public:
	
	ApeAnimation(Ogre::AnimationState* anim) {
		mAnimState = anim;
		//mXMLFileName = xmlFileName;
	};

	~ApeAnimation();
	
	AnimationState* getAnimation() {
		return mAnimState;
	}

	Real getBlendMultipier() {
		return mAnimationBlendMultip;
	}
	void setBlendMultipier(Real multip) {
		mAnimationBlendMultip = multip;
	}
	Real getSpeedMultipier() {
		return mAnimationSpeedMultip;
	}
	void setSpeedMultipier(Real multip) {
		mAnimationSpeedMultip = multip;
	}
private:
	Ogre::AnimationState* mAnimState;
	Real mAnimationSpeedMultip;
	Real mAnimationBlendMultip;
	Ogre::String mAnimationName;
	bool mIsLooped;
	
};
class ApeAnimation;

class BodyPart  {
public:

	BodyPart() {
		//mAnimState = anim;
		//mXMLFileName = xmlFileName;
	};

	~BodyPart();

	void updateAnimation();
	ApeAnimation* getAnim(AnimState::animState ms);
	void setAnimState(AnimState::animState ms);

	//AnimationState* getAnimation() {
	//	return mAnimState;
	//}

	//Real getBlendMultipier() {
	//	return mAnimationBlendMultip;
	//}
	//void setBlendMultipier(Real multip) {
	//	mAnimationBlendMultip = multip;
	//}
	//Real getSpeedMultipier() {
	//	return mAnimationSpeedMultip;
	//}
	//void setSpeedMultipier(Real multip) {
	//	mAnimationSpeedMultip = multip;
	//}
	std::map<AnimState::animState,ApeAnimation*> mAnimList;
	std::string bodyPartName;
	std::string meshName;
	//ApeAnimation* animObj;
	enum AnimState::animState mCurrentAnim;
	enum AnimState::animState mNextAnim;

private:

	//Ogre::AnimationState* mAnimState;
	//Real mAnimationSpeedMultip;
	//Real mAnimationBlendMultip;
	//Ogre::String mAnimationName;
	//bool mIsLooped;

};
class BodyPart;


class CAnimation : public GameComponent {
public:
	
	//static Ogre::Vector3 Position;
	//Ogre::Vector3 Position;


	//CAnimation();
	CAnimation(std::string xmlFileName = "");
	~CAnimation();

	void update();
	void setup();
	bool loadSettings();
	void playAnim(AnimState::animState ms);

	Ogre::String getParamValue(Ogre::String paramName,Ogre::String param);

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
	/*
	void setAnim_Walk(AnimationState* anim);
	void setAnim_Run(AnimationState* anim);
	void setAnim_Jump(AnimationState* anim);
	void setAnim_Crouch(AnimationState* anim);
	void setAnim_Idle(AnimationState* anim);
	*/
	void updateAnimation();
	/*ApeAnimation* getAnim(AnimState::animState ms);*/
	
	void setAnimState(AnimState::animState ms);
	/*
	void startAnim_Walk();
	void startAnim_Idle();
	void startAnim_Run();
	void startAnim_Jump();
	void startAnim_Crouch();
	*/

	Ogre::SceneNode* mPlayerNode;
	Ogre::SceneNode* mItemHolder;
	Ogre::SceneNode* mWeaponHolder;

private:
	static const std::string mFamilyID;
	static const std::string mComponentID;

	OgreRender* mOgre;
	//std::string mCurrentAnim;
	//std::string mNextAnim;
	enum AnimState::animState mCurrentAnim;
	enum AnimState::animState mNextAnim;

	CCharacter* mCharacter;
	
	
	std::list<BodyPart*> mBodyPartsList;

	std::string mXMLFileName;
};

#endif
