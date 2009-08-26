/*!
	@file
	@author		Pablo Nuñez
	@date		13/2009
	@module
*//*
	This file is part of the Nebula Engine.
	
	Nebula Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Nebula Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Nebula Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _VIDEO_MANAGER_H
#define _VIDEO_MANAGER_H

#include "EnginePrerequisites.h"

//#include "UtilsOgreDshow.h"
#include "CEGUI/CEGUI.h"
#include "OgreCEGUIRenderer.h"
#include "OgreCEGUIResourceProvider.h"
#include "OgreExternalTextureSourceManager.h"

namespace Nebula {

	using namespace Ogre;

	class NebulaDllPrivate VideoManager : public ITask,
										  public Ogre::Singleton<VideoManager>,
										  public OIS::KeyListener, 
										  public OIS::MouseListener
	{
	public:
		VideoManager();
		~VideoManager();
		
		static VideoManager& getSingleton(void);
		static VideoManager* getSingletonPtr(void);

		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();

	protected:

	private:
		TheoraVideoManager* mTheoraManager;
		TheoraVideoClip* mClip;
		
		bool mSeeking;
		bool mPaused;
		int mSeekStep;

		CEGUI::OgreCEGUIRenderer* mGUIRenderer;
		CEGUI::System* mGUISystem;
		CEGUI::Window* mGuiSheet;
		bool mShaders;
		
		TheoraVideoClip* getClip(String name);
		bool OnPlayPause(const CEGUI::EventArgs& e);
		bool OnSeekEnd(const CEGUI::EventArgs& e);
		bool OnSeekStart(const CEGUI::EventArgs& e);

		//OgreUtils::DirectShowMovieTexture* dshowMovieTextureSystem;

		void createQuad(String name,String material_name,float left,float top,float right,float bottom);

		OIS::InputManager* mInputManager;
		OIS::Keyboard* mKeyboard;
		OIS::Mouse*    mMouse;
		unsigned long mhWnd;	

		bool mouseMoved( const OIS::MouseEvent &arg );
		bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool keyPressed( const OIS::KeyEvent &arg );
		bool keyReleased( const OIS::KeyEvent &arg );

		//Set Lua bindings
		void setBindings();

	};


} //end namespace

#endif