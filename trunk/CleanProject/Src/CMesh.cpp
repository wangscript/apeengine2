#include "CMesh.h"

namespace Nebula {
	
	CMesh::CMesh()
	{
		mComponentID = "CMesh";

	}

	CMesh::CMesh(const CMeshDesc& desc)
	{
		mComponentID = "CMesh";
		mDesc = desc;
	}

	CMesh::~CMesh()
	{

	}

	Real CMesh::getDistanceToActor(CPhysicsActor* actor) {
		Vector3 actorPos = NxTools::convert(actor->getNxActor()->getGlobalPosition());
		Vector3 thisActorPos;
		
		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

		if(render)
			thisActorPos = render->getNode()->_getDerivedPosition();
		else
			return 0;

		return thisActorPos.distance(actorPos);
	}

	Real CMesh::getDistanceToCharacter(CCharacterController* character) {
		Vector3 characterPos = character->getCharacterPosOgre();
		Vector3 thisActorPos; // = NxTools::convert(this->getNxActor()->getGlobalPosition());

		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

		if(render)
			thisActorPos = render->getNode()->_getDerivedPosition();
		else
			return 0;

		return thisActorPos.distance(characterPos);
	}

	Real CMesh::getDistanceToTrigger(CPhysicsTrigger* trigger) {
		Vector3 triggerPos = NxTools::convert(trigger->getNxActor()->getGlobalPosition());
		Vector3 thisActorPos; // = NxTools::convert(this->getNxActor()->getGlobalPosition());

		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
		if(render)
			thisActorPos = render->getNode()->_getDerivedPosition();
		else
			return 0;

		return thisActorPos.distance(triggerPos);
	}

