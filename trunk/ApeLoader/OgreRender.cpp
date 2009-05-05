#include <iostream>

#include "OgreRender.h"
#include "InputHandler.h"
#include "ApeManager.h"
#include "ApeSceneManager.h"
#include "ObjectManager.h"
#include "OgrePCZSceneManager.h"

template<> OgreRender* Ogre::Singleton<OgreRender>::ms_Singleton = 0;

OgreRender* OgreRender::getSingletonPtr(void)
{
	return ms_Singleton;
}
OgreRender& OgreRender::getSingleton(void)
{  
	//assert( ms_Singleton );  
	return ( *ms_Singleton );  
}

Real OgreRender::getTimeMS() {
	static Ogre::Timer timer;
	return timer.getMilliseconds();
}

OgreRender::OgreRender() {
	
}
OgreRender::~OgreRender() {
	//destroy();
	//delete mRoot;
	//delete mWindow;
	//delete mSceneMgr;
	//delete mCamera;
	//delete mViewport;
	//mRoot->destroySceneManager(mSceneMgr);
	// deleting the root will take care of the window and the root itself
	//delete mRoot;

}

//Initialize Ogre API
bool OgreRender::initialize() {
	//makeConnections();
	
	createRoot();
	createWindow();
	createSceneManager();
	createCamera();
	loadResources();

	mDebugText = new DebugText(mSceneMgr,mWindow);
	
	//sig_OgreRender.emit(this);
	mElapsedTime = 0.0f;
	
	return true;
}

/*
void OgreRender::makeConnections() {
	
	//Retrieve receiver's pointers and set their signals
	//InputHandler* mInput = ApeManager::getSingleton().getInputImp();
	Physics* mPhysics = ApeManager::getSingleton().getPhysicsImp();
	EditableTerrain* mTerrain = ApeManager::getSingleton().getTerrainImp();
	ApeScene* mScene = ApeManager::getSingleton().getApeSceneImp();
	ObjectManager* mObjMan = ApeManager::getSingleton().getObjectManagerImp();

	//sig_OgreRender.connect(mInput, &InputHandler::OnOgreRender_Created);
	//sig_OgreRender.connect(mPhysics, &Physics::OnOgreRender_Created);
	sig_OgreRender.connect(mTerrain, &EditableTerrain::OnOgreRender_Created);
	sig_OgreRender.connect(mScene, &ApeScene::OnOgreRender_Created);
	//sig_OgreRender.connect(mObjMan, &ObjectManager::OnOgreRender_Created);
	
	//sig_hWnd.connect(mInput, &InputHandler::On_OgreWindowCreated);
	//sig_SceneMgr.connect(mInput, &InputHandler::On_OgreWindowCreated);
}
*/

DebugText* OgreRender::getDebugText() {
	return mDebugText;
}
void OgreRender::update() {
	//mDebugText->addText("a");

	mDebugText->printText();

	mRoot->renderOneFrame();
	updateTimer();
	
}
bool OgreRender::createRoot() {
	String pluginsPath;

	mRoot = new Root("plugins.cfg","ogre.cfg", "Ogre.log");

	//assert(mRoot);

	if(!mRoot) {
		Ogre::LogManager::getSingleton().logMessage("*** Ogre - Error creating Root! *** ");
		return false;
	}

	return true;
}

//Load Application resources
bool OgreRender::loadResources() {

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

				//if(secName == "Bootstrap" || secName == "General" || secName == "ET") {
				if(secName != "Client") {
					typeName = i->first;
					archName = i->second;
					ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
				}
			}
    }

	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	TextureManager::getSingleton().setDefaultNumMipmaps(5);
	return true;
}

//Display Ogre condig dialog
bool OgreRender::createWindow() {
    if(mRoot->showConfigDialog())
    {
        mWindow = mRoot->initialise(true,"Ape Client");
		
		if(mWindow) {
			mWindow->getCustomAttribute("WINDOW", &hWnd);
		} else {
			Ogre::LogManager::getSingleton().logMessage("Ogre - Error initializing Render Window");
		}
    }
	return true;
}
void OgreRender::createSceneManager() {
	//if(mRoot)

	if(ApeSceneManager::getSingleton().mUseZoneManager) {
		
		//mRoot->createSceneManager("PCZSceneManager", "PCZSceneManager");
		//new ZoneManager("PCZSceneManager");
		//mSceneMgr = (Ogre::SceneManager*)(ZoneManager::getSingletonPtr());

		mSceneMgr = mRoot->createSceneManager("PCZSceneManager", "PCZSceneManager");
		//mSceneMgr = (Ogre::SceneManager*)( new ZoneManager("PCZSceneManager") );
		//new ZoneManager("PCZSceneManager");
		
		//mSceneMgr = (Ogre::SceneManager*)(ZoneManager::getSingletonPtr());

		//ZoneManager::getSingleton().initialize();
		// initialize the scene manager using terrain as default zone
		String zoneTypeName = "ZoneType_Default";
		String zoneFilename = "none";

		//ZoneManager::getSingleton() = (PCZSceneManager*)mSceneMgr;

		((PCZSceneManager*)mSceneMgr)->init(zoneTypeName);
		((PCZSceneManager*)mSceneMgr)->enableSky(true);
		
		

	} else {
		mSceneMgr = mRoot->createSceneManager("OctreeSceneManager", "ETInstance");
	}
}

