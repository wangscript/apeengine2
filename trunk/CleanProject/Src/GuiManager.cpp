#include "GuiManager.h"

template<> Nebula::GuiManager* Ogre::Singleton<Nebula::GuiManager>::ms_Singleton = 0;

namespace Nebula {

	GuiManager::GuiManager() : mBackgroundImage(0)
	{
		mMainMenuVisible = true;
		mDisplayFPS = false;
		mDisplayWireFrame = false;
		mDisplayNodes = false;

		mMouseOverObject = NULL;

		//CppEventHandler h1 = 
		registerEvents();

		mGUI = NULL;
		mGUI = new MyGUI::Gui();
		mGUI->initialise(OgreManager::getSingleton().getWindow());
		
		Ogre::RenderWindow* rw = OgreManager::getSingleton().getWindow();
		OnWindowResized(rw);
		
		if(mGUI)
			createConsole();


	}
	GuiManager::~GuiManager()
	{

	}

	void GuiManager::registerEvents() {
		InputManager::getSingleton().eventMouseMoved.attach(this,&GuiManager::OnMouseMoved);
		InputManager::getSingleton().eventMousePressed.attach(this,&GuiManager::OnMousePressed);
		InputManager::getSingleton().eventMouseReleased.attach(this,&GuiManager::OnMouseReleased);
		InputManager::getSingleton().eventKeyPressed.attach(this,&GuiManager::OnKeyPressed);
		InputManager::getSingleton().eventKeyReleased.attach(this,&GuiManager::OnKeyReleased);
		InputManager::getSingleton().eventWindowResized.attach(this,&GuiManager::OnWindowResized);
		InputManager::getSingleton().eventWindowClosed.attach(this,&GuiManager::OnWindowClosed);
	}

	void GuiManager::setBindings() {

	}

	void notifyMouseSetFocus_Load(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old)
	{
		SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Active");
	}

	void notifyMouseLostFocus_Load(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new)
	{
		//SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Normal");
	}
	void notifyMouseSetFocus_Save(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old)
	{
		SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Active");
	}

	void notifyMouseLostFocus_Save(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new)
	{
		//SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Normal");
	}

	void notifyMouseSetFocus_Play(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old)
	{
		SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Active");
	}

	void notifyMouseLostFocus_Play(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new)
	{
		//SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Normal");
	}
	void notifyMouseSetFocus_Options(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old)
	{
		SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Active");
	}

	void notifyMouseLostFocus_Options(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new)
	{
		//SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Normal");
	}
	void notifyMouseSetFocus_Exit(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old)
	{
		SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Active");
	}

	void notifyMouseLostFocus_Exit(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new)
	{
		//SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");		
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Normal");
	}
	
	void GuiManager::notifyMouseButtonClick_Exit(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id) //MyGUI::EventHandle_WidgetIntIntButton MyGUI::WidgetEvent::eventMouseButtonPressed
	{
		//SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/1.wav");		
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		//image->setItemName("Normal");
		TaskManager::getSingleton().killAllTasks();
	}

	void GuiManager::notifyMouseButtonClick_Play(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id) //MyGUI::EventHandle_WidgetIntIntButton MyGUI::WidgetEvent::eventMouseButtonPressed
	{
		LuaStateManager::getSingleton().runFile("../Media/Scripts/Play.lua");
	}
	void GuiManager::notifyMouseButtonClick_Load(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id) //MyGUI::EventHandle_WidgetIntIntButton MyGUI::WidgetEvent::eventMouseButtonPressed
	{
		LuaStateManager::getSingleton().runFile("../Media/Scripts/Load.lua");
	}
	void GuiManager::notifyMouseButtonClick_Save(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id) //MyGUI::EventHandle_WidgetIntIntButton MyGUI::WidgetEvent::eventMouseButtonPressed
	{
		LuaStateManager::getSingleton().runFile("../Media/Scripts/Save.lua");
	}
	void GuiManager::notifyMouseButtonClick_Options(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id) //MyGUI::EventHandle_WidgetIntIntButton MyGUI::WidgetEvent::eventMouseButtonPressed
	{
		LuaStateManager::getSingleton().runFile("../Media/Scripts/Options.lua");
	}