	bool CMesh::OnCharacterMouseMovedOverObject(CCharacterController* character, Ogre::Vector3 position) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMouseMovedOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position);
		}
		return true;
	}

	bool CMesh::OnCharacterMouseMovedEnterOverObject(CCharacterController* character, Ogre::Vector3 position) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMouseMovedEnterOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position);
		}
		return true;
	}

	bool CMesh::OnCharacterMouseMovedLeaveOverObject(CCharacterController* character, Ogre::Vector3 position) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMouseMovedLeaveOverObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position);
		}
		return true;
	}

	bool CMesh::OnCharacterMousePressedObject(CCharacterController* character, Ogre::Vector3 position, int mouseButton) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMousePressedObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position, mouseButton);
		}
		return true;
	}

	bool CMesh::OnCharacterMouseReleasedObject(CCharacterController* character, Ogre::Vector3 position, int mouseButton) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState["OnCharacterMouseReleasedObject"];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject(), character->getOwnerObject(), position, mouseButton);
		}
		return true;
	}

	void CMesh::update() {

	}

	void CMesh::setup() {
		
		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

		std::string entName = getName();
		std::string fileName = getMeshFileName();
		mEntity = OgreManager::getSingleton().getSceneManager()->createEntity(entName,fileName);
		
		mEntity->setUserAny(Ogre::Any(getOwnerObject()));

		//mEntity->setMaterialName("empty_material");
		updateMaterial();

		if(render) {

			mOffsetNode = render->getNode()->createChildSceneNode(mDesc.name);
			mOffsetNode->attachObject(mEntity);
			
			//render->getNode()->attachObject(mEntity);

		}

		//	
		//	CPosition *pos = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
		//	COrientation *orient = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));
		//	//CMesh *mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));

		//	render->getNode()->setPosition(static_cast<Vector3>(*pos));
		//	render->getNode()->setOrientation(static_cast<Quaternion>(*orient));

		//}
		
	}

	void CMesh::setMeshAmbientColour(Ogre::ColourValue colourValue) {
		
		unsigned int nbSubEnt = mEntity->getNumSubEntities();
		for(unsigned int i = 0;i < nbSubEnt;i++) {

			MaterialPtr mat = mEntity->getSubEntity(i)->getMaterial();

			 mEntity->getSubEntity(i)->getMaterial()->getTechnique(0)->getPass(0)->setAmbient(colourValue);

			Ogre::GpuProgramParametersSharedPtr gpup;

			Ogre::String name = mat->getTechnique(0)->getPass(0)->getVertexProgramName();
			if(name == "ambient_vs") {
				gpup = mat->getTechnique(0)->getPass(0)->getVertexProgramParameters();
				gpup->setNamedConstant("ambient", colourValue);
			}
		}
	}

					//

				//GpuConstantDefinition gpucon = gpup->getConstantDefinition("ambient");

				//gpup->setNamedConstant("ambient", Ogre::Vector4(colourValue.r,colourValue.g,colourValue.b,colourValue.a) );
				//gpup->setNamedConstant("scaleU", Ogre::StringConverter::parseReal(mDesc.textureTileU) );
				//gpup->setNamedConstant("scaleV", Ogre::StringConverter::parseReal(mDesc.textureTileV) );
				//mat->getTechnique(0)->getPass(0)->setVertexProgramParameters(gpup);

				//mat->getTechnique(0)->getPass(0)->getVertexProgram()
				//size_t s = gpup->get getNumAutoConstantDefinitions();
				//mat->getTechnique(0)->getPass(0)->setAmbient(colourValue);
				//mat->getTechnique(0)->getPass(0)->
				//mat->getTechnique(0)->getPass(0)->getfra
				//mat->setna

	void CMesh::updateMaterial() {

		try {

			unsigned int nbSubEnt = mEntity->getNumSubEntities();
			for(unsigned int i = 0;i < nbSubEnt;i++) {

				Ogre::String tex1 = mDesc.textureFileName;
				if(tex1 != "") {

					if(OgreManager::getSingleton().isDepthShadowMapping()) {
						MaterialPtr material;

						material = Ogre::MaterialManager::getSingleton().getByName("Ogre/DepthShadowmap/Receiver/RockWall");
						//material = Ogre::MaterialManager::getSingleton().getByName("Ogre/DepthShadowmap/Receiver/Athene");
						MaterialPtr mat = material->clone(getOwnerObject()->getID() + "_Material");

						Ogre::String meshName = getOwnerObject()->getID() + ".tga";
						//mat->getTechnique(0)->getPass(2)->getTextureUnitState(0)->setTextureName(meshName);

						Ogre::String normal = tex1.substr(0,tex1.length()-4);
						Ogre::String ext = tex1.substr(tex1.length()-3,3);

						Ogre::String textDest;
						textDest = normal + "_n." + ext;
						//mat->getTechnique(0)->getPass(1)->getTextureUnitState(0)->setTextureName(textDest);
						
						mat->getTechnique(0)->getPass(2)->getTextureUnitState(0)->setTextureName(tex1);

						mEntity->getSubEntity(i)->setMaterial(mat);

					} else {

						MaterialPtr material;
						
						bool hasLightMap = true;

						//if(shadows) {
						//mDesc.actorParams.mGroupAsName
						CPhysicsActor* actor = dynamic_cast<CPhysicsActor*>(getOwnerObject()->getComponent("CPhysicsActor")); //->toActor();
						if(actor) {
							//if(actor->)
							//if(actor->getNxActor()->isDynamic())
							//	hasLightMap = true;
							//else
								hasLightMap = false;
						}

						if(hasLightMap) {
							material = Ogre::MaterialManager::getSingleton().getByName("ogre");
						} else {
							material = Ogre::MaterialManager::getSingleton().getByName("ogre_diff_only");
						}

						MaterialPtr mat = material->clone(getOwnerObject()->getID() + "_Material");

						Ogre::String tu1 = material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
						Ogre::String tu2 = material->getTechnique(0)->getPass(1)->getTextureUnitState(0)->getTextureName();
						Ogre::String tu3 = material->getTechnique(0)->getPass(1)->getTextureUnitState(2)->getTextureName();

						mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(tex1);
						mat->getTechnique(0)->getPass(1)->getTextureUnitState(0)->setTextureName(tex1);
						mat->getTechnique(0)->getPass(1)->getTextureUnitState(1)->setTextureName(tex1);

						Ogre::String meshName = getOwnerObject()->getID() + ".tga";
						
						if(hasLightMap)
							mat->getTechnique(0)->getPass(1)->getTextureUnitState(1)->setTextureName(meshName);

						Ogre::String normal = tex1.substr(0,tex1.length()-4);
						Ogre::String ext = tex1.substr(tex1.length()-3,3);

						Ogre::String textDest;
						textDest = normal + "_n." + ext;
						mat->getTechnique(0)->getPass(1)->getTextureUnitState(3)->setTextureName(textDest);

						Ogre::GpuProgramParametersSharedPtr gpup = mat->getTechnique(0)->getPass(1)->getVertexProgramParameters();

						gpup->setNamedConstant("scaleU", Ogre::StringConverter::parseReal(mDesc.textureTileU) );
						gpup->setNamedConstant("scaleV", Ogre::StringConverter::parseReal(mDesc.textureTileV) );

						mat->getTechnique(0)->getPass(1)->setVertexProgramParameters(gpup);

						mEntity->getSubEntity(i)->setMaterial(mat);
					}

				}
			}

		} catch (Ogre::Exception& e) {

		}

	}

	void CMesh::callLuaFunction(const std::string func ) {
		luabind::object componentState = getOwnerObject()->getTemplateObject();
		if(componentState) {
			luabind::object CallBack = componentState[func];
			if(CallBack)
				luabind::call_function<void>(CallBack,this->getOwnerObject()); // this
		}
	}

} //end namespace