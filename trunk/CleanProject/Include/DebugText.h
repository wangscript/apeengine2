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

#ifndef _DebugText_H
#define _DebugText_H

#include "EnginePrerequisites.h"

namespace Nebula {
	
	using namespace Ogre;
	using namespace std;

	class DebugText
	{

	public: 
		DebugText(SceneManager* sm,RenderWindow* window);
		~DebugText();

		void updateStats(Ogre::String text);
		void addText(String text);
		void printText();
		void toggleFPSWindow();

	protected:
		SceneManager* mSceneMgr;
		RenderWindow* mWindow;
		std::list<String>* mDebugLines;

		Overlay* mDebugOverlay;

	};

} //end namespace

#endif