	void GuiManager::hideMainMenuItems() {
		if(!mGUI)
			return;

		if(mMainMenuVisible) {
			mMainMenuVisible = false;
			getWallpaper()->setVisible(false);
			getConsole()->setVisible(false);
			mMenuImage_Play->setVisible(false);
			mMenuImage_Load->setVisible(false);
			mMenuImage_Save->setVisible(false);
			mMenuImage_Options->setVisible(false);
			mMenuImage_Exit->setVisible(false);
		} else {
			mMainMenuVisible = true;
			getWallpaper()->setVisible(true);
			getConsole()->setVisible(true);
			mMenuImage_Play->setVisible(true);
			mMenuImage_Load->setVisible(true);
			mMenuImage_Save->setVisible(true);
			mMenuImage_Options->setVisible(true);
			mMenuImage_Exit->setVisible(true);
		}

	}

	bool GuiManager::start()
	{
		if(mGUI) {
			//setBindings();
			//SoundManager::getSingleton().getManager()->play2D("../Media/Sounds/Churched.wav");
			//setWallpaper("background.jpg");

			//base::BaseManager::getInstance().addResourceLocation("../../Media/Demos/Demo_ItemBox");
			
			Nebula::ResourceItemInfo::registryType();

			MyGUI::ResourceManager::getInstance().load("MenuResources.xml");
			MyGUI::ResourceManager::getInstance().load("ItemBoxResources.xml");
			MyGUI::ResourceManager::getInstance().load("HealthBarResources.xml");

			//std::vector<IResourcePtr> rv = MyGUI::ResourceManager::getResources();
			
			MyGUI::Gui::getInstance().load("ItemBox_skin.xml");
			MyGUI::FontManager::getInstance().getEnumerator();

			//IResourcePtr rp = MyGUI::ResourceManager::getInstance().getResource("info_Crystal_Clear_Item0");

			//MyGUI::StaticImagePtr image;
			
			//MyGUI::StaticImagePtr* test = 
			//"backpack.png"

			Ogre::Vector2 pos;
			pos.x = OgreManager::getSingleton().getWindow()->getWidth() / 2 - 250;
			pos.y = OgreManager::getSingleton().getWindow()->getHeight() / 2 - 15;
			mMenuImage_Play = addMainMenuItem("Play",pos);
			mMenuImage_Play->eventMouseSetFocus = MyGUI::newDelegate(notifyMouseSetFocus_Play);
			mMenuImage_Play->eventMouseLostFocus = MyGUI::newDelegate(notifyMouseLostFocus_Play);
			mMenuImage_Play->setMaskPick("mask.png");
			mMenuImage_Play->eventMouseButtonPressed = MyGUI::newDelegate(this,&GuiManager::notifyMouseButtonClick_Play);

			pos.y += 64;
			mMenuImage_Load = addMainMenuItem("Load",pos);
			mMenuImage_Load->eventMouseSetFocus = MyGUI::newDelegate(notifyMouseSetFocus_Load);
			mMenuImage_Load->eventMouseLostFocus = MyGUI::newDelegate(notifyMouseLostFocus_Load);
			mMenuImage_Load->setMaskPick("mask.png");
			mMenuImage_Load->eventMouseButtonPressed = MyGUI::newDelegate(this,&GuiManager::notifyMouseButtonClick_Load);

			//pos.y += 256;
			pos.y += 64;
			mMenuImage_Save = addMainMenuItem("Save",pos);
			mMenuImage_Save->eventMouseSetFocus = MyGUI::newDelegate(notifyMouseSetFocus_Save);
			mMenuImage_Save->eventMouseLostFocus = MyGUI::newDelegate(notifyMouseLostFocus_Save);
			mMenuImage_Save->setMaskPick("mask.png");
			mMenuImage_Save->eventMouseButtonPressed = MyGUI::newDelegate(this,&GuiManager::notifyMouseButtonClick_Save);

			//pos.y += 384;
			pos.y += 64;
			mMenuImage_Options = addMainMenuItem("Options",pos);
			mMenuImage_Options->eventMouseSetFocus = MyGUI::newDelegate(notifyMouseSetFocus_Options);
			mMenuImage_Options->eventMouseLostFocus = MyGUI::newDelegate(notifyMouseLostFocus_Options);
			mMenuImage_Options->setMaskPick("mask.png");
			mMenuImage_Options->eventMouseButtonPressed = MyGUI::newDelegate(this,&GuiManager::notifyMouseButtonClick_Options);

			//pos.y += 512;
			pos.y += 64;
			mMenuImage_Exit = addMainMenuItem("Exit",pos);
			mMenuImage_Exit->eventMouseSetFocus = MyGUI::newDelegate(notifyMouseSetFocus_Exit);
			mMenuImage_Exit->eventMouseLostFocus = MyGUI::newDelegate(notifyMouseLostFocus_Exit);
			mMenuImage_Exit->eventMouseButtonPressed = MyGUI::newDelegate(this,&GuiManager::notifyMouseButtonClick_Exit);

			mMenuImage_Exit->setMaskPick("mask.png");

			
			//const MyGUI::IntSize & view = MyGUI::Gui::getInstance().getViewSize();
			//const MyGUI::IntSize size(150, 125);

			//MyGUI::StaticImagePtr image = MyGUI::Gui::getInstance().createWidget<MyGUI::StaticImage>("StaticImage", MyGUI::IntCoord((view.width - size.width) / 2, (view.height - size.height) / 2, size.width, size.height), MyGUI::Align::Default, "Main");
			//image->setItemResource("Inventory_BackPack");
			//image->setItemGroup("States");
			//image->setItemName("Normal");

			////image->setPosition(0,0);
			////image->setAlign(Align::Bottom | Align::Left);
			//
			//image->eventMouseSetFocus = MyGUI::newDelegate(notifyMouseSetFocus_Exit);
			//image->eventMouseLostFocus = MyGUI::newDelegate(notifyMouseLostFocus_Exit);
			//image->eventMouseButtonPressed = MyGUI::newDelegate(this,&GuiManager::notifyMouseButtonClick_Exit);


		}
		return true;
	}

