#include <EnginePrerequisites.h>
#include "TestApp.h"

using namespace Nebula;

class InputManager;

template<> OgreManager* Ogre::Singleton<OgreManager>::ms_Singleton = 0;
template<> TaskManager* Ogre::Singleton<TaskManager>::ms_Singleton = 0;
template<> LuaStateManager* Ogre::Singleton<LuaStateManager>::ms_Singleton = 0;
template<> GuiManager* Ogre::Singleton<GuiManager>::ms_Singleton = 0;
template<> VideoManager* Ogre::Singleton<VideoManager>::ms_Singleton = 0;
template<> SoundManager* Ogre::Singleton<SoundManager>::ms_Singleton = 0;
template<> PhysicsManager* Ogre::Singleton<PhysicsManager>::ms_Singleton = 0;
template<> OgreMaxManager* Ogre::Singleton<OgreMaxManager>::ms_Singleton = 0;
template<> ParticleManager* Ogre::Singleton<ParticleManager>::ms_Singleton = 0;
template<> Nebula::InputManager* Ogre::Singleton<Nebula::InputManager>::ms_Singleton = 0;

TestApp::TestApp() {
	
}

TestApp::~TestApp() {

}

void TestApp::go(void) {
	
	using namespace boost;
	using namespace Nebula;

	CLog::Get().Write(LOG_APP,"****************************************************");
	CLog::Get().Write(LOG_APP,"Nebula Engine Started");
	CLog::Get().Write(LOG_APP,"****************************************************");

	new LuaStateManager();
	new TaskManager();
	new OgreManager();
	new Nebula::InputManager();
	new GuiManager();
	//new VideoManager();
	new PhysicsManager();
	new OgreMaxManager();
	new SoundManager();
	new ParticleManager();
	
	//OgreMaxManager::getSingleton().loadSceneFile("test.scene");
	
	
	OgreManager::getSingleton().priority = 2;
	if(!TaskManager::getSingleton().addTask(TaskManager::getSingletonPtr())) {
		/*CLog::Get().Write(LOG_APP,"*** Error loading Ogre. Cant continue.");*/
		return;
	}
	OgreManager::getSingleton().priority = 3;
	if(!TaskManager::getSingleton().addTask(LuaStateManager::getSingletonPtr())) {
		/*CLog::Get().Write(LOG_APP,"*** Error loading Ogre. Cant continue.");*/
		return;
	}
	OgreManager::getSingleton().priority = 4;
	if(!TaskManager::getSingleton().addTask(OgreMaxManager::getSingletonPtr())) {
		/*CLog::Get().Write(LOG_APP,"*** Error loading Ogre. Cant continue.");*/
		return;
	}


	Nebula::InputManager::getSingleton().priority = 1;
	TaskManager::getSingleton().addTask(Nebula::InputManager::getSingletonPtr());

	OgreManager::getSingleton().priority = 10;
	if(!TaskManager::getSingleton().addTask(OgreManager::getSingletonPtr())) {
		CLog::Get().Write(LOG_APP,"*** Error loading Ogre. Cant continue.");
		return;
	}

	SoundManager::getSingleton().priority = 11;
	TaskManager::getSingleton().addTask(SoundManager::getSingletonPtr());

	//PhysicsManager::getSingleton().priority = 12;
	//TaskManager::getSingleton().addTask(PhysicsManager::getSingletonPtr());

	GuiManager::getSingleton().priority = 20;
	TaskManager::getSingleton().addTask(GuiManager::getSingletonPtr());

	PhysicsManager::getSingleton().priority = 30;
	TaskManager::getSingleton().addTask(PhysicsManager::getSingletonPtr());

	//VideoManager::getSingleton().priority = 30;
	//TaskManager::getSingleton().addTask(VideoManager::getSingletonPtr());


	//TaskManager::getSingleton().setAllBindings();
	LuaStateManager::getSingleton().setBindings();
	LuaStateManager::getSingleton().runFile("../Media/Scripts/Nebula_Start.lua");

	TaskManager::getSingleton().execute();
	
	LuaStateManager::getSingleton().forceGarbageCollect();
	
	GuiManager::getSingleton().~GuiManager();
	TaskManager::getSingleton().~TaskManager();
	//OgreManager::getSingleton().~OgreManager();
	PhysicsManager::getSingleton().~PhysicsManager();
	OgreMaxManager::getSingleton().~OgreMaxManager();
	SoundManager::getSingleton().~SoundManager();
	ParticleManager::getSingleton().~ParticleManager();
	LuaStateManager::getSingleton().~LuaStateManager();

	CLog::Get().Write(LOG_APP,"****************************************************");
	CLog::Get().Write(LOG_APP,"Nebula Engine Finished");
	CLog::Get().Write(LOG_APP,"****************************************************");

}

