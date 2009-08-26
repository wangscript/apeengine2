#include "OgreManager.h"

template<> Nebula::OgreManager* Ogre::Singleton<Nebula::OgreManager>::ms_Singleton = 0;

namespace Nebula {

	OgreManager::OgreManager()
	{
		if(!initialize()) {
			this->canKill = true;
			//TaskManager::getSingleton().killAllTasks();
			//return false;
		}
		
		mDebugText = new DebugText(getSceneManager(),
								   getWindow());

		mCollisionTools = new CollisionTools(getSceneManager());

	}
	OgreManager::~OgreManager()
	{

	}

	SceneNode* OgreManager::createChildSceneNode( SceneNode *obj, const String name )
	{
		return obj->createChildSceneNode( name );
	}

	Vector3 OgreManager::getBoneWorldPosition(Ogre::Entity *ent, Ogre::Bone *bone)
    {
        Ogre::Vector3 world_position = bone->_getDerivedPosition();

        //multiply with the parent derived transformation
		Ogre::Node* pParentNode = ent->getParentNode();
        Ogre::SceneNode* pSceneNode = ent->getParentSceneNode();
        while (pParentNode != NULL)
        {
            //process the current i_Node
            if (pParentNode != pSceneNode)
            {
                //this is a tag point (a connection point between 2 entities). which means it has a parent i_Node to be processed
				world_position = static_cast<Ogre::TagPoint*>(pParentNode)->_getFullLocalTransform() * world_position;
                pParentNode = static_cast<Ogre::TagPoint*>(pParentNode)->getParentEntity()->getParentNode();
            }
            else
            {
                //this is the scene i_Node meaning this is the last i_Node to process
                world_position = pParentNode->_getFullTransform() * world_position;
                break;
            }
        }
        return world_position;
    }
	Quaternion OgreManager::getBoneWorldOrientation(Ogre::Entity *ent, Ogre::Bone *bone)
    {
        Ogre::Quaternion world_orientation = bone->_getDerivedOrientation();

        //multiply with the parent derived transformation
		Ogre::Node* pParentNode = ent->getParentNode();
        Ogre::SceneNode* pSceneNode = ent->getParentSceneNode();
        while (pParentNode != NULL)
        {
            //process the current i_Node
            if (pParentNode != pSceneNode)
            {
                //this is a tag point (a connection point between 2 entities). which means it has a parent i_Node to be processed
				world_orientation = static_cast<Ogre::TagPoint*>(pParentNode)->_getDerivedOrientation() * world_orientation;
                pParentNode = static_cast<Ogre::TagPoint*>(pParentNode)->getParentEntity()->getParentNode();
            }
            else
            {
                //this is the scene i_Node meaning this is the last i_Node to process
                world_orientation = pParentNode->_getDerivedOrientation() * world_orientation;
                break;
            }
        }
        return world_orientation;
    }

	DebugText* OgreManager::getDebugText() {
		return mDebugText;
	}

	void OgreManager::setBindings() {

	}

