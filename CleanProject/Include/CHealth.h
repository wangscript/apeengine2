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

#ifndef _CHEALTH_H_
#define _CHEALTH_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	
	struct NebulaDllPrivate CHealthDesc
	{
		CHealthDesc()
		{

		}

		Ogre::Real maxHitPoints;
		Ogre::Real currentHitPoints;

		Ogre::Vector2 healthImageSize;
		std::string healthResourceName;

		bool isPosoned;

	};
	
	class NebulaDllPrivate CHealth : public IGameComponent
	{
	public:
		CHealth();
		CHealth(const CHealthDesc&);
		~CHealth();

		void update();
		void setup();

		CHealthDesc& getDescription() {
			return mDesc;
		}

		void setMaxHitPoints(Ogre::Real);
		Ogre::Real getMaxHitPoints();

		void setCurrentHitPoints(Ogre::Real);
		Ogre::Real getCurrentHitPoints();

		void removeHitPoint();
		void addHitPoint();
		void addHitPoints(Ogre::Real points);

		void createHealthBar(Vector2 imageSize,std::string resourceName);
		void refreshHealthBar();

		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;

		std::vector<MyGUI::StaticImagePtr> mHealthBar;

		CHealthDesc mDesc;
	};

} //end namespace

#endif
