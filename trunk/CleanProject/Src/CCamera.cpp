#include "CCamera.h"

namespace Nebula {
	CCamera::CCamera()
	{
		mComponentID = "CCamera";
	}

	CCamera::CCamera(const CCameraDesc& desc)
	{
		mComponentID = "CCamera";
		mDesc = desc;
		
		//mDesc.animationEnabled = false;
	}

	CCamera::~CCamera()
	{

	}

	void CCamera::update() {

	}

	void CCamera::setup() {
		
		//CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		//if(render && mCamera) {

			//Ogre::SceneNode* parent = mCamera->getParentSceneNode();
			//parent->detachObject(mCamera);
			//if(!render->getNode()->getAttachedObject(OgreManager::getSingleton().getCamera()->getName())) {
			//	render->getNode()->attachObject(OgreManager::getSingleton().getCamera()); //mCamera
			//}
		//}
	}
	
	bool CCamera::isCameraEnabled() {
		return mDesc.animationEnabled;
	}

	void CCamera::enableAnimation(bool flag) {
		mDesc.animationEnabled = flag;
		
		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		if(render) { // && mCamera
			//OgreManager::getSingleton().getCamera()
			//OgreManager::getSingleton().getCamera()->setOrientation(Quaternion::IDENTITY);
			
			//Ogre::SceneNode* node = render->getNode()->createChildSceneNode();
			//node->attachObject(OgreManager::getSingleton().getCamera());
			//node->rotate(Quaternion(Degree(180), Ogre::Vector3::UNIT_Y)); //Ogre::SceneNode::TransformSpace::TS_WORLD

			//node->setOrientation(mDesc.initialOrientation);

			//render->getNode()->attachObject(OgreManager::getSingleton().getCamera());
		}
	}

	void CCamera::setCamera(Ogre::Camera* cam) {
		mCamera = cam;
	}

	Ogre::Camera* CCamera::getCamera() {
		return mCamera;
	}

	void CCamera::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
