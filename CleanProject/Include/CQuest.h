/*!
	@file
	@author		Pablo Nu�ez
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

#ifndef _CQUEST_H_
#define _CQUEST_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	
	struct NebulaDllPrivate CQuestDesc
	{
		CQuestDesc()
		{

		}

		std::string name;
		
	};
	
	class NebulaDllPrivate CQuest : public IGameComponent
	{
	public:
		CQuest();
		CQuest(const CQuestDesc&);
		~CQuest();

		void update();
		void setup();

		CQuestDesc& getDescription() {
			return mDesc;
		}

		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;

		CQuestDesc mDesc;
	};

} //end namespace

#endif
