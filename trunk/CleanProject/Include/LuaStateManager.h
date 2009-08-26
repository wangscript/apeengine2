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

#ifndef _LUA_STATE_MANAGER_H
#define _LUA_STATE_MANAGER_H

#include "EnginePrerequisites.h"

namespace Nebula
{
	using namespace luabind;
	
	class CCharacterController;
	class CRender;
	class CCharacterAnimation;
	class CAnimation;
	class CHealth;
	class CInventory;
	class CLight;
	class CMesh;
	class COrientation;
	class CPosition;
	class CRoom;
	class CWeapon;
	class CPhysicsActor;
	class CPhysicsTrigger;
	class CItem;
	class CDoor;
	class CElevator;
	class CEventZone;
	class CQuest;
	class CSwitch;
	class CHumanoid;
	class CSmallCreature;
	class CCamera;

	class NebulaDllPrivate LuaStateManager : public Ogre::Singleton<LuaStateManager>,
											 public ITask
	{
	private:
		lua_State* L;

		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();

		//Set Lua bindings

	public:

		LuaStateManager();
		virtual ~LuaStateManager();
		
		static LuaStateManager& getSingleton(void);
		static LuaStateManager* getSingletonPtr(void);
	
		void setBindings();
		lua_State* getState() const;
		int runFile( const char *fname );
		int runSource( const char *source );
		int errorHandler();
		void forceGarbageCollect();
		bool funcExist( lua_State* L, const char *name );


		CCharacterAnimation* getCharacterAnimationComponent(GameObject* obj);
		CCharacterController* getCharacterControllerComponent(GameObject* obj);
		CRender* getRenderComponent(GameObject* obj);
		CAnimation* getAnimationComponent(GameObject* obj);
		CHealth* getHealthComponent(GameObject* obj);
		CInventory* getInventoryComponent(GameObject* obj);
		CLight* getLightComponent(GameObject* obj);
		CMesh* getMeshComponent(GameObject* obj);
		COrientation* getOrientationComponent(GameObject* obj);
		CPosition* getPositionComponent(GameObject* obj);
		CRoom* getRoomComponent(GameObject* obj);
		CWeapon* getWeaponComponent(GameObject* obj);
		CPhysicsActor* getPhysicsActorComponent(GameObject* obj);
		CPhysicsTrigger* getPhysicsTriggerComponent(GameObject* obj);
		CItem* getItemComponent(GameObject* obj);
		CDoor* getDoorComponent(GameObject* obj);
		CElevator* getElevatorComponent(GameObject* obj);
		CEventZone* getEventZoneComponent(GameObject* obj);
		CQuest* getQuestComponent(GameObject* obj);
		CSwitch* getSwitchComponent(GameObject* obj);
		CHumanoid* getHumanoidComponent(GameObject* obj);
		CSmallCreature* getSmallCreatureComponent(GameObject* obj);
		CCamera* getCameraComponent(GameObject* obj);

		//CRender& getRender(GameObject& obj);

	};

}

#endif
