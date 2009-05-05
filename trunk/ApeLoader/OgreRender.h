#ifndef _OGRE_SYS_H_
#define _OGRE_SYS_H_

#include "Ogre.h"
//#include "sigslot.h"
//#include "Receiver.h"
#include "DebugText.h"

//#include "CCAmera.h"

#include "ParticleUniverseSystem.h"
#include "ParticleUniverseSystemManager.h"

//using namespace sigslot;
//class MessageManager;
//class CCamera;
class DebugText;
class ParticleUniverse::ParticleSystemManager;
class ParticleUniverse::ParticleSystem;

using namespace Ogre;

//class OgreRender;
class OgreRender : public Ogre::Singleton<OgreRender>
{ //: public ApplicationSignal 
public:

	OgreRender(); 
	~OgreRender();

	static OgreRender& getSingleton(void);
	static OgreRender* getSingletonPtr(void);

	bool initialize();
	bool createRoot();
	bool createWindow();
	bool loadResources();
	void createSceneManager();
	void destroy();
	//void Render();
	void update();
	//void makeConnections();
	Root* getRoot();
	RenderWindow* getWindow();
	unsigned long getWindowHandler();
	SceneManager* getSceneManager();
	Camera* getCamera();
	void createCamera();
	//void createViewport();
	Viewport* getViewport();
	void updateTimer();
	Ogre::Real getTimeSinceLastFrame();
	Real getTimeMS();

	//CCamera* mCustomCamera;
	Ogre::SceneNode* mWeaponNode;

	DebugText* getDebugText();
	//void OnApplicationState_Changed(ApplicationState as){};

	ParticleUniverse::ParticleSystemManager* getParticleManager() {
		return mParticleSystemManager;
	}
	ParticleUniverse::ParticleSystem* getParticleSystem() {
		return mSystem;
	}
private:
	Root *mRoot;
	RenderWindow *mWindow;
	unsigned long hWnd;
	SceneManager* mSceneMgr;
	Camera* mCamera;
	Viewport *mViewport;
	Ogre::Timer mTimer;
	//static 

	Real mStartTime;
	Real mFinishTime;
	Real mElapsedTime;

	//Signals
	//signal1<unsigned long> sig_hWnd;
	//signal1<Ogre::SceneManager*> sig_SceneMgr;
	
	DebugText* mDebugText;


	ParticleUniverse::ParticleSystemManager* mParticleSystemManager;
	ParticleUniverse::ParticleSystem* mSystem;

	//signal1<OgreRender*> sig_OgreRender;

};


#endif
