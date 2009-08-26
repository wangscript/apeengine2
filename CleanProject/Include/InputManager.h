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

#ifndef _InputManager_H
#define _InputManager_H

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;

	class NebulaDllPrivate	InputManager : public ITask,
							public Ogre::Singleton<InputManager>,
				  			public OIS::MouseListener, 
							public OIS::KeyListener, 
							public OIS::JoyStickListener,
							public Ogre::WindowEventListener
	{
	private:
		OIS::InputManager *mInputManager;
		OIS::Mouse *mMouse;
		OIS::Keyboard *mKeyboard;
		
		unsigned long mhWnd;

		//bool mShutDown;
		//bool mMouseLeftButton;
		//bool mMouseRightButton;
		//bool mMouseMiddleButton;
		//Radian mPitch;
		//Radian mYaw;

		//Set Lua bindings
		void setBindings();

		// MouseListener
		bool mouseMoved(const OIS::MouseEvent &evt);
		bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
		bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);

		// KeyListener
		bool keyPressed(const OIS::KeyEvent &evt);
		bool keyReleased(const OIS::KeyEvent &evt);
		
		// JoyStickListener
		bool buttonPressed(const OIS::JoyStickEvent &evt, int index);
		bool buttonReleased(const OIS::JoyStickEvent &evt, int index);
		bool axisMoved(const OIS::JoyStickEvent &evt, int index);
		bool povMoved(const OIS::JoyStickEvent &evt, int index);

		// Window events
		void windowResized(Ogre::RenderWindow* rw);
		void windowClosed(Ogre::RenderWindow* rw);

		void setWindowExtents(int width, int height) ;
		

		void capture();
		void updateMouseMetrics(int width,int height);

	public:
		
		//////////////////////////////////////////////////////////////////////////
		//Events

		//Mouse Moved
		CppEvent1<bool,const OIS::MouseEvent&> eventMouseMoved;
		//Mouse Pressed
		CppEvent2<bool,const OIS::MouseEvent&, OIS::MouseButtonID> eventMousePressed;
		//Mouse Released
		CppEvent2<bool,const OIS::MouseEvent&, OIS::MouseButtonID> eventMouseReleased;

		//Key pressed
		CppEvent1<bool,const OIS::KeyEvent&> eventKeyPressed;
		//Key released
		CppEvent1<bool,const OIS::KeyEvent&> eventKeyReleased;

		//Window resized
		CppEvent1<bool,Ogre::RenderWindow*> eventWindowResized;
		//Window Close
		CppEvent1<bool,Ogre::RenderWindow*> eventWindowClosed;

		//////////////////////////////////////////////////////////////////////////

		InputManager(); 
		~InputManager();

		static InputManager& getSingleton(void);
		static InputManager* getSingletonPtr(void);

		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();
		void initialize();
		
		//bool isRightButtonDown();
		//bool isLeftButtonDown();
		//bool isMiddleButtonDown();

		const OIS::MouseState getMouseStat();
		OIS::Keyboard* getKeyboardObject();		
		OIS::Mouse* getMouseObject();

	};

} //end namespace

#endif