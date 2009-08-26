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

#ifndef _CINVENTORY_H_
#define _CINVENTORY_H_

#include "EnginePrerequisites.h"

#include "ItemBoxWindow.h"
#include "Tooltip.h"

namespace Nebula {

	using namespace Ogre;
	using namespace MyGUI;

	//class IGameComponent;
	//class IPickableItem;
	//class GameObject;
	class ToolTip;
	class ItemBoxWindow;

	//class GuiManager;
	//enum WindowPosition;

	struct NebulaDllPrivate CInventoryDesc
	{
		CInventoryDesc()
		{

		}

		unsigned int numberOfSlots;
		Ogre::Real maxWeightSupported;
		unsigned int numberOfItems;
		Ogre::Real totalWeight;

		Ogre::Vector2 inventoryImageSize;
		std::string inventoryItemResourceName;
	};
	
	class NebulaDllPrivate CInventory : public IGameComponent,
									   public IPickableItem
	{
	public:
		CInventory();
		CInventory(const CInventoryDesc&);
		~CInventory();

		void update();
		void setup();

		void notifyStartDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result);
		void notifyRequestDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result);
		void notifyEndDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool _result);
		void notifyNotifyItem(wraps::BaseLayout * _sender, const MyGUI::IBNotifyItemData & _info);
		void notifyDropState(wraps::BaseLayout * _sender, MyGUI::DDItemState _state);
		void notifyToolTip(wraps::BaseLayout * _sender, const MyGUI::ToolTipInfo & _info, ItemData * _data);

		void notifyMouseButtonClick(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id);
		void notifyMouseSetFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old);
		void notifyMouseLostFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new);

		void notifyMouseButtonDoubleClick(ItemData*); //MyGUI::WidgetPtr _sender

		void hideInventoryImage();
		void showInventoryImage();
		void createInventoryImage(Vector2 imageSize,std::string resourceName); //, WindowPosition align
		void destroyInventoryImage();

		void create();

		void addItem(GameObject* item) ;
		void removeItem(GameObject* item);
		void dropItem(GameObject*);
		void reset();

		CInventoryDesc& getDescription() {
			return mDesc;
		}
		
		void callLuaFunction(const std::string func );

		virtual const std::string& componentID() const { 
			return mComponentID; 
		}
	private:
		std::string mComponentID;
		ItemBoxWindow * mItemBox;
		ToolTip * mToolTip;

		MyGUI::StaticImagePtr mInventoryImage;

		//bool mIsInventoryVisible;

		std::map<std::string,IPickableItem*> mItemList;

		CInventoryDesc mDesc;

		Ogre::Real mLastClickTime;
	};

} //end namespace

#endif
