#include "CPlayerInput.h"

#include "CPosition.h"
#include "COrientation.h"
#include "CMesh.h"
#include "CCharacter.h"
#include "CCAmera.h"
#include "ApeSceneManager.h"

class ApeSceneManager;

/*static*/ 
const std::string CPlayerInput::mFamilyID = "CPlayerInput";
const std::string CPlayerInput::mComponentID = "CPlayerInput";

CPlayerInput::CPlayerInput() : mInput(0),
							   mOgre(0),
							   mCharacter(0),
							   mCamera(0),
							   mCAnim(0)
{
	mOgre = OgreRender::getSingletonPtr();
}
CPlayerInput::~CPlayerInput()
{

}

bool CPlayerInput::IsDirectionalKeyDown() {
	mInput->getKeyboard()->capture();
	//bool res = (mInput->getKeyboard()->isKeyDown(OIS::KC_W) && mInput->getKeyboard()->isKeyDown(OIS::KC_S) && mInput->getKeyboard()->isKeyDown(OIS::KC_A) && mInput->getKeyboard()->isKeyDown(OIS::KC_D) && mInput->getKeyboard()->isKeyDown(OIS::KC_SPACE) );
	bool res = (mInput->getKeyboard()->isKeyDown(OIS::KC_W) && mInput->getKeyboard()->isKeyDown(OIS::KC_S) && mInput->getKeyboard()->isKeyDown(OIS::KC_A) && mInput->getKeyboard()->isKeyDown(OIS::KC_D) );
	return res;
}
/*
void CPlayerInput::repositionMouse(Real& deltaMouseX, Real& deltaMouseY)
{
	const OIS::MouseState &ms = mInput->getMouseObj()->getMouseState();
	
	
	int x = ms.X.abs;
	int y = ms.Y.abs;
	//int width = glutGet(GLUT_WINDOW_WIDTH);
	//int height = glutGet(GLUT_WINDOW_HEIGHT);

	//int cx = (width>>1);
	//int cy = (height>>1);

	//glutWarpPointer(cx, cy);

	deltaMouseX = NxF32(cx - gMouseX);
	deltaMouseY = NxF32(cy - gMouseY);
}
*/

void CPlayerInput::update() {

	mInput->getMouseObj()->capture();
	mInput->getKeyboard()->capture();

	const OIS::MouseState &ms = mInput->getMouseObj()->getMouseState(); // getMouseStat();
	
	Real elapsedTime = mOgre->getTimeSinceLastFrame();
	
	mCamera->setMouseRelativePosition(ms.X.rel,ms.Y.rel,ms.Z.rel);

	Vector3 _NextMovement = Vector3(0,0,0);
	//Ogre::Quaternion _Direction = mCamera->getMainNode()->getOrientation();
	Ogre::Quaternion _Direction = Ogre::Quaternion::IDENTITY;

	//mIsKeyPressed = false;
	//mDirKeys = false;

	if(mInput->getKeyboard()->isKeyDown(OIS::KC_W))
	{
		//_NextMovement.z = -1;

		//mCharacter->startWalking(0);
		//mIsKeyPressed = true;
		//mDirKeys = true;
	}
	if(mInput->getKeyboard()->isKeyDown(OIS::KC_S))
	{
		//_NextMovement.z = 1;

		//mCharacter->startWalking(0);
		//mIsKeyPressed = true;
		//mDirKeys = true;
	}
	if(mInput->getKeyboard()->isKeyDown(OIS::KC_D))
	{
		_Direction = Ogre::Quaternion(sqrt(0.5),-sqrt(0.5),0,0);
		_NextMovement.x = -1;
		//mCharacter->startWalking(0);
		//mIsKeyPressed = true;
		//mDirKeys = true;
	}
	if(mInput->getKeyboard()->isKeyDown(OIS::KC_A))
	{
		_Direction = Ogre::Quaternion(sqrt(0.5),sqrt(0.5),0,0);
		_NextMovement.x = 1;
		//mCharacter->startWalking(0);
		//mIsKeyPressed = true;
		//mDirKeys = true;
	}


	if(_NextMovement.x == 0 ) //&& (!mCharacter->isOnAir()) && _NextMovement.z == 0
	{
		//mCharacter->enableMotion(false);

		mCharacter->setWalkState(true);
		//mCharacter->stopWalking();
	}
	else
	{
		//mCharacter->setWalkState(false);

		mCharacter->enableMotion(true);
		mCharacter->setDisplacement(_NextMovement);
		mCharacter->setDirection(_Direction);


	}
	//mCharacter->setDisplacement(_NextMovement);
	//mCharacter->setDirection(_Direction);

	mCharacter->updateCharacter();
	mCamera->updateCamera();
	mCAnim->updateAnimation();
}

