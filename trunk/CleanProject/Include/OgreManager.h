/*
Nebula Engine
http://code.google.com/p/apeengine2/

Copyright (c) 2008 Pablo Santiago Nuñez

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#ifndef _OGRE_TASK_H
#define _OGRE_TASK_H

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	using namespace boost;
	using namespace std;
	using namespace MOC;

	class DebugText;

	class NebulaDllPrivate OgreManager : public ITask, public Ogre::Singleton<OgreManager>
	{
	public:
		OgreManager();
		~OgreManager();
		
		static OgreManager& getSingleton(void);
		static OgreManager* getSingletonPtr(void);

		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();
		
		SceneNode* createChildSceneNode( Ogre::SceneNode *obj, const String name );

		Viewport* getViewport();
		Root* getRoot();
		RenderWindow* getWindow();
		unsigned long getWindowHandler();
		SceneManager* getSceneManager();
		DebugText* getDebugText();
		Ogre::Real getTimeSinceLastFrame();
		Ogre::Real getGlobalTime_Milliseconds();
		
		void setupShadows();
		void activateDepthShadowMapping(bool val);
		bool isDepthShadowMapping();

		Vector3 getBoneWorldPosition(Ogre::Entity *ent, Ogre::Bone *bone);
		Quaternion getBoneWorldOrientation(Ogre::Entity *ent, Ogre::Bone *bone);

		SceneNode* getRootSceneNode();

		void setCamera(Ogre::Camera*);
		Ogre::Camera* getCamera();
		
		CollisionTools* getCollisionTools() {
			return mCollisionTools;
		}

		GameObject* castRayGetClosest(Vector3 startPosition, Vector3 direction, bool omitTriggers,bool omitActors, bool omitStatic, bool omitDynamic, bool omitCharacters);

	protected:
		

	private:
		
		bool initialize();
		
		void updateTimer();

		bool createRoot();
		bool createSceneManager();
		bool createWindow();
		bool createCamera();
		bool loadResources();
		
		//Set Lua bindings
		void setBindings();

		bool mShadowMaps;

		shared_ptr<Root> mRoot;
		shared_ptr<RenderWindow> mWindow;
		shared_ptr<SceneManager> mSceneMgr;
		shared_ptr<Camera> mCamera;
		shared_ptr<Viewport> mViewport;

		unsigned long mhWnd;

		Ogre::Timer mTimer;
		Real mStartTime;
		Real mFinishTime;
		Real mElapsedTime;

		CollisionTools* mCollisionTools;

		DebugText* mDebugText;
	};


} //end namespace

#endif