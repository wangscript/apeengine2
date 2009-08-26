#include "CWeapon.h"

namespace Nebula {
	CWeapon::CWeapon()
	{
		mComponentID = "CWeapon";
	}

	CWeapon::CWeapon(const CWeaponDesc& desc) : IPickableItem()
	{
		mComponentID = "CWeapon";
		mDesc = desc;

	}

	CWeapon::~CWeapon()
	{

	}

	void CWeapon::update() {
		
		Ogre::Real time = OgreManager::getSingleton().getTimeSinceLastFrame();

		if(mTrail)
			mTrail->onUpdate(time);

		CRender* render = static_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		if(render) {
			ParticleUniverse::ParticleSystem* ps = ParticleManager::getSingleton().getParticle("door1_particle");
			ParticleUniverse::ParticleTechnique* tech = ps->getTechnique(0);
			ParticleUniverse::ParticleEmitter* emiter = tech->getEmitter(0);
			emiter->setParticleDirection( OgreManager::getSingleton().getCamera()->getDirection() ); //render->getNode()->_getDerivedOrientation() * Vector3::UNIT_Z
			//tech->getAffector(0)->
			
				//ParticleUniverse::

			//emiter->get

			//	ParticleUniverse::ParticleEmitter::set
		}


	}
	
	Ogre::SceneNode* CWeapon::getRibbonTrailNodeTip() {
		return mRibbonTrailNodeTip;
	}

	Ogre::SceneNode* CWeapon::getRibbonTrailNodeBase() {
		return mRibbonTrailNodeBase;
	}

	void CWeapon::setRibbonTrailVisible(bool flag) {
		mTrail->setActive(flag);
	}

	void CWeapon::setRibbonTrailWidth(float width) {
		mTrail->setWidth(width);
	}

	void CWeapon::setRibbonTrailMaterial(std::string material) {
		//mTrail->
	}
	void CWeapon::setRibbonTrailNodeTip(Ogre::SceneNode* node) {
		//setRibbonTrailNodeTip(node);
		mTrail->setTrailBaseTip(node);
	}

	void CWeapon::setRibbonTrailNodeBase(Ogre::SceneNode* node) {
		//setRibbonTrailNodeBase(node);
		mTrail->setTrailBaseNode(node);
	}
	void CWeapon::setSegmentStartInitialColor(const Ogre::ColourValue& p_Color) {
		mTrail->setSegmentStartInitialColor(p_Color);
	}

	void CWeapon::setSegmentEndInitialColor(const Ogre::ColourValue& p_Color) {
		mTrail->setSegmentEndInitialColor(p_Color);
	}

	void CWeapon::setSegmentStartColorChange(const Ogre::ColourValue& p_Color) {
		mTrail->setSegmentStartColorChange(p_Color);
	}

	void CWeapon::setSegmentEndColorChange(const Ogre::ColourValue& p_Color) {
		mTrail->setSegmentEndColorChange(p_Color);
	}

	void CWeapon::setup() {
		std::string trailName = getOwnerObject()->getID();
		mTrail = new WeaponTrail(trailName);
		//mTrail = NULL;

		CMesh* mesh = static_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));

		if(mesh) {
			mTrail->setWeaponEntity(mesh->getEntity());
			mTrail->setActive(false);
		}

	}
	
	void CWeapon::OnWeaponInventoryActivate() {
		callLuaFunction("OnWeaponInventoryActivate");
	}

	void CWeapon::OnWeaponPick() {
		callLuaFunction("OnWeaponPick");
	}

	void CWeapon::OnWeaponDrop() {
		callLuaFunction("OnWeaponDrop");
	}

	void CWeapon::OnWeaponItemMenuStartDrag() {
		callLuaFunction("OnWeaponItemMenuStartDrag");
	}

	void CWeapon::OnWeaponItemMenuFinishDrag() {
		callLuaFunction("OnWeaponItemMenuFinishDrag");
	}

	void CWeapon::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace
