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

#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

#include "EnginePrerequisites.h"

//#include "Common.h"
//#include "GameObject.h"
//#include <string>

namespace Nebula {

	class GameObject;

	class NebulaDllPrivate IGameComponent {
	public:

		IGameComponent() : mOwnerObj(0) {}
		virtual ~IGameComponent() = 0 {}

		virtual const std::string& componentID() const = 0;

		virtual void update() {}
		virtual void setup() {}

		void setOwnerObject( GameObject* obj) { 
			mOwnerObj = obj; 
		}
		
		GameObject* getOwnerObject() const { 
			return mOwnerObj; 
		}

	private:
		GameObject *mOwnerObj;
		

	};

} //end namespace

#endif
