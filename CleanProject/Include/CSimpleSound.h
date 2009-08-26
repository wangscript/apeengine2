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

#ifndef _CSIMPLE_SOUND_H_
#define _CSIMPLE_SOUND_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	

	struct NebulaDllPrivate CSimpleSoundDesc
	{
		CSimpleSoundDesc()
		{

		}

		
	};
	
	class NebulaDllPrivate CSimpleSound : public IGameComponent {
	public:
		
		CSimpleSound(const CSimpleSoundDesc&);
		~CSimpleSound();

		void update();
		void setup();

		void callLuaFunction(const std::string func );

		CSimpleSoundDesc& getDescription() {
			return mDesc;
		}

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;

		CSimpleSoundDesc mDesc;
	};

} //end namespace

#endif

