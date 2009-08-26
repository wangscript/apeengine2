#include "CSmallCreature.h"

namespace Nebula {
	CSmallCreature::CSmallCreature()
	{
		mComponentID = "CSmallCreature";
	}

	CSmallCreature::CSmallCreature(const CSmallCreatureDesc& desc) : IPickableItem()
	{
		mComponentID = "CSmallCreature";
		mDesc = desc;
	}

	CSmallCreature::~CSmallCreature()
	{

	}

	void CSmallCreature::notifyMouseButtonClick(MyGUI::WidgetPtr _sender, int _left, int _top, MyGUI::MouseButton _id) {
		
		MyGUI::WidgetPtr window = mCreatureBox->getItemBox()->getItemBox()->getParent();
		while(window)
			if(window->getParent())
				window = window->getParent();
			else
				break;

		if(window)
			window->setVisible(!window->isVisible());

		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCreatureIconClick"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(),window->isVisible()); // this

		}
	}

	void CSmallCreature::notifyMouseSetFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _old) {
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Active");
	}

	void CSmallCreature::notifyMouseLostFocus(MyGUI::WidgetPtr _sender, MyGUI::WidgetPtr _new) {
		MyGUI::StaticImagePtr image = _sender->castType<MyGUI::StaticImage>();
		image->setItemName("Normal");
	}

	void CSmallCreature::notifyStartDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result)
	{
		
		if (_info.sender_index != MyGUI::ITEM_NONE) {
			ItemData * data = *((ItemBox*)_info.sender)->getItemDataAt<ItemData*>(_info.sender_index);
			_result = !data->isEmpty();
		}
	}

	void CSmallCreature::notifyRequestDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool & _result)
	{
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

	void CSmallCreature::notifyEndDrop(wraps::BaseLayout * _sender, wraps::DDItemInfo _info, bool _result)
	{
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

	void CSmallCreature::update() {

	}

	void CSmallCreature::setup() {
		create();
	}
		
	void CSmallCreature::hideCreaturePaper() {
		
	}

	void CSmallCreature::showCreaturePaper() {

	}

	void CSmallCreature::createCreaturePaper(Vector2 imageSize,std::string resourceName) { //, WindowPosition align

		MyGUI::IntSize& view = MyGUI::Gui::getInstance().getViewSize();
		const MyGUI::IntSize size(imageSize.x, imageSize.y);

		//mDesc.inventoryImageSize = imageSize;
		
		mCreatureImage = MyGUI::Gui::getInstance().createWidget<MyGUI::StaticImage>("StaticImage", MyGUI::IntCoord((view.width - size.width) / 2, (view.height - size.height) / 2, size.width, size.height), MyGUI::Align::Bottom, "Main");
		mCreatureImage->setItemResource(resourceName);
		mCreatureImage->setItemGroup("States");
		mCreatureImage->setItemName("Normal");

		mCreatureImage->setPosition(view.width - imageSize.x,view.height - imageSize.y);

		//mDesc.inventoryItemResourceName = resourceName;

		mCreatureImage->eventMouseSetFocus = MyGUI::newDelegate(this,&CSmallCreature::notifyMouseSetFocus);
		mCreatureImage->eventMouseLostFocus = MyGUI::newDelegate(this,&CSmallCreature::notifyMouseLostFocus);
		mCreatureImage->eventMouseButtonPressed = MyGUI::newDelegate(this,&CSmallCreature::notifyMouseButtonClick);
		
		//mInventoryImage->eventMouseButtonDoubleClick = MyGUI::newDelegate(this,&CInventory::notifyMouseButtonDoubleClick);
		
		MyGUI::WidgetPtr window = mCreatureBox->getItemBox()->getItemBox()->getParent();
		while(window)
			if(window->getParent())
				window = window->getParent();
			else
				break;

		if(window) {

			MyGUI::IntSize& view = MyGUI::Gui::getInstance().getViewSize();
			const MyGUI::IntSize size(view.width - mCreatureImage->getSize().width , view.height / 4);

			window->setSize(size);

			window->setPosition(0,view.height - (view.height / 4) );
			
			window->setVisible(!window->isVisible());
		}

	}

	void CSmallCreature::create() {
		
		mToolTip = new ToolTip();
		mToolTip->hide();

		mCreatureBox = new ItemBoxWindow("ItemBoxV.layout");

		mCreatureBox->getItemBox()->eventStartDrag = MyGUI::newDelegate(this, &CSmallCreature::notifyStartDrop);
		mCreatureBox->getItemBox()->eventRequestDrop = MyGUI::newDelegate(this, &CSmallCreature::notifyRequestDrop);
		mCreatureBox->getItemBox()->eventDropResult = MyGUI::newDelegate(this, &CSmallCreature::notifyEndDrop);
		mCreatureBox->getItemBox()->eventChangeDDState = newDelegate(this, &CSmallCreature::notifyDropState);
		mCreatureBox->getItemBox()->eventNotifyItem = newDelegate(this, &CSmallCreature::notifyNotifyItem);
		mCreatureBox->getItemBox()->eventToolTip = newDelegate(this, &CSmallCreature::notifyToolTip);
	}

	void CSmallCreature::destroyCreaturePaper() {

	}

	void CSmallCreature::notifyNotifyItem(wraps::BaseLayout * _sender, const MyGUI::IBNotifyItemData & _info)
	{
		if (_info.index != MyGUI::ITEM_NONE) {
			//if (_info.notify == MyGUI::NotifyItem::NOTIFY_MOUSE_RELEASED) {

			//_sender->
			//ItemData * sender_data = *((ItemBox*)_sender)->getItemDataAt<ItemData*>(_info.sender_index);

			size_t index = mCreatureBox->getItemBox()->getItemBox()->getIndexSelected();
			//ItemData* item = *( (ItemBox*) (mItemBox->getItemBox()->getItemBox()) ) ->getItemDataAt(index);
			ItemData *item = *(mCreatureBox->getItemBox()->getItemBox()->getItemDataAt<ItemData*>(index));

			//MyGUI::ItemBoxPtr sender = ((BaseItemBox<CellView>*)_sender)->getItemBox();
			//sender->setPosition(sender->getCoord());
			//sender->getItemIndexSelected

			//notifyMouseButtonDoubleClick(item);

		}
		

		
	}

	void CSmallCreature::notifyDropState(wraps::BaseLayout * _sender, MyGUI::DDItemState _state)
	{
		/*if (_state == MyGUI::DDItemState::Refuse) MyGUI::PointerManager::getInstance().setPointer("drop_refuse", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Accept) MyGUI::PointerManager::getInstance().setPointer("drop_accept", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Miss) MyGUI::PointerManager::getInstance().setPointer("drop", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::Start) MyGUI::PointerManager::getInstance().setPointer("drop", _sender->mainWidget());
		else if (_state == MyGUI::DDItemState::End) MyGUI::PointerManager::getInstance().setDefaultPointer();*/
	}

	void CSmallCreature::notifyToolTip(wraps::BaseLayout * _sender, const MyGUI::ToolTipInfo & _info, ItemData * _data)
	{
		if (_info.type == MyGUI::ToolTipInfo::Show) {
			mToolTip->show(_data, _info.point);
		}
		else if (_info.type == MyGUI::ToolTipInfo::Hide) {
			mToolTip->hide();
		}
	}

	void CSmallCreature::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
