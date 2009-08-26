#include "CInventory.h"

namespace Nebula {
	CInventory::CInventory()
	{
		mComponentID = "CInventory";
		
		mDesc.numberOfSlots = 10;

		mLastClickTime = 0;
	}

	CInventory::CInventory(const CInventoryDesc& desc) : IPickableItem()
	{
		mComponentID = "CInventory";
		mDesc = desc;
		
		mDesc.numberOfSlots = 10;
		mLastClickTime = 0;
	}

	CInventory::~CInventory()
	{

	}
	
	/*bool CInventory::toggleInventoryWindow() {
		mIsInventoryVisible = !mIsInventoryVisible;
		return mIsInventoryVisible;
	}*/

	void CInventory::create() {

		mToolTip = new ToolTip();
		mToolTip->hide();

		mItemBox = new ItemBoxWindow("ItemBoxV.layout");

		mItemBox->getItemBox()->eventStartDrag = MyGUI::newDelegate(this, &CInventory::notifyStartDrop);
		mItemBox->getItemBox()->eventRequestDrop = MyGUI::newDelegate(this, &CInventory::notifyRequestDrop);
		mItemBox->getItemBox()->eventDropResult = MyGUI::newDelegate(this, &CInventory::notifyEndDrop);
		mItemBox->getItemBox()->eventChangeDDState = newDelegate(this, &CInventory::notifyDropState);
		mItemBox->getItemBox()->eventNotifyItem = newDelegate(this, &CInventory::notifyNotifyItem);
		mItemBox->getItemBox()->eventToolTip = newDelegate(this, &CInventory::notifyToolTip);

		//mItemBox->getItemBox()->eventItemBoxDoubleClick = newDelegate(this, &CInventory::notifyMouseButtonDoubleClick);

	
		//mItemBox->getItemBox()->ev

		//mItemBox->getItemBox()->getItemBox()->eventMouseButtonDoubleClick = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);
		
		//mItemBox->getItemBox()->getItemBox()->eventMouseButtonClick = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);
		//mItemBox->getItemBox()->getItemBox()->eventMouseButtonReleased = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);

		//mItemBox->getItemBox()->getItemBox()->eventmo = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);
		//mItemBox->getItemBox()->getItemBox()->even

		//mItemBox->getItemBox()->getItemBox()->eventMouseButtonDoubleClick = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonClick);

		

		//mInventoryImage->eventMouseButtonDoubleClick = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);

		reset();

		//mItemBox->getItemBox()->addItem(new ItemData());
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item1", 5));
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item2", 5));
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item3", 5));
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item4", 5));
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item5", 5));
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item6", 5));
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item7", 5));
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item8", 5));
		//mItemBox->getItemBox()->addItem(new ItemData("info_Crystal_Clear_Item9", 5));




		//image->setPosition(0,0);
		//image->setAlign(Align::Bottom | Align::Left);

	}
	
	void CInventory::reset() {
		//mItemBox->getItemBox()->
		for(unsigned int i = 1; i <= mDesc.numberOfSlots; i++) {
			mItemBox->getItemBox()->addItem(new ItemData());
		}
	}

	void CInventory::hideInventoryImage() {
		
	}

	void CInventory::showInventoryImage() {
		
	}

	void CInventory::destroyInventoryImage() {

	}

	void CInventory::createInventoryImage(Vector2 imageSize,std::string resourceName) { //, WindowPosition align
		MyGUI::IntSize& view = MyGUI::Gui::getInstance().getViewSize();
		const MyGUI::IntSize size(imageSize.x, imageSize.y);

		mDesc.inventoryImageSize = imageSize;
		
		mInventoryImage = MyGUI::Gui::getInstance().createWidget<MyGUI::StaticImage>("StaticImage", MyGUI::IntCoord((view.width - size.width) / 2, (view.height - size.height) / 2, size.width, size.height), MyGUI::Align::Bottom, "Main");
		mInventoryImage->setItemResource(resourceName);
		mInventoryImage->setItemGroup("States");
		mInventoryImage->setItemName("Normal");

		//Vector2 widgetPosition = GuiManager::getSingleton().calculateWidgetPosition(imageSize,align);

		//Vector2 widgetPosition = GuiManager::getSingleton().calculateWidgetPosition(imageSize, align);
		mInventoryImage->setPosition(view.width - imageSize.x,view.height - imageSize.y);
		//mInventoryImage->setPosition(MyGUI::IntSize(widgetPosition.x,widgetPosition.y)); //view.width - imageSize.x,view.height - imageSize.y

		mDesc.inventoryItemResourceName = resourceName;

		mInventoryImage->eventMouseSetFocus = MyGUI::newDelegate(this,&CInventory::notifyMouseSetFocus);
		mInventoryImage->eventMouseLostFocus = MyGUI::newDelegate(this,&CInventory::notifyMouseLostFocus);
		mInventoryImage->eventMouseButtonPressed = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonClick);
		
