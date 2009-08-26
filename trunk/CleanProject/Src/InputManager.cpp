#include "InputManager.h"

template<> Nebula::InputManager* Ogre::Singleton<Nebula::InputManager>::ms_Singleton = 0;

namespace Nebula {

	InputManager::InputManager() : mMouse(0),mKeyboard(0),mInputManager(0) {
		initialize();
	}
	
	InputManager* InputManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}

	InputManager& InputManager::getSingleton(void)
	{
		assert( ms_Singleton );  
		return ( *ms_Singleton );
	}

	void InputManager::setBindings() {
		//lua_State* lua = LuaStateManager::getSingleton().getState();
		//module( lua )
		//	[
		//		class_< GuiManager >( "GuiManager" )
		//		.def("setWallpaper", (void(GuiManager::*)(const std::string&))&GuiManager::setWallpaper )
		//		.def( "getSingleton", &GuiManager::getSingleton ) // like this
		//	];

		//   getConsole()->registerConsoleDelegate("GuiManager", MyGUI::newDelegate(this, &GuiManager::command));
		////getConsole()->registerConsoleDelegate("GuiManager:", MyGUI::newDelegate(this, &GuiManager::command));
		//getConsole()->registerConsoleDelegate("GuiManager:setWallpaper", MyGUI::newDelegate(this, &GuiManager::command));

		//object global_vars = globals(lua);
		//global_vars["GuiManager"] = &GuiManager::getSingleton(); 
	}

	OIS::Mouse * InputManager::getMouseObject() {
		return mMouse;
	}

	OIS::Keyboard* InputManager::getKeyboardObject() {
		return mKeyboard;
	}

	bool InputManager::start() {
		//setBindings();
		return true;
	}

	void InputManager::onSuspend() {

	}

	void InputManager::update() {
		mMouse->capture();
		mKeyboard->capture();

		//const OIS::MouseState &ms = mMouse->getMouseState(); // getMouseStat();

	}

	void InputManager::onResume() {

	}

	void InputManager::stop() {

	}

	void InputManager::initialize() {
		
		//mOgre = OgreRender::getSingletonPtr();
		/*
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		*/
		
		mhWnd = OgreManager::getSingletonPtr()->getWindowHandler();

		if(mhWnd ==0)
			return;

		OIS::ParamList pl;
		pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(mhWnd)));

		mInputManager = OIS::InputManager::createInputSystem( pl );
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true));
		mMouse->setEventCallback(this);
		mKeyboard->setEventCallback(this);
		
		mMouse->setEventCallback(this);
		mKeyboard->setEventCallback(this);

	}

	InputManager::~InputManager() {
		
		eventMouseMoved.detachAll();

		if( mInputManager != NULL )
		{
			mInputManager->destroyInputObject( mMouse );
			mInputManager->destroyInputObject( mKeyboard );

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}

	void InputManager::capture() {
		mMouse->capture();
		mKeyboard->capture();
	}

	const OIS::MouseState InputManager::getMouseStat() {
		const OIS::MouseState ms = mMouse->getMouseState();
		return ms;
	}

	//bool InputManager::isRightButtonDown() {
	//	const OIS::MouseState ms = mMouse->getMouseState();
	//	if(ms.buttonDown(OIS::MB_Right))
	//		return true;
	//	return false;
	//}
	//
	//bool InputManager::isLeftButtonDown() {
	//	const OIS::MouseState &ms = mMouse->getMouseState();
	//	if(ms.buttonDown(OIS::MB_Left))
	//		return true;
	//	return false;
	//}

	//bool InputManager::isMiddleButtonDown() {
	//	const OIS::MouseState ms = mMouse->getMouseState();
	//	if(ms.buttonDown(OIS::MB_Middle))
	//		return true;
	//	return false;
	//}

	void  InputManager::setWindowExtents(int width, int height){
		const OIS::MouseState &ms = mMouse->getMouseState();
		ms.width = width;
		ms.height = height;
	}

	bool InputManager::mouseMoved(const OIS::MouseEvent &evt) {
		int i = evt.state.Z.rel;

		eventMouseMoved.notify(evt);

		return true;
	}

	bool InputManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
		eventMousePressed.notify(evt,btn);
		return true;
	}

	bool InputManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
		eventMouseReleased.notify(evt,btn);
		return true;
	}

	// KeyListener
	bool InputManager::keyPressed(const OIS::KeyEvent &evt) {
		eventKeyPressed.notify(evt);
		return true;
	}

	bool InputManager::keyReleased(const OIS::KeyEvent &evt) {
		eventKeyReleased.notify(evt);
		return true;
	}

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
	
	void InputManager::windowResized(Ogre::RenderWindow* rw){
		eventWindowResized.notify(rw);
	}
	void InputManager::windowClosed(Ogre::RenderWindow* rw){
		eventWindowClosed.notify(rw);
		stop();
		TaskManager::getSingleton().killAllTasks();
	}

} //end namespace