void CPlayerInput::setup() {
	mInput = new InputHandler();
	mInput->initialize();

	mInput->getKeyboard()->setEventCallback(this);
	mInput->getMouseObj()->setEventCallback(this);

	mCharacter = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));
	mCamera = dynamic_cast<CCamera*>(getOwnerObject()->getComponent("CCamera"));
	mCAnim = dynamic_cast<CAnimation*>(getOwnerObject()->getComponent("CAnimation"));
	
	//mDirKeys = false;
}

bool CPlayerInput::mouseMoved(const OIS::MouseEvent &evt) {
	return true;
}

bool CPlayerInput::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
	switch(btn) {
		case OIS::MB_Left:
			//mouseLeftButton = true;
			if(mCharacter->isArmed()) {
				if(mCharacter->isHoldingItem())
					mCharacter->throwItemInHand(8000);
				
				mCharacter->startShooting();
			} else {
				if(mCharacter->isHoldingItem())
					mCharacter->throwItemInHand(8000);
			}

			break;
		case OIS::MB_Right:
			//*CCamera::*/mouseRightButton = true;
			mCamera->setCameraAimView(CCamera::AIM_VIEW_NORMAL);
			break;
		case OIS::MB_Middle:
			
			//mouseMiddleButton = true;
			break;
	}
	return true;
}

bool CPlayerInput::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
	switch(btn) {
		case OIS::MB_Left:
			//mouseLeftButton = false;
			if(mCharacter->isArmed()) {
				mCharacter->stopShooting();
			}
			break;
		case OIS::MB_Right:
			//mouseRightButton = false;
			mCamera->setCameraAimView(CCamera::AIM_VIEW_OFF);
			break;
		case OIS::MB_Middle:
			//mouseMiddleButton = false;
			break;
	}

	return true;
}

