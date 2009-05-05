#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "GameComponent.h"
#include "MouseFilter.h"
#include "Ogre.h"
#include "OgreRender.h"
#include "CMesh.h"
#include "CCharacter.h"
#include "CRender.h"
//#include "TransformationHistory.h"
#include "SoundManager.h"
#include "CAnimation.h"

using namespace Ogre;

class SoundManager;
class CCharacter;
class GameComponent;
class OgreRender;
class CMesh;
class CRender;
class CAnimation;

class CCamera : public GameComponent {
public:
	
	enum CameraView {
		VIEW_FIRST_PERSON,
		VIEW_FIRST_PERSON_EDITOR,
		VIEW_THIRD_PERSON_FREE,
		VIEW_THIRD_PERSON_AIM,
		VIEW_THIRD_PERSON_SIDE
	};

	enum CameraAimView {
		AIM_VIEW_OFF,
		AIM_VIEW_SHOULDER,
		AIM_VIEW_NORMAL
	};
	
	//static Ogre::Vector3 Position;
	Ogre::Camera* mCamera;
	Ogre::Vector3 mPosition;

	CCamera(CameraView view); // = NULL
	~CCamera();

	void update();
	void setup();
	void initialize();
	void setMouseRelativePosition(const int _x,const int _y,const int _z);
	void updateCamera();

	Real getCameraHitDistance();
	Ogre::SceneNode* getMainNode();
	Ogre::SceneNode* getCameraNode();
	Ogre::SceneNode* getCameraPitchNode();
	Ogre::SceneNode* getPlayerNode();
	void setCameraView(CameraView view);
	void setCameraAimView(CameraAimView view);
	Ogre::SceneNode* getItemHolderNode();
	Ogre::SceneNode* getWeaponHolderNode();

	Ogre::SceneNode* mCharacterMeshNode;

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}
private:
	static const std::string mFamilyID;
	static const std::string mComponentID;

	CameraView mCamView;
	CameraAimView mCamAimView;
	OgreRender *mOgre;

//	TransformationHistory mMouseFilter;
	Vector3 *pos; //mMouseXRel,mMouseYRel,mMouseZRel
	Ogre::Quaternion* quat;
	Ogre::Vector3* vel;

	MouseFilter mFilter;
	bool mUseMouseFilter;

	MouseFilter mZoomFilter;

	Ogre::SceneNode* mMainNode;
	//Ogre::SceneNode* mPlayerNode;
	Ogre::SceneNode* mCameraNode;
	Ogre::SceneNode* mCameraPitchNode;
	Ogre::SceneNode* camDestNode;
	Ogre::SceneNode* camDestNodePitch;
	//Ogre::SceneNode* mItemHolder;
	//Ogre::SceneNode* mWeaponHolder;

	Real mCameraTime;
	Ogre::SceneNode* sn1;
           // Destination orientation
	Ogre::Real mRotProgress;                   // How far we've interpolated
	Ogre::Real mRotFactor;                     // Interpolation step



	//Real m
	//Ogre::AnimationState* mAnimationState;
	bool mRotating;
	Ogre::Quaternion mOrientSrc;
	Ogre::Quaternion mOrientDest;
	Ogre::Real mDistance;
	Ogre::Degree mDestYaw;
	Ogre::Degree mYaw;
	Ogre::Degree mYawInc;

	Ogre::Vector3 mNodeOffset;
	Real mZoom;
	Ogre::Vector3 mCameraOffset;

	Ogre::Quaternion mCamOrientSrc;               // Initial orientation
	Ogre::Quaternion mCamOrientDest;              // Destination orientation
	Ogre::Real mCamRotProgress;                   // How far we've interpolated
	Ogre::Real mCamRotFactor;                     // Interpolation step
	bool mCamRotating;

	bool mSmoothCameraMovement;

	int mMouseXRel;
	int mMouseYRel;
	int mMouseZRel;
	
	Real mMouseSpeed;
	
	CMesh* mMesh;
	CCharacter* mCharacter;
	CRender *mCRender;
	CAnimation *mCAnim;
	//Ogre::Vector3 mStartPos;
};

#endif
