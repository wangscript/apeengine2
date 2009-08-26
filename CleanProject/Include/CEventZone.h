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

#ifndef _CEVENT_ZONE_H_
#define _CEVENT_ZONE_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	
	struct NebulaDllPrivate CEventZoneDesc
	{
		CEventZoneDesc()
		{

		}

		std::string name;
		
	};
	
	class NebulaDllPrivate CEventZone : public IGameComponent
	{
	public:
		CEventZone();
		CEventZone(const CEventZoneDesc&);
		~CEventZone();

		void update();
		void setup();

		CEventZoneDesc& getDescription() {
			return mDesc;
		}

		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;

		CEventZoneDesc mDesc;
	};

} //end namespace

#endif
