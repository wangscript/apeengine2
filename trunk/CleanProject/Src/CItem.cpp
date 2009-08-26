#include "CItem.h"

namespace Nebula {
	CItem::CItem()
	{
		mComponentID = "CItem";
	}

	CItem::CItem(const CItemDesc& desc) : IPickableItem()
	{
		mComponentID = "CItem";
		mDesc = desc;
	}

	CItem::~CItem()
	{

	}

	void CItem::update() {

	}

	void CItem::setup() {
		
	}
	
	void CItem::OnItemInventoryActivate() {

	}

	void CItem::OnItemPick() {
		callLuaFunction("OnItemPick");
	}

	void CItem::OnItemDrop() {
		callLuaFunction("OnItemDrop");
	}

	void CItem::OnItemMenuStartDrag() {
		callLuaFunction("OnItemMenuStartDrag");
	}

	void CItem::OnItemMenuFinishDrag() {
		callLuaFunction("OnItemMenuFinishDrag");
	}

	void CItem::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