	MyGUI::StaticImagePtr GuiManager::addMainMenuItem(Ogre::String name, Ogre::Vector2 position) {
		const MyGUI::IntSize & view = MyGUI::Gui::getInstance().getViewSize();
		const MyGUI::IntSize size(300, 74);

		MyGUI::StaticImagePtr image = MyGUI::Gui::getInstance().createWidget<MyGUI::StaticImage>("StaticImage", MyGUI::IntCoord((view.width - size.width) / 2, (view.height - size.height) / 2, size.width, size.height), MyGUI::Align::Default, "Main");
		image->setItemResource(name);
		image->setItemGroup("States");
		image->setItemName("Normal");
		
		image->setPosition(position.x,position.y);
		
		return image;
	}

	void GuiManager::onSuspend()
	{

	}

	void GuiManager::update()
	{

		//if(mKeyboard)
		//	mKeyboard->capture();

		//if(mMouse)
		//	mMouse->capture();

		if(mGUI) {
			//mKeyboard->capture();
			//mMouse->capture();
			mGUI->injectFrameEntered(OgreManager::getSingleton().getTimeSinceLastFrame());
		}

		//OIS::MouseButtonID id;
		//id = static_cast<OIS::MouseButtonID>(-1);

		//castRayFromMouse(arg,id);

	}

	void GuiManager::onResume()
	{

	}

	void GuiManager::stop()
	{
		if (mGUI) {
			mGUI->shutdown();
			delete mGUI;
			mGUI = 0;
		}
		//destroyInput();
	}

