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

#ifndef _GUI_TASK_H
#define _GUI_TASK_H

#include "EnginePrerequisites.h"

//enum WindowPosition
//{
//	ALIGN_TOP_LEFT,
//	ALIGN_TOP_CENTER,
//	ALIGN_TOP_RIGHT,
//
//	ALIGN_MIDDLE_LEFT,
//	ALIGN_MIDDLE,
//	ALIGN_MIDDLE_RIGHT,
//
//	ALIGN_BOTTOM_LEFT,
//	ALIGN_BOTTOM,
//	ALIGN_BOTTOM_RIGHT,
//};

namespace Nebula {

	class Console;

	class NebulaDllPrivate GuiManager : public ITask, 
										public Ogre::Singleton<GuiManager>
	{
	public:

		GuiManager();
		~GuiManager();
		
		static GuiManager& getSingleton(void);
		static GuiManager* getSingletonPtr(void);

		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();

		//Ogre::Vector2 calculateWidgetPosition(Vector2 widgetSize, WindowPosition align);

		void setWindowCaption(const std::string & _text);
		void setWallpaper(const std::string & _filename);

		void setBindings();
		
		void command(const Ogre::UTFString & _key, const Ogre::UTFString & _value);

		Console* getConsole();
		void hideMainMenuItems();

		CppEvent2<bool,GameObject*, Ogre::Vector3> eventMouseMovedOverObject;
		
		CppEvent2<bool,GameObject*, Ogre::Vector3> eventMouseMovedEnterOverObject;
		CppEvent2<bool,GameObject*, Ogre::Vector3> eventMouseMovedLeaveOverObject;
		
		CppEvent3<bool,GameObject*, Ogre::Vector3, int> eventMousePressedObject;
		CppEvent3<bool,GameObject*, Ogre::Vector3, int> eventMouseReleasedObject;

		
		GameObject* castRayFromMouse(const OIS::MouseEvent &e, OIS::MouseButtonID id, bool mouseButtonDown);
		
		GameObject* getMouseSelectedObject() {
			return mMouseOverObject;
		}

	private:
		MyGUI::Gui *mGUI;
		Console* mConsole;

		GameObject* mMouseOverObject;

		bool mMainMenuVisible;

		bool mDisplayFPS;
		bool mDisplayWireFrame;
		bool mDisplayNodes;
		
		MyGUI::StaticImagePtr mBackgroundImage;
		MyGUI::StaticImagePtr mMenuImage_Play;
		MyGUI::StaticImagePtr mMenuImage_Load;
		MyGUI::StaticImagePtr mMenuImage_Save;
		MyGUI::StaticImagePtr mMenuImage_Options;
		MyGUI::StaticImagePtr mMenuImage_Exit;

		void notifyMouseButtonClick_Play(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id);
		void notifyMouseButtonClick_Load(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id);
		void notifyMouseButtonClick_Save(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id);
		void notifyMouseButtonClick_Options(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id);
		void notifyMouseButtonClick_Exit(MyGUI::WidgetPtr _sender,int _left, int _top, MyGUI::MouseButton _id);

		unsigned long mhWnd;		
		unsigned int mWidth;
		unsigned int mHeight;
		
		MyGUI::EditPtr mEdit;

		MyGUI::StaticImagePtr getWallpaper();

		bool createConsole();

		void setDescriptionText(const Ogre::UTFString & _text);

		void registerEvents();

		bool OnMouseMoved( const OIS::MouseEvent &arg );
		bool OnMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool OnMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		bool OnKeyPressed( const OIS::KeyEvent &arg );
		bool OnKeyReleased( const OIS::KeyEvent &arg );
		bool OnWindowResized(Ogre::RenderWindow* rw);
		bool OnWindowClosed(Ogre::RenderWindow* rw);
		
		MyGUI::StaticImagePtr addMainMenuItem(Ogre::String name, Ogre::Vector2 position);

	};


} //end namespace

#endif