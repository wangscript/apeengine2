#include "CHumanoid.h"

namespace Nebula {
	CHumanoid::CHumanoid()
	{
		mComponentID = "CHumanoid";
	}

	CHumanoid::CHumanoid(const CHumanoidDesc& desc)
	{
		mComponentID = "CHumanoid";
		mDesc = desc;

	}

	CHumanoid::~CHumanoid()
	{

	}
	void CHumanoid::notifyMouseButtonClick(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id) {
		
		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyMouseButtonClick";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		MyGUI::WidgetPtr window = mCharacterBox->getItemBox()->getItemBox()->getParent();
		while(window) {
			if(window->getParent()) {
				window = window->getParent();
				window->setInheritsAlpha(false);
			}
			else {
				break;
			}
		}

		if(window) {
			window->setVisible(!window->isVisible());
			window->setAlpha(0.5);
		}
		
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterIconClick"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),window->isVisible()); // this

		}
	}

	void CHumanoid::notifyMouseSetFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old) {

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyMouseSetFocus";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Active");
	}

	void CHumanoid::notifyMouseLostFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new) {

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyMouseLostFocus";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Normal");
	}

	void CHumanoid::notifyStartDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result)
	{

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyStartDrop";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////
		
		if (_info.sender_index != MyGUI::ITEM_NONE) {
			ItemData * data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);
			_result = !data->isEmpty();
		}
	}

	void CHumanoid::notifyRequestDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result)
	{

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyRequestDrop";
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

	void CHumanoid::notifyEndDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool _result)
	{

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyEndDrop";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		if(!_sender) {
			_sender = NULL;
		}

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
					//dropItem(object);
					//removeItem(object);
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

	void CHumanoid::update() {

	}

	void CHumanoid::setup() {
		create();
	}
	
	void CHumanoid::createCharacterPaper(Vector2 imageSize,std::string resourceName) { //, WindowPosition align

		MyGUI::IntSize& view = MyGUI::Gui::getInstance().getViewSize();
		const MyGUI::IntSize size(imageSize.x, imageSize.y);

		//mDesc.inventoryImageSize = imageSize;
		
		mCharacterImage = MyGUI::Gui::getInstance().createWidget<MyGUI::StaticImage>("StaticImage", MyGUI::IntCoord((view.width - size.width) / 2, (view.height - size.height) / 2, size.width, size.height), MyGUI::Align::Bottom, "Main");
		mCharacterImage->setItemResource(resourceName);
		mCharacterImage->setItemGroup("States");
		mCharacterImage->setItemName("Normal");

		mCharacterImage->setPosition(view.width - imageSize.x,0);

		//mDesc.inventoryItemResourceName = resourceName;

		mCharacterImage->eventMouseSetFocus = MyGUI::newDelegate(this,&CHumanoid::notifyMouseSetFocus);
		mCharacterImage->eventMouseLostFocus = MyGUI::newDelegate(this,&CHumanoid::notifyMouseLostFocus);
		mCharacterImage->eventMouseButtonPressed = MyGUI::newDelegate(this,&CHumanoid::notifyMouseButtonClick);
		
		//mInventoryImage->eventMouseButtonDoubleClick = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);
		
		MyGUI::WidgetPtr window = mCharacterBox->getItemBox()->getItemBox()->getParent();
		while(window)
			if(window->getParent())
				window = window->getParent();
			else
				break;

		if(window) {

			MyGUI::IntSize& view = MyGUI::Gui::getInstance().getViewSize();
			const MyGUI::IntSize size(view.width - mCharacterImage->getSize().width , view.height / 4);

			//window->setSize(size);

			window->setPosition(view.width / 2, view.height / 2); //view.height - (view.height / 4)
			
			window->setVisible(!window->isVisible());
		}
	}

	void CHumanoid::hideCharacterPaper() {
		
	}

	void CHumanoid::showCharacterPaper() {

	}
	void CHumanoid::destroyCharacterPaper() {

	}

	void CHumanoid::notifyNotifyItem(wraps::BaseLayout * _sender, const MyGUI::IBNotifyItemData & _info)
	{

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyNotifyItem";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		if (_info.index != MyGUI::ITEM_NONE) {
			//if (_info.notify == MyGUI::NotifyItem::NOTIFY_MOUSE_RELEASED) {

			//_sender->
			//ItemData * sender_data = *((ItemBox*)_sender)->getItemDataAt<ItemData*>(_info.sender_index);

			//ItemBox* weapon = MyGUI::Gui::getInstance().findWidget<ItemBox*>("WeaponSlot");
			

			size_t index = mCharacterBox->getItemBox()->getItemBox()->getIndexSelected();
			//ItemData* item = *( (ItemBox*) (mItemBox->getItemBox()->getItemBox()) ) ->getItemDataAt(index);
			ItemData *item = *(mCharacterBox->getItemBox()->getItemBox()->getItemDataAt<ItemData*>(index));

			//MyGUI::ItemBoxPtr sender = ((BaseItemBox<CellView>*)_sender)->getItemBox();
			//sender->setPosition(sender->getCoord());
			//sender->getItemIndexSelected

			//notifyMouseButtonDoubleClick(item);

		}
		

		
	}

	void CHumanoid::notifyDropState(wraps::BaseLayout * _sender, MyGUI::DDItemState _state)
	{

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyDropState";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		/*if (_state == MyGUI::DDItemState::Refuse) MyGUI::PointerManager::getInstance().setPointer("drop_refuse", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Accept) MyGUI::PointerManager::getInstance().setPointer("drop_accept", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Miss) MyGUI::PointerManager::getInstance().setPointer("drop", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Start) MyGUI::PointerManager::getInstance().setPointer("drop", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::End) MyGUI::PointerManager::getInstance().setDefaultPointer();*/
	}

	void CHumanoid::notifyToolTip(wraps::BaseLayout * _sender, const MyGUI::ToolTipInfo & _info, ItemData * _data)
	{

		//////////////////////////////////////////////////////////////////
		std::string msg;
		msg += "CHumanoid - notifyToolTip";
		CLog::Get().Write(LOG_APP,msg.c_str());
		//////////////////////////////////////////////////////////////////

		if (_info.type == MyGUI::ToolTipInfo::Show) {
			mToolTip->show(_data, _info.point);
		}
		else if (_info.type == MyGUI::ToolTipInfo::Hide) {
			mToolTip->hide();
		}
	}

	void CHumanoid::create() {
		
		mToolTip = new ToolTip();
		mToolTip->hide();

		mCharacterBox = new ItemBoxWindow("CharacterBox.layout");

		//MyGUI::WidgetPtr wptr = mCharacterBox->getItemBox()->getItemBox()->findWidget("WeaponSlot");
		//MyGUI::ItemBox* wptr = *( (ItemBox*)( MyGUI::Gui::getInstance().findWidget<MyGUI::ItemBox*>("WeaponSlot") ) );
		//MyGUI::IntPoint wp = wptr->getPosition();

		//MyGUI::StaticImagePtr wp = MyGUI::Gui::getInstance().findWidget<MyGUI::StaticImage>("characterImage");
		
		//wraps::BaseLayout::
		
		//MyGUI::ItemBoxPtr ib = ((BaseItemBox<CellView>*) mCharacterBox->getItemBox()) ;
		//ib->findWidget
		
		
		mCharacterBox->getItemBox()->eventStartDrag = MyGUI::newDelegate(this, &CHumanoid::notifyStartDrop);
		mCharacterBox->getItemBox()->eventRequestDrop = MyGUI::newDelegate(this, &CHumanoid::notifyRequestDrop);
		mCharacterBox->getItemBox()->eventDropResult = MyGUI::newDelegate(this, &CHumanoid::notifyEndDrop);
		mCharacterBox->getItemBox()->eventChangeDDState = newDelegate(this, &CHumanoid::notifyDropState);
		mCharacterBox->getItemBox()->eventNotifyItem = newDelegate(this, &CHumanoid::notifyNotifyItem);
		mCharacterBox->getItemBox()->eventToolTip = newDelegate(this, &CHumanoid::notifyToolTip);
	}

	void CHumanoid::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
