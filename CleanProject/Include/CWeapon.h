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

#ifndef _CWEAPON_H_
#define _CWEAPON_H_

#include "EnginePrerequisites.h"

namespace Nebula {

	using namespace Ogre;
	class IGameComponent;
	class WeaponTrail;

	struct NebulaDllPrivate CWeaponDesc
	{
		CWeaponDesc()
		{

		}

		int maxAmmo;
		int currentAmmo;
		bool isEmpty;
		bool isContinuousWeapon;
		int slotsPerClip;
		int numberOfClips;
		
		int amount;
	};
	
	class NebulaDllPrivate CWeapon : public IGameComponent,
									 public IPickableItem
	{
	public:
		CWeapon();
		CWeapon(const CWeaponDesc&);
		~CWeapon();

		void update();
		void setup();

		void OnWeaponPick();
		void OnWeaponDrop();
		void OnWeaponItemMenuStartDrag();
		void OnWeaponItemMenuFinishDrag();
		
		void OnWeaponInventoryActivate();
		
		Ogre::SceneNode* getRibbonTrailNodeTip();
		Ogre::SceneNode* getRibbonTrailNodeBase();

		void setRibbonTrailNodeTip(Ogre::SceneNode* node);
		void setRibbonTrailNodeBase(Ogre::SceneNode* node);

		void setRibbonTrailVisible(bool);
		void setRibbonTrailMaterial(std::string);

		void setRibbonTrailWidth(float width);

		void setSegmentStartInitialColor(const Ogre::ColourValue& p_Color);
		void setSegmentEndInitialColor(const Ogre::ColourValue& p_Color);
		void setSegmentStartColorChange(const Ogre::ColourValue& p_Color);
		void setSegmentEndColorChange(const Ogre::ColourValue& p_Color);

		CWeaponDesc& getDescription() {
			return mDesc;
		}
		
		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;

		WeaponTrail* mTrail;
		
		Ogre::SceneNode* mRibbonTrailNodeTip;
		Ogre::SceneNode* mRibbonTrailNodeBase;

		CWeaponDesc mDesc;
	};

} //end namespace

#endif