SceneManager* OgreRender::getSceneManager() {
	//if(mSceneMgr)
		return mSceneMgr;
}
Camera* OgreRender::getCamera() {
	//if(mCamera)
		return mCamera;
}
void OgreRender::createCamera() {
	if(mSceneMgr) {
		mCamera =  mSceneMgr->createCamera("MainCamera");

		//mSceneMgr->setShadowTechnique(SHADOWDETAILTYPE_STENCIL);
		//mSceneMgr->set
		//mSceneMgr->setShadowColour( ColourValue(0.5, 0.5, 0.5) );

		//Borrar despues
		
		mCamera->setPosition(204.9f,186.0f,402.0f);
		
	
		/*
		Ogre::Light *lightp = mSceneMgr->createLight("flashLightNode");
		lightp->setType(Light::LT_DIRECTIONAL);
		//lightp->setType(Light::LT_POINT);
		lightp->setSpecularColour(0.5,0.5,0.5);
		lightp->setDiffuseColour(1.4,1.4,1.4);
		//lightp->setPosition(0,-430,0);
		lightp->setPosition(0,1430,0);
		lightp->setDirection(0,-1,0);
		//lightp->setCastShadows(true);
		*/

		/*
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		Ogre::Light *lightp = mSceneMgr->createLight("flashLightNode");
		lightp->setType(Light::LT_POINT);
		lightp->setPosition(0,3200,0);
		lightp->setDirection(0,-1,0);
		lightp->setSpecularColour(0.0,0.452381,0.0);
		lightp->setDiffuseColour(1.0,1.0,1.0);

		if(lightp->getType() == Ogre::Light::LightTypes::LT_SPOTLIGHT)
			lightp->setSpotlightRange(Degree(80),Degree(90)); 

		lightp->setAttenuation(100000,1.0,0.0,0); //0.0005
		lightp->setCastShadows(true);
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		*/


		/*
		Ogre::Light *lightp = mSceneMgr->createLight("flashLightNode");
		lightp->setType(Light::LT_POINT);
		lightp->setPosition(0,1400,0);
		//lightp->setSpotlightRange(Degree(30), Degree(50));
		Vector3 dir;
		//dir = -lightp->getPosition();
		//dir.normalise();
		//lightp->setDirection(dir);
		lightp->setDirection(0,-1,0);

		//lightp->setDiffuseColour(0.35, 0.35, 0.38);
		//lightp->setSpecularColour(0.9, 0.9, 1);
		lightp->setSpecularColour(0.5,0.5,0.5);
		lightp->setDiffuseColour(1.4,1.4,1.4);
		lightp->setCastShadows(true);
*/


		//mSceneMgr->setAmbientLight(ColourValue(0.2,0.2,0.2));

		//////////////////////////////////////////////////////////////////////////

		mViewport = mWindow->addViewport(mCamera);
		//mViewport->setBackgroundColour(ColourValue(0.47f, 0.67f, 0.96f));	//Blue sky background color
		mViewport->setBackgroundColour(ColourValue(0.0f, 0.0f, 0.0f));
		

		mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));
		mCamera->setNearClipDistance(1.0f);
		mCamera->setFarClipDistance(5000.0f);
	} else {
		Ogre::LogManager::getSingleton().logMessage("Ogre - Error creating camera, no Scene Manager");
	}
	
}
/*
void OgreRender::createViewport() {
	if(mWindow) {
		mViewport = mWindow->addViewport(mCamera);
		mViewport->setBackgroundColour(ColourValue(0.47f, 0.67f, 0.96f));	//Blue sky background color
	} else {
		Ogre::LogManager::getSingleton().logMessage("Ogre - Error creating Viewport, no RenderWindow created");
	}
}
*/
Viewport* OgreRender::getViewport() {
	return mViewport;
}

void OgreRender::destroy(){
	if (mRoot) {
		delete mRoot;
	}
}

Root* OgreRender::getRoot(){
	return mRoot;
}

RenderWindow* OgreRender::getWindow() {
	return mWindow;
}

unsigned long OgreRender::getWindowHandler() {
	return hWnd;
}

void OgreRender::updateTimer() {

	mFinishTime = mTimer.getMilliseconds();
	mElapsedTime = (mFinishTime - mStartTime ) / 1000;
	mStartTime = mTimer.getMilliseconds();
}

Ogre::Real OgreRender::getTimeSinceLastFrame() {
	return mElapsedTime;
}

