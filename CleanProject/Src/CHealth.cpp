#include "CHealth.h"

namespace Nebula {
	CHealth::CHealth()
	{
		mComponentID = "CHealth";
		mDesc.maxHitPoints = 5;
		mDesc.currentHitPoints = 5;
	}

	CHealth::CHealth(const CHealthDesc& desc)
	{
		mComponentID = "CHealth";
		mDesc = desc;

		mDesc.maxHitPoints = 5;
		mDesc.currentHitPoints = 5;
	}

	CHealth::~CHealth()
	{

	}

	void CHealth::update() {

	}

	void CHealth::setup() {
		
	}

	void CHealth::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

	void CHealth::setMaxHitPoints(Ogre::Real points) {
		mDesc.maxHitPoints = points;
		refreshHealthBar();
	}

	Ogre::Real CHealth::getMaxHitPoints() {
		return mDesc.maxHitPoints;
		refreshHealthBar();
	}

	void CHealth::setCurrentHitPoints(Ogre::Real points) {
		mDesc.currentHitPoints = points;
		refreshHealthBar();
	}

	Ogre::Real CHealth::getCurrentHitPoints() {
		return mDesc.currentHitPoints;
		refreshHealthBar();
	}

	void CHealth::removeHitPoint() {
		mDesc.currentHitPoints--;
		refreshHealthBar();
	}

	void CHealth::addHitPoint() {
		mDesc.currentHitPoints++;
		refreshHealthBar();
	}
	
	void CHealth::addHitPoints(Ogre::Real points) {
		mDesc.currentHitPoints += points;
		refreshHealthBar();
	}

	void CHealth::refreshHealthBar() {
		if(!mHealthBar.empty()) {
			//refresh

		}
	}

	void CHealth::createHealthBar(Vector2 imageSize,std::string resourceName) {
		MyGUI::IntSize& view = MyGUI::Gui::getInstance().getViewSize();
		const MyGUI::IntSize size(imageSize.x, imageSize.y);

		mDesc.healthImageSize = imageSize;
		mDesc.healthResourceName = resourceName;

		//MyGUI::StaticImagePtr healthImage = MyGUI::Gui::getInstance().createWidget<MyGUI::StaticImage>("StaticImage", MyGUI::IntCoord((view.width - size.width) / 2, (view.height - size.height) / 2, size.width, size.height), MyGUI::Align::Bottom, "Main");
		for(int i = 0; i < mDesc.maxHitPoints; i++ ) {
			MyGUI::StaticImagePtr healthImage = MyGUI::Gui::getInstance().createWidget<MyGUI::StaticImage>("StaticImage", 0, 0, size.width, size.height, MyGUI::Align::Top, "Main");
			healthImage->setItemResource(resourceName);
			healthImage->setItemGroup("States");
			healthImage->setItemName("Normal");
			healthImage->setPosition((i * imageSize.x),0);
			//healthImage->setPosition((i * imageSize.x),0);

			mHealthBar.push_back(healthImage);
		}

	}


} //end namespace
