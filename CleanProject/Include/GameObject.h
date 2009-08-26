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

#ifndef __GAME_OBJECT_HPP__
#define __GAME_OBJECT_HPP__

#include "EnginePrerequisites.h"

//#include "Common.h"
//#include "IGameComponent.h"
//#include <string>
//#include <list>
//
//#include <boost/serialization/list.hpp>
//#include <boost/serialization/string.hpp>
//#include <boost/serialization/nvp.hpp>


namespace Nebula {

	class IGameComponent;
	class GameObject;

	class NebulaDllPrivate GameObject {
	public:

		GameObject( const std::string& id) {
			setID(id);
			mTemplateName = "";
			//lua = 0;
		}
		GameObject( const std::string& id, const std::string& templateName) {
			setID(id);
			mTemplateName = templateName;
		}
		GameObject() {
			//setID(id);
		}

		const std::string& getID() const { 
			return mOID; 
		}
		
		void setID( const std::string& id ) { 
			mOID = id; 
		}
		
		const std::string& getTemplateName() const { 
			return mTemplateName; 
		}

		void setTemplateName( const std::string& templateName ) { 
			mTemplateName = templateName; 
		}
		
		IGameComponent* getComponent(const std::string& componentID ) {
			if(mComponents.empty())
				return NULL;

			std::list<IGameComponent*>::iterator it;
			for(it=mComponents.begin();it!=mComponents.end();it++)
			{
				IGameComponent* comp = (*it);
				if(comp->componentID() == componentID)
					return comp;
			}
			return NULL;

		}

		IGameComponent* setComponent(IGameComponent *newComp) {
			newComp->setOwnerObject(this);
			mComponents.push_back(newComp);
			return newComp;
		}

		void clearComponents() {
			//std::list<IGameComponent*>::iterator it;
			//for(it=mComponents.begin();it!=mComponents.end();it++)
			//{
			//	//delete it;
			//}
			mComponents.clear();
			callLuaFunction("OnComponentDestroy");
		}

		void update() {
			callLuaFunction("OnStartUpdate");
			std::list<IGameComponent*>::iterator it;
			for(it=mComponents.begin();it!=mComponents.end();it++)
			{
				(*it)->update();
			}
			callLuaFunction("OnFinishUpdate");
		}
		void setup() {
			callLuaFunction("OnComponentCreateStart");
			std::list<IGameComponent*>::iterator it;
			for(it=mComponents.begin();it!=mComponents.end();it++)
			{
				(*it)->setup();
			}

			//lua_State* lua = LuaStateManager::getSingleton().getState();
			std::string templateName = getTemplateName();
			luabind::object obj;
			if(templateName != "") {
				std::string file = "../Media/Scripts/" + getTemplateName() + ".lua";
				runFile(file.c_str());

				obj = luabind::globals(mLuaState)[templateName];
				//Set the template object as current state.
				setTemplateObject(obj);

				callLuaFunction("OnComponentCreateFinish");
			}
			
		}

		void callLuaFunction(const std::string func ) {
			luabind::object componentState = getTemplateObject();
			if(componentState) {
				luabind::object CallBack = componentState[func];
				if(CallBack)
					luabind::call_function<void>(CallBack,this); // this
			}
		}

		void setLuaState(lua_State* lua) {
			if(lua)
				mLuaState = lua;
		}

		void setTemplateObject(luabind::object newState) {
			mCurrentState = newState;
		}

		luabind::object getTemplateObject() {
			return mCurrentState;
		}

		//void setParent(GameObject* go) {
		//	mParent = go;
		//}
		//
		//void setChild(GameObject* go) {
		//	mChild = go;
		//}

	private:

		int runFile( const char *fname )
		{
			int ret;

			std::string msg;
			msg += "Lua - Loading File: ";
			msg += fname;

			//CLog::Get().Write(LOG_APP,msg.c_str());

			if( ret = luaL_loadfile(mLuaState, fname) || lua_pcall( mLuaState, 0 ,0 ,0 ))
				errorHandler();

			return ret;
		}
		int errorHandler()
		{
			luabind::object error_msg(luabind::from_stack(mLuaState, -1));
			std::stringstream ss; 

			ss << error_msg << std::endl;

			//CLog::Get().Write(LOG_USER,ss.str().c_str(),"");

			return 0;
		}

		std::string mOID;
		std::list<IGameComponent*> mComponents;
		//GameObject* mParent;
		//GameObject* mChild;
		std::string mTemplateName;
		
		lua_State* mLuaState;
		luabind::object mCurrentState;

		friend class boost::serialization::access;
		template<class archive>
		void serialize(archive& ar, const unsigned int version)
		{
			using boost::serialization::make_nvp;
			ar & make_nvp("OID", mOID);
			//ar & make_nvp("Cheese", m_cheese);
			//ar & make_nvp("Meats", m_meats);
			//ar & make_nvp("Add Spicy Eggplant", m_spicy_eggplant_p);

		}
		
	};

} //end namespace

#endif