	GuiManager* GuiManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}

	GuiManager& GuiManager::getSingleton(void)
	{
		assert( ms_Singleton );  
		return ( *ms_Singleton );
	}
	
	//Ogre::Vector2 GuiManager::calculateWidgetPosition(Vector2 widgetSize, WindowPosition align) {

	//	MyGUI::IntSize& view = MyGUI::Gui::getInstance().getViewSize();
	//	const MyGUI::IntSize size(widgetSize.x, widgetSize.y);
	//		
	//	//ALIGN_TOP_LEFT,
	//	//ALIGN_TOP_CENTER,
	//	//ALIGN_TOP_RIGHT,

	//	//ALIGN_MIDDLE_LEFT,
	//	//ALIGN_MIDDLE,
	//	//ALIGN_MIDDLE_RIGHT,

	//	//ALIGN_BOTTOM_LEFT,
	//	//ALIGN_BOTTOM,
	//	//ALIGN_BOTTOM_RIGHT,

	//	Vector2 position = Vector2::ZERO;

	//	switch (align) {
	//		case ALIGN_TOP_LEFT:
	//			position = Vector2(0,0);
	//			break;
	//		case ALIGN_TOP_CENTER:
	//			position = Vector2(view.width / 2,0);
	//			break;
	//		case ALIGN_TOP_RIGHT:
	//			position = Vector2(view.width - widgetSize.x, 0);
	//			break;

	//		case ALIGN_BOTTOM_LEFT:
	//			position = Vector2(0,view.height - widgetSize.y);
	//			break;
	//		case ALIGN_BOTTOM:
	//			position = Vector2(view.width / 2,view.height - widgetSize.y);
	//			break;
	//		case ALIGN_BOTTOM_RIGHT:
	//			position = Vector2(view.width - widgetSize.x,view.height - widgetSize.y);
	//			break;
	//	}

	//	return position;
	//}

	void GuiManager::command(const Ogre::UTFString & _key, const Ogre::UTFString & _value) {

		if (_key == "colour") {
			if (_value.empty()) 
				mConsole->addToConsole(mConsole->getConsoleStringCurrent(), _key, MyGUI::utility::toString(mEdit->getTextColour()));
			else {
				MyGUI::Colour colour;
				if ( ! MyGUI::utility::parseComplex(_value, colour.red, colour.green, colour.blue, colour.alpha)) {
					mConsole->addToConsole(mConsole->getConsoleStringError(), _key, _value);
					mConsole->addToConsole(mConsole->getConsoleStringFormat(), _key, "red green blue alpha");
				}
				else {
					mConsole->addToConsole(mConsole->getConsoleStringSuccess(), _key, _value);
					mEdit->setTextColour(colour);
				}
			}
		}

		//else if (_key == "show") {
		//	if (_value.empty()) {
		//		mConsole->addToConsole(mConsole->getConsoleStringCurrent(), _key, MyGUI::utility::toString(mEdit->isVisible()));
		//	}
		//	else {
		//		bool show;
		//		if ( ! MyGUI::utility::parseComplex(_value, show)) {
		//			mConsole->addToConsole(mConsole->getConsoleStringError(), _key, _value);
		//			mConsole->addToConsole(mConsole->getConsoleStringFormat(), _key, "true | false");
		//		}
		//		else {
		//			mConsole->addToConsole(mConsole->getConsoleStringSuccess(), _key, _value);
		//			mEdit->setVisible(show);
		//		}
		//	}
		//}
		//else if (_key == "alpha") {
		//	if (_value.empty()) {
		//		mConsole->addToConsole(mConsole->getConsoleStringCurrent(), _key, MyGUI::utility::toString(mEdit->getAlpha()));
		//	}
		//	else {
		//		float alpha;
		//		if ( ! MyGUI::utility::parseComplex(_value, alpha) || (alpha < 0 || alpha > 1)) {
		//			mConsole->addToConsole(mConsole->getConsoleStringError(), _key, _value);
		//			mConsole->addToConsole(mConsole->getConsoleStringFormat(), _key, "0 - 1");
		//		}
		//		else {
		//			mConsole->addToConsole(mConsole->getConsoleStringSuccess(), _key, _value);
		//			mEdit->setAlpha(alpha);
		//		}
		//	}
		//}
		//else if (_key == "coord") {
		//	if (_value.empty()) mConsole->addToConsole(mConsole->getConsoleStringCurrent(), _key, MyGUI::utility::toString(mEdit->getCoord()));
		//	else {
		//		MyGUI::IntCoord coord;
		//		if ( ! MyGUI::utility::parseComplex(_value, coord.left, coord.top, coord.width, coord.height)) {
		//			mConsole->addToConsole(mConsole->getConsoleStringError(), _key, _value);
		//			mConsole->addToConsole(mConsole->getConsoleStringFormat(), _key, "left top width height");
		//		}
		//		else {
		//			mConsole->addToConsole(mConsole->getConsoleStringSuccess(), _key, _value);
		//			mEdit->setCoord(coord);
		//		}
		//	}
		//}
	}

	bool GuiManager::createConsole() {
		if(!mGUI)
			return true;

		mConsole = new Console();

		mEdit = mGUI->createWidget<MyGUI::Edit>("EditStretch", MyGUI::IntCoord(10, 80, 100, 100), MyGUI::Align::Default, "Overlapped");
		mEdit->setCaption("some edit");
		mEdit->setTextAlign(MyGUI::Align::Center);
		mEdit->setEditMultiLine(true);

		mEdit->setVisible(false);

		mConsole->registerConsoleDelegate("colour", MyGUI::newDelegate(this, &GuiManager::command));
		mConsole->registerConsoleDelegate("show", MyGUI::newDelegate(this, &GuiManager::command));
		mConsole->registerConsoleDelegate("alpha", MyGUI::newDelegate(this, &GuiManager::command));
		mConsole->registerConsoleDelegate("coord", MyGUI::newDelegate(this, &GuiManager::command));

		mConsole->setVisible(true);
		return true;
	}

	Console* GuiManager::getConsole() {
		return mConsole;
	}
	
	bool GuiManager::OnMouseMoved( const OIS::MouseEvent &arg ) {
		if (mGUI) 
			mGUI->injectMouseMove(arg);
		
		OIS::MouseButtonID id;
		id = static_cast<OIS::MouseButtonID>(-1);

		castRayFromMouse(arg,id,false);
		
		return true;
	}

	GameObject* GuiManager::castRayFromMouse(const OIS::MouseEvent &e, OIS::MouseButtonID id, bool mouseButtonDown)
	{
		Ogre::Vector3 resultPosition;
		Ogre::ulong target;
		float closestDistance;
		int idValue = (int)id;

		int button = static_cast<int>(id);

		Ogre::Entity* entity = OgreManager::getSingleton().getCollisionTools()->raycastFromCamera(OgreManager::getSingleton().getWindow(), 
			OgreManager::getSingleton().getCamera(), e, resultPosition, target,closestDistance);
		
		if(entity) {
			
			if(entity->getUserAny().isEmpty())
				return NULL;

			GameObject* object = Ogre::any_cast<GameObject*>(entity->getUserAny());
			
			
				if(object && mMouseOverObject) {
					if(mMouseOverObject->getID() != object->getID()) {
						eventMouseMovedEnterOverObject.notify(object,resultPosition);
						eventMouseMovedLeaveOverObject.notify(mMouseOverObject,resultPosition);
						mMouseOverObject = object;
						//return object;
					}
				} else if (object && !mMouseOverObject) {
					mMouseOverObject = object;
					eventMouseMovedEnterOverObject.notify(object,resultPosition);
					//return object;
				}
				
				if(object) {
					eventMouseMovedOverObject.notify(mMouseOverObject,resultPosition);
					mMouseOverObject = object;
					//return object;
				}

			if( button > -1) { //For mouse moved events

			//} else { //For button pressed/released events
				
				if(mouseButtonDown) {
					eventMousePressedObject.notify(object,resultPosition,id);
				} else {
					eventMouseReleasedObject.notify(object,resultPosition,id);
				}

				//if( id == OIS::MouseButtonID::


			}
			return NULL;
		} else {
			if(mMouseOverObject) {
				eventMouseMovedLeaveOverObject.notify(mMouseOverObject,Vector3(0,0,0));
				mMouseOverObject = NULL;
			}
		}

		return NULL;
	}

	bool GuiManager::OnMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
		
		if (mGUI)
			mGUI->injectMousePress(arg, id);

		castRayFromMouse(arg,id,true);

		return true;
	}

	bool GuiManager::OnMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
		
		if (mGUI) 
			mGUI->injectMouseRelease(arg, id);

		castRayFromMouse(arg,id,false);

		return true;
	}
	bool GuiManager::OnKeyPressed( const OIS::KeyEvent &arg ) {

		if ( arg.key == OIS::KC_ESCAPE ) { 
			//destroyInput();
			//stop();
			//TaskManager::getSingleton().
			//TaskManager::getSingleton().killAllTasks();
			//TaskManager::getSingleton().killAllTasks();

			//mGUI->getConsole()->setVisible(false);
			//getWallpaper()->setVisible(false);
			//getConsole()->setVisible(false);
			hideMainMenuItems();
		} 
		else if( arg.key == OIS::KC_F1 ) {
			
			if(!mDisplayFPS) {
				mDisplayFPS = true;
				OgreManager::getSingleton().getCamera()->setPolygonMode(PM_WIREFRAME);
			} else {
				mDisplayFPS = false;
				OgreManager::getSingleton().getCamera()->setPolygonMode(PM_SOLID);
			}

			mDisplayWireFrame = false;
			mDisplayNodes = false;

			return false; 
		} 
		else if( arg.key == OIS::KC_F2 ) {

			//stop();
			if(!mDisplayNodes) {
				mDisplayNodes = true;
				OgreManager::getSingleton().getSceneManager()->setDisplaySceneNodes(mDisplayNodes);
			} else {
				mDisplayNodes = false;
				OgreManager::getSingleton().getSceneManager()->setDisplaySceneNodes(mDisplayNodes);
			}
			return false; 
		} 

		else if ( arg.key == OIS::KC_SYSRQ ) {
			std::ifstream stream;
			std::string file;
			do {
				stream.close();
				static size_t num = 0;
				const size_t max_shot = 100;
				if (num == max_shot) {
					MYGUI_LOG(Info, "The limit of screenshots is exceeded : " << max_shot);
					return true;
				}
				file = MyGUI::utility::toString("screenshot_", ++num, ".png");
				stream.open(file.c_str());
			} while (stream.is_open());
			OgreManager::getSingleton().getWindow()->writeContentsToFile(file);
			return true;
		} 
		else if ( arg.key == OIS::KC_F12) {
			if (mGUI) 
				MyGUI::InputManager::getInstance().setShowFocus(!MyGUI::InputManager::getInstance().getShowFocus());
		}

		if (mGUI) 
			mGUI->injectKeyPress(arg);

		return true;
	}
	bool GuiManager::OnKeyReleased( const OIS::KeyEvent &arg ) {
		if (mGUI) 
			mGUI->injectKeyRelease(arg);
		
		return true;
	}
	bool GuiManager::OnWindowResized(Ogre::RenderWindow* rw){
		mWidth = rw->getWidth();
		mHeight = rw->getHeight();

		//if (mMouse) {
		const OIS::MouseState &ms = InputManager::getSingleton().getMouseObject()->getMouseState(); // getMouseStat(); // mMouse->getMouseState();
		ms.width = (int)mWidth;
		ms.height = (int)mHeight;
		return true;
		//}
	}
	bool GuiManager::OnWindowClosed(Ogre::RenderWindow* rw){
		//m_exit = true;
		//destroyInput();
		stop();
		TaskManager::getSingleton().killAllTasks();
		return true;
		//destroyInput();
	}

	void GuiManager::setWindowCaption(const std::string & _text)
	{
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
		size_t windowHnd = 0;
		OgreManager::getSingleton().getWindow()->getCustomAttribute("WINDOW", &windowHnd);
		::SetWindowTextA((HWND)windowHnd, _text.c_str());
#endif
	}

	void GuiManager::setWallpaper(const std::string & _filename)
	{
		if(!mGUI)
			return;

		//static MyGUI::StaticImagePtr image = nullptr;
		if (mBackgroundImage == nullptr) //image
			mBackgroundImage = mGUI->createWidget<MyGUI::StaticImage>("StaticImage", MyGUI::IntCoord(MyGUI::IntPoint(), mGUI->getViewSize()), MyGUI::Align::Stretch, "Back");
		
		mBackgroundImage->setImageTexture(_filename);
		mBackgroundImage->setNeedMouseFocus(false);
	}

	MyGUI::StaticImagePtr GuiManager::getWallpaper()
	{
		if(!mGUI)
			return NULL;

		//static MyGUI::StaticImagePtr image = nullptr;
		if (mBackgroundImage == nullptr) //image
			mBackgroundImage = mGUI->createWidget<MyGUI::StaticImage>("StaticImage", MyGUI::IntCoord(MyGUI::IntPoint(), mGUI->getViewSize()), MyGUI::Align::Stretch, "Back");
		
		//mBackgroundImage->setImageTexture(_filename);
		//mBackgroundImage->setNeedMouseFocus(false);
		
		return mBackgroundImage;
	}


	void GuiManager::setDescriptionText(const Ogre::UTFString & _text)
	{
		if(!mGUI)
			return;

		MyGUI::EditPtr text = nullptr;
		if (text == nullptr)
		{
			MyGUI::WidgetPtr panel = mGUI->createWidget<MyGUI::Widget>("PanelSmall", mGUI->getViewWidth(), -128, 400, 128, MyGUI::Align::Default, "Statistic");
			text = panel->createWidget<MyGUI::Edit>("WordWrapSimple", 10, 10, 380, 108, MyGUI::Align::Default);
			//text->setTextColour(MyGUI::Colour(0, 1, 0, 1));
			MyGUI::StaticImagePtr image = panel->createWidget<MyGUI::StaticImage>(MyGUI::WidgetStyle::Popup, "StaticImage", MyGUI::IntCoord(mGUI->getViewWidth()-48, 0, 48, 48), MyGUI::Align::Default, "Back");
			image->setItemResource("pic_CoreMessageIcon");
			image->setItemGroup("Icons");
			image->setItemName("Quest");

			MyGUI::ControllerEdgeHide * controller = new MyGUI::ControllerEdgeHide(0.5);
			MyGUI::ControllerManager::getInstance().addItem(panel, controller);
		}
		text->setCaption(_text);
	}

} //end namespace
