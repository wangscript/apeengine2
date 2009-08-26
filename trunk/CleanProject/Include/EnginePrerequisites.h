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

#ifndef NEBULA_ENGINE_H_INCLUDED
#define NEBULA_ENGINE_H_INCLUDED

#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma warning (disable : 4267)

//////////////////////////////////////////////////////////////////////////
// Dependencies
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <list>
#include <string>
#include <map>
#include <deque>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#include <cassert>
#include <assert.h>
#include <sstream>
#include <cmath>
#include <ctime>

#ifdef WIN32
#include <windows.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <iostream>
#include <tchar.h>

//////////////////////////////////////////////////////////////////////////
// Boost
//////////////////////////////////////////////////////////////////////////
#include <boost/shared_ptr.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
//////////////////////////////////////////////////////////////////////////
// Lua and Luabind
//////////////////////////////////////////////////////////////////////////

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "luabind/luabind.hpp"

//////////////////////////////////////////////////////////////////////////
// Ogre
//////////////////////////////////////////////////////////////////////////
#include "Ogre.h"

//////////////////////////////////////////////////////////////////////////
// MOC (Minimal Ogre Collision)
//////////////////////////////////////////////////////////////////////////

#include "CollisionTools.h"

//////////////////////////////////////////////////////////////////////////
// XML Parser
//////////////////////////////////////////////////////////////////////////

#include "xmlParser.h"

//////////////////////////////////////////////////////////////////////////
// NVidia PhysX
//////////////////////////////////////////////////////////////////////////

#define NOMINMAX

#include "NxPhysics.h"
#include "NxConverter.h"
#include "NxUserAllocator.h"
#include "UserAllocator.h"
#include "ErrorStream.h"
#include "NxScene.h"
#include "NxControllerManager.h"
#include "NxController.h"
#include "NxBoxController.h"
#include "NxCapsuleController.h"
#include "NxCooking.h"
#include "NxStream.h"
#include "cooking.h"

#include "FileResource.h"

//////////////////////////////////////////////////////////////////////////
// OIS
//////////////////////////////////////////////////////////////////////////

#include "OIS/OISEvents.h"
#include "OIS/OISInputManager.h"
#include "OIS/OISMouse.h"
#include "OIS/OISKeyboard.h"
#include "OIS/OISJoystick.h"

//////////////////////////////////////////////////////////////////////////
// MyGUI
//////////////////////////////////////////////////////////////////////////

#include <MyGUI.h>
#include "BaseLayout.h"
#include "Console.h"

//#include "ResourceItemInfo.h"
//#include "CellView.h"
//#include "ItemBox.h"
//#include "Tooltip.h"
//#include "ItemBox/BaseItemBox.h"
//#include "ItemBoxWindow.h"
//#include "ItemData.h"

//////////////////////////////////////////////////////////////////////////
// irrKlang Sound library
//////////////////////////////////////////////////////////////////////////

#include "irrKlang.h"

//////////////////////////////////////////////////////////////////////////
// Ogre Max
//////////////////////////////////////////////////////////////////////////

#include "OgreMaxScene.hpp"

//////////////////////////////////////////////////////////////////////////
// Particle Universe
//////////////////////////////////////////////////////////////////////////

#include "ParticleUniverseSystem.h"
#include "ParticleUniverseSystemManager.h"

//////////////////////////////////////////////////////////////////////////
// TecnoFreak Animation System
//////////////////////////////////////////////////////////////////////////

#include <Ogre/AnimationSystem.h>
#include <TriggerFunctor.h>
#include <NodeFactory.h>

//////////////////////////////////////////////////////////////////////////
// Nebula Engine Files
//////////////////////////////////////////////////////////////////////////

#include "Common.h"
#include "resource.h"
#include "Events.h"
#include "ITask.h"
#include "IPickableItem.h"
#include "InputManager.h"
#include "IProfilerOutputHandler.h"
#include "IGameComponent.h"
#include "GameObject.h"
#include "LuaTriggerFunctor.h"
#include "log.h"
#include "profiler.h"
#include "profileloghandler.h"
#include "DebugText.h"
#include "WeaponTrail.h"

#include "OgreManager.h"
#include "GuiManager.h"
#include "TaskManager.h"
#include "PhysicsManager.h"
#include "OgreMaxManager.h"
#include "ParticleManager.h"
#include "TheoraVideoManager.h"
#include "TheoraVideoClip.h"
#include "VideoManager.h"
#include "SoundManager.h"

#include "CRender.h"
#include "CLight.h"
#include "CMesh.h"
#include "COrientation.h"
#include "CPosition.h"
#include "CLight.h"
#include "CRoom.h"
#include "CSimpleSound.h"
#include "CPhysicsActor.h"
#include "CPhysicsTrigger.h"
#include "CParticle.h"
#include "CCharacterController.h"
#include "CCharacterAnimation.h"
#include "CAnimation.h"
#include "CHealth.h"
#include "CInventory.h"
#include "CWeapon.h"
#include "CItem.h"
#include "CDoor.h"
#include "CElevator.h"
#include "CEventZone.h"
#include "CQuest.h"
#include "CSwitch.h"
#include "CHumanoid.h"
#include "CSmallCreature.h"
#include "CCamera.h"

#include "LuaStateManager.h"

using namespace Nebula;

//namespace Nebula {
//	class ITask;
//	class IPickableItem;
//	class IGameComponent;
//	class InputManager;
//	class GameObject;
//	class DebugText;
//	class OgreManager;
//	class GuiManager;
//	class TaskManager;
//	class PhysicsManager;
//	class OgreMaxManager;
//	class ParticleManager;
//	//class TheoraVideoManager;
//	class SoundManager;
//
//	class CRender;
//	class CLight;
//	class CMesh;
//	class COrientation;
//	class CPosition;
//	class CLight;
//	class CRoom;
//	class CSimpleSound;
//	class CPhysicsActor;
//	class CPhysicsTrigger;
//	class CParticle;
//	class CCharacterController;
//	class CCharacterAnimation;
//	class CAnimation;
//	class CHealth;
//	class CInventory;
//	class CWeapon;
//	class CItem;
//	class CDoor;
//	class CElevator;
//	class CEventZone;
//	class CQuest;
//	class CSwitch;
//	class CHumanoid;
//	class CSmallCreature;
//
//	class LuaStateManager;
//	
//}

#endif