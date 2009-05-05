#include "GameObject.h"
#include "ZoneManager.h"

#include "CRender.h"
#include "CLight.h"
#include "CMesh.h"
#include "CPosition.h"
#include "COrientation.h"
#include "CActor.h"
#include "CRoom.h"
#include "CPortal.h"
#include "CSound.h"
#include "CParticle.h"

//#include "CAI.h"

std::string CRender::mFamilyID = "CRender";
std::string CRender::mComponentID = "CRender";

GameComponent* CRender::makeComponent() {
	//CRender *comp = new CRender(this);
	return this;
}
// = ""
CRender::CRender(Ogre::String renderName,Ogre::String parentZoneName) : mObjMan(0),
																													  mOgre(0),
																													  mNode(0)

{
	mOgre = OgreRender::getSingletonPtr();
	mObjMan = ObjectManager::getSingletonPtr();
	
	if(parentZoneName == "" || parentZoneName == "undefined" || parentZoneName == "defaultZone")
		mParentZoneName = "ZoneType_Default";
	else
		mParentZoneName = parentZoneName;

	mRenderName = renderName;

	//mNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(mNodeName);

}
Ogre::String CRender::getNodeName() {
	return mRenderName;
}

CRender::~CRender()
{
	mNode->detachAllObjects(); // _deinitialise();
	delete mNode;
}

Ogre::SceneNode* CRender::getNode() {
	return mNode;
}
void CRender::setNode(Ogre::SceneNode* node) {
	mNode = node;
}

void CRender::setup() {
	CPosition *mCPosition = dynamic_cast<CPosition*>(getOwnerObject()->getComponent("CPosition"));
	COrientation *mCOrientation = dynamic_cast<COrientation*>(getOwnerObject()->getComponent("COrientation"));
	CMesh *mCMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	CLight *mCLight = dynamic_cast<CLight*>(getOwnerObject()->getComponent("CLight"));
	CActor *mCActor = dynamic_cast<CActor*>(getOwnerObject()->getComponent("CActor"));
	CRoom *mCRoom = dynamic_cast<CRoom*>(getOwnerObject()->getComponent("CRoom"));
	CCharacter *mCChar = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));
	CPortal *mCPortal = dynamic_cast<CPortal*>(getOwnerObject()->getComponent("CPortal"));
	CSound *mSound = dynamic_cast<CSound*>(getOwnerObject()->getComponent("CSound"));
	CParticle *mParticle = dynamic_cast<CParticle*>(getOwnerObject()->getComponent("CParticle"));

	if(mCChar) // || mCPortal
		return;

	if(mRenderName == "Sphere01")
		mRenderName = "table02";

	if(mCActor) {
		if(!mCActor->isStatic()) {
				return;
		}
	}

	if(mCRoom || mParentZoneName == "ZoneType_Default") { //Rooms are parent SceneNodes
		
		if(!mCRoom)
			mNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(mRenderName);
			
		if(mCLight) {
			mNode->attachObject(mCLight->mLight);

			if(mCPosition)
				mNode->setPosition(mCPosition->Position);

			if(mCOrientation)
				mNode->setOrientation(mCOrientation->Orientation);
				
			mNode->rotate(Quaternion(Degree(90), Ogre::Vector3::NEGATIVE_UNIT_X),Ogre::SceneNode::TransformSpace::TS_WORLD);

			return;
		}
		if(mParticle) {

			if(mCPosition)
				mNode->setPosition(mCPosition->Position);

			if(mCOrientation)
				mNode->setOrientation(mCOrientation->Orientation);

			return;
		}

		//if(mParticle


		if(!mCRoom && !mCPortal && mCMesh) {
			Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(getNodeName(),mCMesh->mMeshName);
			mCMesh->mEntity = ent;

			updateMaterial(ent, true);
			
			//ent->
			mNode->attachObject(ent);

			if(mCPosition)
				mNode->setPosition(mCPosition->Position);

			if(mCPosition)
				mNode->setOrientation(mCOrientation->Orientation);
			
		}
		return;
	}

	if(mCPortal)
		return;
	
	std::map<const std::string, GameObject*> gos;
	gos = mObjMan->getGOs();

	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		CRoom *mCRoom;
		GameObject* obj;
		obj = iter->second;

		mCRoom = dynamic_cast<CRoom*>(obj->getComponent("CRoom"));
		if(mCRoom) {
			
			CRender* mRoomRender = dynamic_cast<CRender*>(obj->getComponent("CRender"));
			
			Ogre::String roomNodeName = mRoomRender->getNodeName();
			if(roomNodeName == mParentZoneName) {

				if(mCLight) {
					
					//mNode = mRoomRender->getNode()->createChildSceneNode(mRenderName);
					
					//Default SceneNode
					mNode = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(mRenderName);

					mNode->attachObject(mCLight->mLight);
					if(mCPosition)
						mNode->setPosition(mCPosition->Position);

					if(mCPosition)
						mNode->setOrientation(mCOrientation->Orientation);
					return;
				}

				mNode = mRoomRender->getNode()->createChildSceneNode(mRenderName);

				if(mCMesh) {
					if(mCActor) {
						
						//mSound->setupSounds();

						if(!mCActor->isBody())
							return;
					}

					Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(getNodeName(),mCMesh->mMeshName);
					mCMesh->mEntity = ent;
					
					updateMaterial(ent);

					//ent->
					mNode->attachObject(ent);

				}

				if(mCPosition)
					mNode->setPosition(mCPosition->Position);

				if(mCPosition)
					mNode->setOrientation(mCOrientation->Orientation);

			}
		}
	}

}

