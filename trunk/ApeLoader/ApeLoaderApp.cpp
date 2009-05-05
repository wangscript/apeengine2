#include "ApeLoaderApp.h"
//#include "InputHandler.h"
#include "OgreRender.h"
#include "ApeManager.h"
#include "InputManager.h"

#include "SoundManager.h"
//#include "AIManager.h"

/*
class testclass : public Ogre::Singleton<testclass> {
public:
	static bool test;

	testclass(){};
	~testclass(){};
};
testclass* testclass::ms_Singleton = 0;
bool testclass::test = false;
*/

ApeLoaderApp::ApeLoaderApp(const char* cmdLine) : mName(cmdLine)
{

}

ApeLoaderApp::~ApeLoaderApp() {

}

void ApeLoaderApp::go() {

	//////////////////////////////////////////////////////////////////////////
	//Start Engine
	new OgreRender();
	new ApeManager();
	new InputManager();
	new Physics();
	//new EditableTerrain();
	new ApeSceneManager();
	new ObjectManager();
	new ZoneManager();
	new SoundManager();
	//new PagingSystem();

	//new AIManager();

	OgreRender::getSingleton().initialize();
	ApeManager::getSingleton().initialize();
	InputManager::getSingleton().initialize();
	Physics::getSingleton().initialize();
	//EditableTerrain::getSingleton().initialize();
	ApeSceneManager::getSingleton().initialize();
	ZoneManager::getSingleton().initialize();
	ObjectManager::getSingleton().initialize();
	SoundManager::getSingleton().initialize();
	//PagingSystem::getSingleton().initialize();

	ObjectManager::getSingleton().addCustomGO();
	
	
	//AIManager::getSingleton().initialize();

	//ObjectManager::getSingleton().loadDotSceneFile("test.scene");

	if(ApeSceneManager::getSingleton().mUseZoneManager) {
		ZoneManager::getSingleton().createZones();

		//Ogre::WindowEventUtilities::messagePump();
		//OgreRender::getSingleton().update();

		ZoneManager::getSingleton().updateObjectsToZones();

		//Ogre::WindowEventUtilities::messagePump();
		//OgreRender::getSingleton().update();

		//ZoneManager::getSingleton().updateObjectsToZones();


	}

	SoundManager::getSingleton().updateSoundObjects();
	
	//ApeManager::getSingleton().initialize();
	//ApeManager::getSingleton().start();
	//////////////////////////////////////////////////////////////////////////

	InputManager::getSingleton().esc = false;

	while (!InputManager::getSingleton().esc) {
		Ogre::WindowEventUtilities::messagePump();

		InputManager::getSingleton().capture();
	
		if(InputManager::getSingleton().esc)
			InputManager::getSingleton().esc = true;
		
		//ApeManager::getSingleton().update();
		ObjectManager::getSingleton().update();

		OgreRender::getSingleton().updateTimer();
	
		static Ogre::Timer timer;
		Physics::getSingleton().simulate(timer.getMilliseconds() * 0.01);
		//Physics::getSingleton().simulate(timer.getMilliseconds() * 0.00001);
		timer.reset();

		//AIManager::getSingleton().updateSimulationAndRedraw(0,OgreRender::getSingleton().getTimeSinceLastFrame());

		InputManager::getSingleton().handleCamera(OgreRender::getSingleton().getTimeSinceLastFrame());
		SoundManager::getSingleton().update(OgreRender::getSingleton().getTimeSinceLastFrame());

		OgreRender::getSingleton().update();

		//PagingSystem::getSingleton().update();

		//ApeManager::getSingleton().update();
		//OgreRender::getSingletonPtr()->update();
	}

	//PagingSystem::getSingleton().~PagingSystem();

	OgreRender::getSingleton().destroy();
	ApeManager::getSingleton().~ApeManager(); // ~Singleton();
	InputManager::getSingleton().~InputManager();
	//ObjectManager::getSingleton().~ObjectManager();
	ZoneManager::getSingleton().~ZoneManager();
	//EditableTerrain::getSingleton().~EditableTerrain();
	Physics::getSingleton().~Physics();
	

//	ApeManager::getSingleton().mInstance = 0;

	return;
}
/*
void ApeLoaderApp::OnStateChanged(ApplicationState as) {

	const char * test = mName;

	ApplicationState myState = as;

	return;
}
*/
