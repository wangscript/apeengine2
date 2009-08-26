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

#ifndef _CITEM_H_
#define _CITEM_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	
	struct NebulaDllPrivate CItemDesc
	{
		CItemDesc()
		{

		}

		std::string name;
		
		unsigned int amount;
		Ogre::Real weight;
	};
	
	class NebulaDllPrivate CItem : public IGameComponent,
									 public IPickableItem
	{
	public:
		CItem();
		CItem(const CItemDesc&);
		~CItem();

		void update();
		void setup();

		CItemDesc& getDescription() {
			return mDesc;
		}

		void callLuaFunction(const std::string func );
		
		void OnItemMenuStartDrag();
		void OnItemMenuFinishDrag();

		void OnItemPick();
		void OnItemDrop();
		void OnItemInventoryActivate();

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;

		CItemDesc mDesc;
	};

} //end namespace

#endif