// KeyListener
bool CPlayerInput::keyPressed(const OIS::KeyEvent &evt) {
	
	if(evt.key == OIS::KC_F) {	
		mOgre->getSceneManager()->getLight("flashLight")->setVisible(!mOgre->getSceneManager()->getLight("flashLight")->isVisible()); // getRootSceneNode()->getChild("flashLightNode")->
	}

	if(evt.key == OIS::KC_G) {	
		if(mCharacter->isArmed()) {
			mCharacter->throwItemInHand(2000);
		}
	}

	//if(evt.key == OIS::KC_W) {
	//	mCharacter->startWalking(0);
	//	mCharacter->setWalkState(false);
	//
	//}
	if(evt.key == OIS::KC_S) {
		mCharacter->startWalking(0);
		mCharacter->setWalkState(false);
	
	}
	if(evt.key == OIS::KC_A) {
		mCharacter->startWalking(0);
		mCharacter->setWalkState(false);
		
		mCAnim->setAnimationState(1);

		//mCAnim->setAnimState(START_WALK);
		//mCAnim->setAnimState("Walk",true,true);
	}
	if(evt.key == OIS::KC_D) {
		mCharacter->startWalking(0);
		mCharacter->setWalkState(false);
		mCAnim->setAnimationState(1);
	}
	//if(evt.key == OIS::KC_W) {
		

	//}
	if(evt.key == OIS::KC_LCONTROL) {

	}
	if(evt.key == OIS::KC_LSHIFT) {

		mCharacter->setSpeed(60.0f);
	}
	if(mInput->getKeyboard()->isKeyDown(OIS::KC_E))
	{
		mCharacter->pickItem(Physics::getSingleton().getActorFromCrosshair());
	}

	if(evt.key == OIS::KC_F1) {
		//mCamera->setCameraView(CCamera::VIEW_THIRD_PERSON_FREE);
		OgreRender::getSingleton().getDebugText()->toggleFPSWindow();
	}
	if(evt.key == OIS::KC_F2) {
		//mCamera->setCameraView(CCamera::VIEW_THIRD_PERSON_FREE);
		if(ApeSceneManager::getSingleton().mBlurCompositorFlag) {
			Ogre::CompositorManager::getSingleton().setCompositorEnabled(OgreRender::getSingleton().getViewport(),"Bloom", false);
			ApeSceneManager::getSingleton().mBlurCompositorFlag = false;
		} else {
			Ogre::CompositorManager::getSingleton().setCompositorEnabled(OgreRender::getSingleton().getViewport(),"Bloom", true);
			ApeSceneManager::getSingleton().mBlurCompositorFlag = true;
		}
	}
	if(evt.key == OIS::KC_F3) {
		mCamera->setCameraView(CCamera::VIEW_THIRD_PERSON_SIDE);
	}
	if(evt.key == OIS::KC_F4) {
		//mCamera->setCameraView(CCamera::VIEW_FIRST_PERSON_EDITOR);
	}
	if(mInput->getKeyboard()->isKeyDown(OIS::KC_W))
	{
		//if we can actually jump set the animation.
		//if(mCharacter->startJump(80));
		mCAnim->setAnimationState(4);
		mCharacter->startJump(9);
			//mCAnim->setAnimState(START_JUMP);

	}

	if(mInput->getKeyboard()->isKeyDown(OIS::KC_F5)) {
		if(mOgre->getCamera()->getPolygonMode() == PM_WIREFRAME) {
			mOgre->getCamera()->setPolygonMode(PolygonMode::PM_SOLID);
		} else {
			mOgre->getCamera()->setPolygonMode(PolygonMode::PM_WIREFRAME);
		}
	}
	if(mInput->getKeyboard()->isKeyDown(OIS::KC_F6)) {
		mOgre->getSceneManager()->setDisplaySceneNodes(!mOgre->getSceneManager()->getDisplaySceneNodes());
	}

	//mOgre->getDebugText()->addText("keyPress =" + Ogre::StringConverter::toString("trueeeeee"));

	return true;
}

bool CPlayerInput::keyReleased(const OIS::KeyEvent &evt) {
	
	//if(evt.key == OIS::KC_W) {

	//}
	if(evt.key == OIS::KC_S) {
		//if(!IsDirectionalKeyDown())
			//mCAnim->setAnimState(STOP_WALK);

		//key = true;
		//mCharacter->stopWalking();
		//mCharacter->setWalkState(true);
	}
	if(evt.key == OIS::KC_A) {
		mCAnim->setAnimationState(0);
	}
	if(evt.key == OIS::KC_D) {
		mCAnim->setAnimationState(0);
	}
	//if(evt.key == OIS::KC_SPACE) {

	//}
	//if(evt.key == OIS::KC_LCONTROL) {

	//}
	if(evt.key == OIS::KC_LSHIFT) {
		mCharacter->setSpeed(60.0f);
	}

	return true;
}

// JoyStickListener
bool CPlayerInput::buttonPressed(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool CPlayerInput::buttonReleased(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool CPlayerInput::axisMoved(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool CPlayerInput::povMoved(const OIS::JoyStickEvent &evt, int index) {
	return true;
}
