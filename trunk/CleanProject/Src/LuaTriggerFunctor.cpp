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

#ifndef _LuaTriggerFunctor_H_
#define _LuaTriggerFunctor_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace tecnofreak;
	using namespace tecnofreak::ogre;

	class NebulaDllPrivate LuaTriggerFunctor
		: public ITriggerSubscriber
	{
	public:
		LuaTriggerFunctor();
		virtual ~LuaTriggerFunctor();

		virtual void operator() ( const tecnofreak::ITrigger* trigger );

		void setLuaFunction( const luabind::object& luaFunction ) {
			mLuaFunction = luaFunction;
		};

		void notifyLua() {
			if(mLuaFunction)
				luabind::call_function<void>(mLuaFunction);
		}

	private:
		luabind::object mLuaFunction;
		std::string mTriggerName;
	};

} //end namespace

#endif