	OgreManager* OgreManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}
	OgreManager& OgreManager::getSingleton(void)
	{
		assert( ms_Singleton );  
		return ( *ms_Singleton );
	}

	void OgreManager::setCamera(Ogre::Camera* cam) {
		mCamera = boost::shared_ptr<Ogre::Camera>(cam);
	}

	GameObject* OgreManager::castRayGetClosest(Vector3 startPosition, Vector3 direction, bool omitTriggers,bool omitActors, bool omitStatic, bool omitDynamic, bool omitCharacters)
	{
		//mCollisionTools->raycastFromCamera(mWindow.get(),mCamera,
		Ogre::Vector3 resultPosition;
		Ogre::ulong target;
		float closestDistance;
		Ogre::Entity* entity = mCollisionTools->raycastFromPoint(startPosition,direction,resultPosition,target,closestDistance);
		if(entity) {
			GameObject* obj = Ogre::any_cast<GameObject*>(entity->getUserAny());
			return obj;
		}
		return NULL;
	}

	bool OgreManager::start()
	{
		return true;
	}

	void OgreManager::onSuspend()
	{
		
	}

	void OgreManager::update()
	{
		updateTimer();
		//mRoot->getRenderSystem()->_initRenderTargets();
		mDebugText->printText();

		Ogre::WindowEventUtilities::messagePump();
		if (mWindow->isActive() == false)
			mWindow->setActive(true);

		mRoot->renderOneFrame();
	}
	
	Ogre::Camera* OgreManager::getCamera() {
		return mCamera.get();
	}

	void OgreManager::onResume()
	{	
		
	}

	void OgreManager::stop()
	{
		//destroyGui();

		// очищаем сцену
		if (mSceneMgr) {
			mSceneMgr->clearScene();
			mSceneMgr->destroyAllCameras();
			//mSceneMgr = 0;
		}

		//destroyInput(); // удаляем ввод

		if (mWindow) {
			mWindow->destroy();
			//mWindow = 0;
		}

		if (mRoot) {
			Ogre::RenderWindow * mWindow = mRoot->getAutoCreatedWindow();
			if (mWindow) 
				mWindow->removeAllViewports();
			//delete mRoot;
			//mRoot = 0;
		}

	}

	bool OgreManager::initialize() {
		//makeConnections();

		if(!createRoot()) {
			return false;
		}
		if(!createWindow()) {
			return false;
		}
		if(!createSceneManager()) {
			return false;
		}
		if(!createCamera()) {
			return false;
		}
		if(!loadResources()) {
			return false;
		}

		setupShadows();

		//mDebugText = boost::shared_ptr<DebugText>(new DebugText(mSceneMgr.get(),mWindow.get()));

		return true;
	}

	void OgreManager::updateTimer() {

		mFinishTime = mTimer.getMilliseconds();
		mElapsedTime = (mFinishTime - mStartTime ) / 1000;
		mStartTime = mTimer.getMilliseconds();
	}

	Ogre::Real OgreManager::getTimeSinceLastFrame() {
		return mElapsedTime;
	}

	Ogre::Real OgreManager::getGlobalTime_Milliseconds() {
		return mTimer.getMilliseconds();
	}

	bool OgreManager::createRoot() {
		
		String pluginsPath;

		mRoot = boost::shared_ptr<Root>(new Root("plugins.cfg","ogre.cfg", "Ogre.log"));

		if(!mRoot.get()) {
			Ogre::LogManager::getSingleton().logMessage("*** Ogre - Error creating Root! *** ");
			return false;
		}

		return true;

	}
	
	void OgreManager::activateDepthShadowMapping(bool val) {
		mShadowMaps = true;
	}
	
	bool OgreManager::isDepthShadowMapping() {
		return mShadowMaps;
	}

	void OgreManager::setupShadows() {
		mShadowMaps = false;

		if(mShadowMaps) {
			mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);

			mSceneMgr->setShadowTexturePixelFormat(Ogre::PF_FLOAT32_R);

			mSceneMgr->setShadowTextureCasterMaterial("Ogre/DepthShadowmap/Caster/Float"); ///PCF"
			mSceneMgr->setShadowTextureReceiverMaterial("Ogre/DepthShadowmap/Receiver/Float/PCF");
			mSceneMgr->setShadowTextureSelfShadow(true);	
			mSceneMgr->setShadowTextureSettings(1024, 2);
			mSceneMgr->setShadowColour(Ogre::ColourValue(0.2, 0.2, 0.2));
			
		} else {
			
		}

	}
	
	bool OgreManager::createSceneManager() {
		
		mSceneMgr = boost::shared_ptr<SceneManager>(mRoot->createSceneManager(Ogre::ST_GENERIC));
		if(!mSceneMgr) {
			Ogre::LogManager::getSingleton().logMessage("Ogre - Error creating Scene Manager");
			return false;
		}

		return true;
	}

	bool OgreManager::createWindow() {

		bool dialogResult = mRoot->showConfigDialog();
		if(dialogResult)
		{
			mWindow = boost::shared_ptr<RenderWindow>(mRoot->initialise(true,"Nebula Engine"));

			if(mWindow.get()) {
				mWindow->getCustomAttribute("WINDOW", &mhWnd);
				#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
					// вытаскиваем дискриптор окна
					size_t hWnd = 0;
					mWindow->getCustomAttribute("WINDOW", &hWnd);
					// берем имя нашего экзешника
					char buf[MAX_PATH];
					::GetModuleFileNameA(0, (LPCH)&buf, MAX_PATH);
					// берем инстанс нашего модуля
					HINSTANCE instance = ::GetModuleHandleA(buf);
					// побыстрому грузим иконку
					HICON hIcon = ::LoadIcon(instance, MAKEINTRESOURCE(1001));
					if (hIcon) {
						::SendMessageA((HWND)hWnd, WM_SETICON, 1, (LPARAM)hIcon);
						::SendMessageA((HWND)hWnd, WM_SETICON, 0, (LPARAM)hIcon);
					}
				#endif

			} else {
				Ogre::LogManager::getSingleton().logMessage("Ogre - Error initializing Render Window");
				return false;
			}
		} else {
			Ogre::LogManager::getSingleton().logMessage("Ogre - Config dialog canceled by user");
			return false;
		}
		return true;
	}

	SceneNode* OgreManager::getRootSceneNode() {
		return mSceneMgr->getRootSceneNode();
	}

	bool OgreManager::createCamera() {
		if(mSceneMgr.get()) {
			mCamera = boost::shared_ptr<Camera>(mSceneMgr->createCamera("MainCamera"));
			//mCamera->setPosition(204.9f,186.0f,402.0f);

			mViewport = boost::shared_ptr<Viewport>(mWindow->addViewport(mCamera.get()));
			mViewport->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));

			mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));
			//mCamera->setNearClipDistance(1.0f);
			//mCamera->setFarClipDistance(5000.0f);

			mCamera->setFOVy(Degree(84));
			//mCamera->setAspectRatio(1.33333);
			mCamera->setNearClipDistance(0.01);
			mCamera->setFarClipDistance(1000);


			mViewport->setBackgroundColour(Ogre::ColourValue(0,0.2,0.0434783,1));
			
		} else {
			Ogre::LogManager::getSingleton().logMessage("Ogre - Error creating camera, no Scene Manager");
			return false;
		}
		return true;
	}

	bool OgreManager::loadResources() {
		
		Ogre::LogManager::getSingleton().logMessage("*** Ogre - Loading Resources *** ");

		// Load resource paths from config file
		ConfigFile cf;
		cf.load("resources.cfg");

		// Go through all sections & settings in the file
		ConfigFile::SectionIterator seci = cf.getSectionIterator();

		String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			ConfigFile::SettingsMultiMap *settings = seci.getNext();
			ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
			}
		}

		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		
		TextureManager::getSingleton().setDefaultNumMipmaps(5);
		
		return true;
	}
	Viewport* OgreManager::getViewport() {
		return mViewport.get();
	}

	Root* OgreManager::getRoot(){
		return mRoot.get();
	}

	RenderWindow* OgreManager::getWindow() {
		return mWindow.get();
	}

	unsigned long OgreManager::getWindowHandler() {
		return mhWnd;
	}
	SceneManager* OgreManager::getSceneManager() {
		return mSceneMgr.get();
	}

} //end namespace