		//mInventoryImage->eventMouseButtonDoubleClick = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);
		
		MyGUI::WidgetPtr window = mItemBox->getItemBox()->getItemBox()->getParent();
		while(window)
			if(window->getParent())
				window = window->getParent();
			else
				break;

		if(window) {
			//window->setVisible(!window->isVisible());
			//window->setPosition()

			MyGUI::IntSize& view = MyGUI::Gui::getInstance().getViewSize();
			const MyGUI::IntSize size(view.width - mInventoryImage->getSize().width , view.height / 4);

			window->setSize(size);

			window->setPosition(0,view.height - (view.height / 4) );
			
			window->setVisible(!window->isVisible());
		}

		//mItemBox->getItemBox()->
	}

	void CInventory::notifyMouseButtonDoubleClick(ItemData* item) { //MyGUI::WidgetPtr _sender ItemData *item

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyMouseButtonDoubleClick";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

	//}

	//void CInventory::notifyMouseButtonDoubleClick(MyGUI::WidgetPtr _sender) {
		if(mLastClickTime == 0) {
			mLastClickTime = OgreManager::getSingleton().getGlobalTime_Milliseconds();
			return;
		}

		if (OgreManager::getSingleton().getGlobalTime_Milliseconds() - mLastClickTime <= 30 ) {
			
			mLastClickTime = 0;

			//size_t index = mItemBox->getItemBox()->getItemBox()->getIndexSelected();

			//ItemData* item = *( (ItemBox*) (mItemBox->getItemBox()->getItemBox()) ) ->getItemDataAt(index);
			//ItemData * item = *((ItemBox*)_sender)->getItemDataAt<ItemData*>(index);
			
			if(item) {

				size_t index = mItemBox->getItemBox()->getItemBox()->getIndexSelected();
				ItemData *item = *(mItemBox->getItemBox()->getItemBox()->getItemDataAt<ItemData*>(index));

				GameObject* object = TaskManager::getSingleton().getGameObject(item->getOwnerObjectName());

				CWeapon* weapon = dynamic_cast<CWeapon*>(object->getComponent("CWeapon"));
				if(weapon) {
					weapon->OnWeaponInventoryActivate();
					
				} else {
					CItem* item = dynamic_cast<CItem*>(object->getComponent("CItem"));
					if(item) {
						item->OnItemInventoryActivate();
						
					}
				}
				

			}
		
		
		} else {
			mLastClickTime = 0;
		}

	}

	void CInventory::notifyMouseButtonClick(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id) {
		
		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyMouseButtonClick";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		MyGUI::WidgetPtr window = mItemBox->getItemBox()->getItemBox()->getParent();
		while(window)
			if(window->getParent())
				window = window->getParent();
			else
				break;

		if(window)
			window->setVisible(!window->isVisible());
		
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnInventoryClick"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),window->isVisible()); // this

		}
	}

	void CInventory::notifyMouseSetFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old) {

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyMouseSetFocus";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Active");
	}

	void CInventory::notifyMouseLostFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new) {

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyMouseLostFocus";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Normal");
	}

	void CInventory::notifyStartDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result)
	{
		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyStartDrop";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		if (_info.sender_index != MyGUI::ITEM_NONE) {
			ItemData * data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);
			
			//std::string imageName = data->getInfo()->getItemResourceImage();

			//data->geti
			
			//MyGUI::ResourceImageSetPtr risp = data->getImage();
			//risp->

			//_info.sender->

			//risp->

			//MyGUI::ItemBoxPtr sender = ((BaseItemBox<CellView>*)_sender)->getItemBox();
			//((BaseItemBox<CellView>*)_info.sender)->

			//	(BaseItemBox<CellView>)

			_result = !data->isEmpty();
		}
	}

	void CInventory::notifyRequestDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result)
	{
		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyRequestDrop";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////


		// не на айтем кидаем
		if (_info.receiver_index == MyGUI::ITEM_NONE) {
			_result = false;
			return;
		}

		// на себя и на тотже айтем
		if ((_info.sender == _info.receiver) && (_info.sender_index == _info.receiver_index)) {
			_result = false;
			return;
		}

		ItemData * sender_data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);
		ItemData * receiver_data = *((ItemBox*)_info.receiver)->getItemDataAt<ItemData*>(_info.receiver_index);

		_result = receiver_data->isEmpty() || receiver_data->compare(sender_data);
	}

	void CInventory::notifyEndDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool _result)
	{
		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyEndDrop";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		if (_result) {

			ItemData * sender_data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);
			ItemData * receiver_data = *((ItemBox*)_info.receiver)->getItemDataAt<ItemData*>(_info.receiver_index);

			receiver_data->add(sender_data);
			receiver_data->setOwnerObjectName(sender_data->getOwnerObjectName());
			sender_data->clear();

			((ItemBox*)_info.receiver)->setItemData(_info.receiver_index, receiver_data);
			((ItemBox*)_info.sender)->setItemData(_info.sender_index, sender_data);
		} else {
			if(MyGUI::InputManager::getInstance().isShiftPressed()) {
				ItemData * sender_data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);

				std::string objName = sender_data->getOwnerObjectName();
				GameObject* object = TaskManager::getSingleton().getGameObject(objName);

				if(object) {
					dropItem(object);
					removeItem(object);
				}

				sender_data->clear();

				CWeapon* weapon = dynamic_cast<CWeapon*>(object->getComponent("CWeapon"));
				if(weapon) {
					weapon->OnWeaponItemMenuFinishDrag();
				} else {
					CItem* item = dynamic_cast<CItem*>(object->getComponent("CItem"));
					if(item) {
						item->OnItemMenuFinishDrag();
					}
				}

			}

		}
		


	}
	
	void CInventory::dropItem(GameObject* object) {
		
		CCharacterAnimation* anim = static_cast<CCharacterAnimation*>(getOwnerObject()->getComponent("CCharacterAnimation"));
		if(anim) {
			if(anim->getBoneAttachedToObject(object) != "") {
				anim->detachItemFromBone(object);

			} else {
				CCharacterController* character = dynamic_cast<CCharacterController*>(getOwnerObject()->getComponent("CCharacterController"));
				if(character) {
					Ogre::Vector3 position = character->getCharacterPosOgre();

					CPhysicsActor *actor = dynamic_cast<CPhysicsActor*>(object->getComponent("CPhysicsActor"));
					CRender* render = dynamic_cast<CRender*>(object->getComponent("CRender"));

					if(render && actor) {
						
						render->getNode()->setPosition(position);

						Ogre::Quaternion orient = render->getNode()->_getDerivedOrientation();

						//render->getNode()->setOrientation( worldOrientation ); // * mOffsetItemOrientation boneOrient

						actor->getNxActor()->moveGlobalPosition( NxTools::convert(position) );
						actor->getNxActor()->moveGlobalOrientationQuat( NxTools::convert(orient) );

						actor->getNxActor()->clearBodyFlag(NX_BF_KINEMATIC);
					}

				}
			}
		}
		
		CWeapon* weapon = dynamic_cast<CWeapon*>(object->getComponent("CWeapon"));
		if(weapon) {
			weapon->OnWeaponDrop();
		} else {
			CItem* item = dynamic_cast<CItem*>(object->getComponent("CItem"));
			if(item) {
				item->OnItemDrop();
			}
		}

	}

	void CInventory::notifyNotifyItem(wraps::BaseLayout * _sender, const MyGUI::IBNotifyItemData & _info)
	{
		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyNotifyItem";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		if (_info.index != MyGUI::ITEM_NONE) {
			//if (_info.notify == MyGUI::NotifyItem::NOTIFY_MOUSE_RELEASED) {

			//_sender->
			//ItemData * sender_data = *((ItemBox*)_sender)->getItemDataAt<ItemData*>(_info.sender_index);

			size_t index = mItemBox->getItemBox()->getItemBox()->getIndexSelected();
			//ItemData* item = *( (ItemBox*) (mItemBox->getItemBox()->getItemBox()) ) ->getItemDataAt(index);
			ItemData *item = *(mItemBox->getItemBox()->getItemBox()->getItemDataAt<ItemData*>(index));

			//MyGUI::ItemBoxPtr sender = ((BaseItemBox<CellView>*)_sender)->getItemBox();
			//sender->setPosition(sender->getCoord());
			//sender->getItemIndexSelected

			notifyMouseButtonDoubleClick(item);

		}
		

		
	}

	void CInventory::notifyDropState(wraps::BaseLayout * _sender, MyGUI::DDItemState _state)
	{
		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyDropState";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		/*if (_state == MyGUI::DDItemState::Refuse) MyGUI::PointerManager::getInstance().setPointer("drop_refuse", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Accept) MyGUI::PointerManager::getInstance().setPointer("drop_accept", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Miss) MyGUI::PointerManager::getInstance().setPointer("drop", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Start) MyGUI::PointerManager::getInstance().setPointer("drop", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::End) MyGUI::PointerManager::getInstance().setDefaultPointer();*/
	}

	void CInventory::notifyToolTip(wraps::BaseLayout * _sender, const MyGUI::ToolTipInfo & _info, ItemData * _data)
	{

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CInventory - notifyToolTip";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		if (_info.type == MyGUI::ToolTipInfo::Show) {
			mToolTip->show(_data, _info.point);
		}
		else if (_info.type == MyGUI::ToolTipInfo::Hide) {
			mToolTip->hide();
		}
	}

	void CInventory::addItem(GameObject* object) {

		if(object) {
			std::string objectName = object->getID();
			if(!mItemList[objectName]) {
				
				CWeapon* weapon = static_cast<CWeapon*>(object->getComponent("CWeapon"));
				if(weapon) {
					mItemList[objectName] = static_cast<IPickableItem*>(weapon);

					ItemData* itemImage = new ItemData(object->getTemplateName(), 1,object->getID());

					size_t s = mItemBox->getItemBox()->getItemBox()->getItemCount();
					for(size_t i = 0; i < s;i++) {
						ItemData *data = *(mItemBox->getItemBox()->getItemBox()->getItemDataAt<ItemData*>(i));
						if(data->isEmpty()) {
							
							//Nebula::ResourceImageSetPtr imageptr = itemImage->getImage();
							 
							//imageptr->getImageIndex()
							//MyGUI::StaticImagePtr image = imageptr->castType<MyGUI::StaticImage>();

							//std::string tname = imageptr->getTypeName();

							//MyGUI::StaticImagePtr si = data->castType<MyGUI::StaticImage>();
							//si->eventMouseButtonDoubleClick = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);
							
							mItemBox->getItemBox()->getItemBox()->setItemData(i,itemImage);
							weapon->OnWeaponPick();
							break;
						}
					}
				
				} else {
					CItem* item = static_cast<CItem*>(object->getComponent("CItem"));
					if(item) {
						mItemList[objectName] = static_cast<IPickableItem*>(item);
						
						ItemData* itemImage = new ItemData(object->getTemplateName(), 1,object->getID());
						mItemBox->getItemBox()->addItem(itemImage);
						item->OnItemPick();
					}
				}
				
				
			}

		}

	}
	void CInventory::removeItem(GameObject* object) {
		//if(item)
		//	delete mItemList[item->getID()];
		if(object) {
			std::string objectName = object->getID();
			if(mItemList[objectName]) {
				//mItemList[objectName] = NULL;
				//mItemBox->getItemBox()->removeItem( mItemBox->getItemBox()-> 0);
				mItemList.erase(objectName); // = NULL;
			}
		}
	}

	void CInventory::update() {

	}

	void CInventory::setup() {
		create();
	}
	
	void CInventory::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
