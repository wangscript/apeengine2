#include "InputManager.h"
#include "ApeManager.h"
//InputHandler* InputHandler::ms_Singleton = 0;

template<> InputManager* Ogre::Singleton<InputManager>::ms_Singleton = 0;

InputManager* InputManager::getSingletonPtr(void)
{
	return ms_Singleton;
}
InputManager& InputManager::getSingleton(void)
{  
	//assert( ms_Singleton );  
	return ( *ms_Singleton );  
}

InputManager::InputManager() : mMouse(0),mKeyboard(0),mInputManager(0) {
	
	//InputHandler* input = 
	//MessageManager::getSingleton().setInputImp(this);

	//input = this;
	//mOgre = 0;
	//mOgre = ogre;

}
OIS::Mouse * InputManager::getMouseObj() {
	return mMouse;
}

void InputManager::initialize() {

	mOgre = OgreRender::getSingletonPtr();
	/*
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
	*/
	m_hWnd = mOgre->getWindowHandler(); // mOgre->getWindowHandler();

	if(m_hWnd ==0)
		return;

	OIS::ParamList pl;
	pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(m_hWnd)));

	mInputManager = OIS::InputManager::createInputSystem( pl );
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true));
	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);
	forward=backward=up=down=left=right = false;
	shutDown = false;

}

OIS::Keyboard* InputManager::getKeyboard() {
	return mKeyboard;
}
/*
OIS:Mouse* InputHandler::getMouse() {
	return mMouse;
}
*/
void InputManager::handleCamera(float dt) {
	
/*
if(ApeManager::getSingleton().isEditorMode()) {
		static float pitch = 0, yaw = 0;

		// get the current mouse state
		const OIS::MouseState &ms = mMouse->getMouseState();
		// fix pitch and yaw
		pitch += -ms.Y.rel * 0.1;
		yaw += -ms.X.rel * 0.1;

		if (pitch < -90) pitch = -90;
		if (pitch >  90) pitch =  90;
		
		Camera* cam = mOgre->getCamera();
		
		cam->setOrientation(Ogre::Quaternion::IDENTITY);
		cam->yaw(Ogre::Degree(yaw));
		cam->pitch(Ogre::Degree(pitch));
	
	
		Ogre::Vector3 move(0, 0, 0);
		if (mKeyboard->isKeyDown(OIS::KC_W))
			move.z += -1;
		if (mKeyboard->isKeyDown(OIS::KC_S))
			move.z += 1;
		if (mKeyboard->isKeyDown(OIS::KC_A))
			move.x += -1;
		if (mKeyboard->isKeyDown(OIS::KC_D))
			move.x += 1;
		if (mKeyboard->isKeyDown(OIS::KC_Q))
			move.y += 1;
		if (mKeyboard->isKeyDown(OIS::KC_E))
			move.y -= 1;

		const float CAM_SPEED = 10; // meters per second
		cam->move(cam->getOrientation() * (move * CAM_SPEED * dt));

		//Ogre::Light *light = mOgre->getSceneManager()->getLight("flashLightNode");
		//light->setPosition(cam->getDerivedPosition());
		//light->setOrientation(cam->getDerivedOrientation());
	}
*/

}
/*
void InputHandler::OnOgreRender_Created(OgreRender* ogre) {
	mOgre = ogre;
}
*/

InputManager::~InputManager() {
	if( mInputManager != NULL )
	{
		mInputManager->destroyInputObject( mMouse );
		mInputManager->destroyInputObject( mKeyboard );
		//mInputManager->destroyInputObject( mJoy );

		OIS::InputManager::destroyInputSystem(mInputManager);
		mInputManager = 0;
	}
}

void InputManager::makeConnections() {


}

void InputManager::capture() {
	mMouse->capture();
	mKeyboard->capture();
	//mKeyboard->get
	//if(mKeyboard->isKeyDown(OIS::kc_
}

const OIS::MouseState InputManager::getMouseStat() {
	const OIS::MouseState ms = mMouse->getMouseState();
	return ms;
}

bool InputManager::isRightButtonDown() {
	const OIS::MouseState ms = mMouse->getMouseState();
	if(ms.buttonDown(OIS::MB_Right))
		return true;
	return false;
}
bool InputManager::isLeftButtonDown() {
	//mMouse->capture();
	//const OIS::MouseState ms = mMouse->getMouseState();
	const OIS::MouseState &ms = mMouse->getMouseState();
	if(ms.buttonDown(OIS::MB_Left))
		return true;
	return false;
}
bool InputManager::isMiddleButtonDown() {
	const OIS::MouseState ms = mMouse->getMouseState();
	if(ms.buttonDown(OIS::MB_Middle))
		return true;
	return false;
}

void  InputManager::setWindowExtents(int width, int height){
	//Set Mouse Region.. if window resizes, we should alter this to reflect as well
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}


// MouseListener
bool InputManager::mouseMoved(const OIS::MouseEvent &evt) {
	int i = evt.state.Z.rel;
	return true;
}

bool InputManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
	switch(btn) {
		case OIS::MB_Left:
			mouseLeftButton = true;
			break;
		case OIS::MB_Right:
			mouseRightButton = true;
			break;
		case OIS::MB_Middle:
			mouseMiddleButton = true;
			break;
	}
	return true;
}

bool InputManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
	switch(btn) {
		case OIS::MB_Left:
			mouseLeftButton = false;
			break;
		case OIS::MB_Right:
			mouseRightButton = false;
			break;
		case OIS::MB_Middle:
			mouseMiddleButton = false;
			break;
	}

	return true;
}

// KeyListener
bool InputManager::keyPressed(const OIS::KeyEvent &evt) {
	if(evt.key == OIS::KC_Q)
		up = true;
	if(evt.key == OIS::KC_E)
		down = true;
	if(evt.key == OIS::KC_W)
		forward = true;
	if(evt.key == OIS::KC_S)
		backward = true;
	if(evt.key == OIS::KC_A)
		left = true;
	if(evt.key == OIS::KC_D)
		right = true;
	if(evt.key == OIS::KC_ESCAPE)
		esc = true;

	//OgreRender::getSingleton().getDebugText()->
	//OgreRender::getSingleton().getDebugText()->addText("keyPress =" + Ogre::StringConverter::toString("trueeeeee"));
	
	return true;
}

bool InputManager::keyReleased(const OIS::KeyEvent &evt) {
	if(evt.key == OIS::KC_Q)
		up = false;
	if(evt.key == OIS::KC_E)
		down = false;
	if(evt.key == OIS::KC_W)
		forward = false;
	if(evt.key == OIS::KC_S)
		backward = false;
	if(evt.key == OIS::KC_A)
		left = false;
	if(evt.key == OIS::KC_D)
		right = false;

	if(evt.key == OIS::KC_ESCAPE)
		esc = true;

	return true;
}



// JoyStickListener
bool InputManager::buttonPressed(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool InputManager::buttonReleased(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool InputManager::axisMoved(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool InputManager::povMoved(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

void InputManager::updateMouseMetrics(int width,int height) {
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;	
}