void CRender::updateMaterial(Ogre::Entity* ent, bool shadows) {
	
	try {
		if(!ent)
			return;

		unsigned int nbSubEnt = ent->getNumSubEntities();
		for(unsigned int i = 0;i < nbSubEnt;i++) {
/*
			MaterialPtr origMaterial = ent->getSubEntity(i)->getMaterial();
			
			Ogre::String materialName = origMaterial->getName();

			unsigned short tech = origMaterial->getNumTechniques();
			if(tech == 0)
				return;
			
			unsigned short passes = origMaterial->getTechnique(0)->getNumPasses();
			if(passes == 0)
				return;

			unsigned short textUnits = origMaterial->getTechnique(0)->getPass(0)->getNumTextureUnitStates();
			if(textUnits == 0)
				return;
*/
			//if(this->mTextureFileName != "") {
				Ogre::String tex1 = this->mTextureFileName; // origMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
				if(tex1 != "") {
					//MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("ApeMaterial");

					//MaterialPtr originalMaterial = Ogre::MaterialManager::getSingleton().getByName("ApeMaterial");
					MaterialPtr material;
					if(shadows) {
						material = Ogre::MaterialManager::getSingleton().getByName("ogre");
					} else {
						material = Ogre::MaterialManager::getSingleton().getByName("ogre_diff_only");

					}
					
					//OgreRender::getSingleton().getSceneManager()->setShadowTextureSelfShadow(false);

					MaterialPtr mat = material->clone("ApeMaterial_" + mRenderName);

					//Ogre::String tn = material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
					Ogre::String tu1 = material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
					Ogre::String tu2 = material->getTechnique(0)->getPass(1)->getTextureUnitState(0)->getTextureName();
					Ogre::String tu3 = material->getTechnique(0)->getPass(1)->getTextureUnitState(2)->getTextureName();
					
					mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(tex1);
					mat->getTechnique(0)->getPass(1)->getTextureUnitState(0)->setTextureName(tex1);
					mat->getTechnique(0)->getPass(1)->getTextureUnitState(1)->setTextureName(tex1);
					
					//mat->getTechnique(0)->getPass(1)->getTextureUnitState(1)->setTextureName(tex1);
					//mat->setReceiveShadows(true);
					//ent->setCastShadows(false);

					//mat->getTechnique(0)->getPass(0)->getTextureUnitState(1)->setTextureName(tex1);
		
					//Ogre::String meshName = ent->getMesh()->getName() * ".lga";
					Ogre::String meshName = ent->getName() + ".tga";

					mat->getTechnique(0)->getPass(1)->getTextureUnitState(1)->setTextureName(meshName);

					Ogre::String normal = tex1.substr(0,tex1.length()-4);
					Ogre::String ext = tex1.substr(tex1.length()-3,3);

					Ogre::String textDest;
					textDest = normal + "_n." + ext;
					mat->getTechnique(0)->getPass(1)->getTextureUnitState(3)->setTextureName(textDest);

					//mat->set setParameter("scaleU",mTextureTiling_U);
					//mat->setParameter("scaleV",mTextureTiling_V);
					
					//mat->getTechnique(0)->getPass(1)->setVertexProgramParameters()
					Ogre::GpuProgramParametersSharedPtr gpup = mat->getTechnique(0)->getPass(1)->getVertexProgramParameters();
					
					gpup->setNamedConstant("scaleU", Ogre::StringConverter::parseReal(mTextureTiling_U) );
					gpup->setNamedConstant("scaleV", Ogre::StringConverter::parseReal(mTextureTiling_V) );

					mat->getTechnique(0)->getPass(1)->setVertexProgramParameters(gpup);

					ent->getSubEntity(i)->setMaterialName("ApeMaterial_" + mRenderName);
					
					//if(!shadows)
						//ent->setCastShadows(false);

					//ent->

					//CActor *mCActor = dynamic_cast<CActor*>(getOwnerObject()->getComponent("CActor"));
					//if(mCActor) {
					//	if(mCActor->isStatic())
					//		ent->setCastShadows(false);
					//}
				}
			//}
		}

	} catch (Ogre::Exception& e) {
		//Ogre::LogManager::getSingleton().logMessage("Entity " + mRenderName + " to zone " + roomNodeName);
	}

}

void CRender::update() {

}

