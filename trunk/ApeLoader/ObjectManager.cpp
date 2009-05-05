#include "ApeManager.h"
#include "ObjectManager.h"
#include "CRender.h"
#include "CLight.h"
#include "CMesh.h"
#include "CPosition.h"
#include "COrientation.h"
#include "CCharacter.h"
#include "CPlayerInput.h"
#include "CCamera.h"
#include "CAnimation.h"
#include "CPortal.h"
#include "CRoom.h"
#include "CActor.h"
#include "Physics.h"
#include "DotSceneLoader.h"
#include "CSound.h"

//ObjectManager* ObjectManager::ms_Singleton = 0;

template<> ObjectManager* Ogre::Singleton<ObjectManager>::ms_Singleton = 0;
ObjectManager* ObjectManager::getSingletonPtr(void)
{
	return ms_Singleton;
}
ObjectManager& ObjectManager::getSingleton(void)
{  
	//assert( ms_Singleton );
	return ( *ms_Singleton );  
}


ObjectManager::ObjectManager() : mOgre(0),
							     mPhysics(0),
							     numComponents(0)
{
	clearGameObjects();
}

ObjectManager::~ObjectManager() { 
	clearGameObjects();
}

void ObjectManager::initialize() {
	mOgre = OgreRender::getSingletonPtr();
	mPhysics = Physics::getSingletonPtr();

}

//void ObjectManager::OnOgreRender_Created(OgreRender* ogre) {
//	mOgre = ogre;
//}

int ObjectManager::getNextCompIndex() {
	return numComponents++;
}

std::map<const std::string, GameObject*> ObjectManager::getGOs() { 
	return mGOs;
}

//Retrieve a Game Object
GameObject* ObjectManager::getGO(const std::string &id) {
	//return mGOs[id];
	
	std::map<const std::string, GameObject*>::iterator iter = mGOs.begin();
	iter = mGOs.find(id);
	if(iter != mGOs.end()) {
		return iter->second;
	}
	return NULL;
}
void ObjectManager::deleteGO(const std::string &id) {
	std::map<const std::string, GameObject*>::iterator iter = mGOs.begin();
	iter = mGOs.find(id);
	
	if(iter != mGOs.end()) {
		iter->second->clearComponents();
		mGOs.erase(iter);
	}
}

GameObject* ObjectManager::addObject(GameObject *go) {
	mGOs[go->getID()] = go;
	return mGOs[go->getID()];
}


void ObjectManager::clearGameObjects() {
	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = mGOs.begin(); iter != mGOs.end(); iter++) {
		iter->second->clearComponents();
	}
	mGOs.clear();
}

void ObjectManager::update() { 
	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = mGOs.begin(); iter != mGOs.end(); iter++) {
		iter->second->update();
	}
}

void ObjectManager::loadDotSceneFile(std::string file) {
	
	OgreMaxSceneCallbacks* mSceneCallbacks = new OgreMaxSceneCallbacks(Vector3(0,0,0));

	//OgreMax::OgreMaxScene::LoadOptions lo;
	

	OgreMaxScene* OMscene; // = NULL;
	OMscene = new OgreMax::OgreMaxScene ();
	OMscene->Load(file, OgreRender::getSingleton().getRoot()->getAutoCreatedWindow(),
		OgreMax::OgreMaxScene::NO_OPTIONS, NULL, NULL, mSceneCallbacks);

}

GameObject* ObjectManager::createCharacter(Ogre::String characterFileName) { 

	GameObject* go = new GameObject(characterFileName + "_GO");
	
	/*std::string mFilePath = "../../Media/Characters/" + characterFileName + ".xml";*/

	//mCurrentMapName = characterName;
	//GameSceneManager::getSingleton()->currentMapName

	//XMLNode xMainNode;

	//try {
	//	xMainNode=XMLNode::openFileHelper(mFilePath.c_str(),"ApeEngine"); //,"PMML"

	//} catch(...) {
	//	Ogre::LogManager::getSingleton().logMessage("*** Error loading character file ***");
	//	return false;
	//}
	//Ogre::Entity* ent = OgreRender::getSingleton().getSceneManager()->createEntity(mMeshName + "_entity",mMeshName);
	//ent->setCastShadows(true);

	//CMesh* mCMesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	//if(mCMesh) {
	//	mCMesh->mEntity = ent;
	//}

	CMesh* _CMesh = new CMesh("freddy.mesh","freddy"); //Ticket Collector.mesh
	CAnimation* _CAnim = new CAnimation("diagram.xml","animation_info.xml");
	CCharacter* _CCharacter = new CCharacter(characterFileName);
	CCamera* _CCamera = new CCamera(CCamera::VIEW_THIRD_PERSON_FREE);
	CPlayerInput* _CPlayerInput = new CPlayerInput();
	CRender* _CRender = new CRender("ninja");
	CSound* _CharSound = new CSound();
	//CPosition* _CPos = new CPosition(Vector3(1350.95,277.201,377.876));
	CPosition* _CPos = new CPosition(Vector3(0.0,0.0,0.0));

	COrientation* _COrient = new COrientation();

	go->setComponent(_CPlayerInput);
	go->setComponent(_CRender);
	
	go->setComponent(_CCharacter);
	go->setComponent(_CCamera);

	go->setComponent(_CAnim);
	go->setComponent(_COrient);
	go->setComponent(_CPos);
	go->setComponent(_CMesh);
	go->setComponent(_CharSound);

	_CCharacter->loadSettings();
	//_CAnim->loadSettings();
	_CAnim->loadXMLFiles();

	go->setup();

	addObject(go);

	mMainCharacter = go;

	return go;
}

void ObjectManager::addCustomGO() { //GameObject* go

	GameObject* character = createCharacter("CharacterExample");

	loadDotSceneFile("test.scene");

	//character->getComponent()
	CCharacter* mCChar = dynamic_cast<CCharacter*>(character->getComponent("CCharacter"));
	if(mCChar) {
		mCChar->setCurrentRoom("Level01_Room01");
	}
	CCamera* mCCam = dynamic_cast<CCamera*>(character->getComponent("CCamera"));
	if(mCCam) {
		mCCam->setCameraView(CCamera::CameraView::VIEW_THIRD_PERSON_SIDE); // setCurrentRoom("Level01_Room01");
	}

	//OgreRender::getSingleton().update();

	//ApeManager::getSingleton().loadApeMap("abcd");
	ApeManager::getSingleton().loadApeMap("a");
	//////////////////////////////////////////////////////////////////////////////////////

}
/*
void ObjectManager::addCustomGO(std::string objName, bool isMesh,bool isLight, Ogre::Light::LightTypes lightType, std::string meshFileName, float xPosition, float yPosition, float zPosition) {

	if(objName != "")
	{
		if(isMesh && meshFileName.c_str() == "") {
			return;
		}

		GameObject *GO = new GameObject(objName.c_str());

		CPosition *mPos = new CPosition();
		COrientation *mOr = new COrientation();
		CMesh *mMesh;

		if(isMesh) {
			mMesh = new CMesh(mOgre,this,meshFileName);
		} else {
			mMesh = new CMesh(mOgre,this,"arrow.mesh");
		}

		CRender *mMov = new CRender(mOgre,this);

		if(isLight) {
			CLight *mLight = new CLight(mOgre,this,lightType);
			GO->setComponent(mLight);
		}

		GO->setComponent(mPos);
		GO->setComponent(mOr);
		GO->setComponent(mMesh);
		GO->setComponent(mMov);
		GO->setup();
		addObject(GO);
	}
}
*/

bool ObjectManager::loadObjectsFromXML(XMLNode xMainNode) {

	XMLNode xNode=xMainNode.getChildNode("Objects");
	int n=xNode.nChildNode("Object");
	int i;
	int myIterator;
/*
		i = 0;
		myIterator=0;

		for (i=0; i<n; i++) {
		
			XMLNode xObjNode = xNode.getChildNode("Object",&myIterator);
			
			if(!xObjNode.getChildNode("CRoom").isEmpty()) {

				std::string objName = xObjNode.getAttribute("objName");

				CRender *mCRender;
				CPosition *mCPos;
				COrientation *mCOrient;
				CLight *mCLight;
				CMesh* mCMesh;
				CActor* mCActor;
				CRoom* mCRoom;
				CPortal* mCPortal;

				GameObject* go = new GameObject(objName);
				
				XMLNode xRoomNode = xObjNode.getChildNode("CRoom");

				Ogre::Vector3 roomSize = Ogre::StringConverter::parseVector3(xRoomNode.getAttribute("RoomSize"));
				Ogre::String roomName = xRoomNode.getAttribute("Name");
				mCRoom = new CRoom(roomSize,roomName);
				go->setComponent(mCRoom);

				if(!xObjNode.getChildNode("CRender").isEmpty()) {
					XMLNode xRenderNode = xObjNode.getChildNode("CRender");
					mCRender = new CRender();
					go->setComponent(mCRender);				
				}
				if(!xObjNode.getChildNode("CPortal").isEmpty()) {
					XMLNode xPortalNode = xObjNode.getChildNode("CPortal");

					Real length = Ogre::StringConverter::parseReal(xPortalNode.getAttribute("length"));
					Real width = Ogre::StringConverter::parseReal(xPortalNode.getAttribute("width"));
					Ogre::String room1 = xPortalNode.getAttribute("ParentRoom1");
					Ogre::String room2 = xPortalNode.getAttribute("ParentRoom2");
					mCPortal = new CPortal(length,width,room1,room2);
					go->setComponent(mCPortal);				
				}

				if(!xObjNode.getChildNode("CLight").isEmpty()) {
					mCLight = new CLight();

					XMLNode xLightNode = xObjNode.getChildNode("CLight");

					unsigned int lt = Ogre::StringConverter::parseUnsignedInt(xLightNode.getAttribute("Light_Type"));
					
					if(lt == Ogre::Light::LT_DIRECTIONAL) {
						mCLight->mLight->setType(Ogre::Light::LT_DIRECTIONAL);
					} else if (lt == Ogre::Light::LT_POINT) {
						mCLight->mLight->setType(Ogre::Light::LT_POINT);
					} else if(lt == Ogre::Light::LT_SPOTLIGHT) {
						mCLight->mLight->setType(Ogre::Light::LT_SPOTLIGHT);
						
						Real SpotInner = Ogre::StringConverter::parseReal(xLightNode.getAttribute("SpotLightRangeInner"));
						Real SpotOuter = Ogre::StringConverter::parseReal(xLightNode.getAttribute("SpotLightRangeOuter"));

						Ogre::Radian SpotInnerRad = (Ogre::Radian)Ogre::Math::AngleUnitsToRadians(SpotInner);
						Ogre::Radian SpotOuterRad = (Ogre::Radian)Ogre::Math::AngleUnitsToRadians(SpotOuter);

						mCLight->mLight->setSpotlightRange(SpotInnerRad,SpotOuterRad);
						

					} else {
						mCLight->mLight->setType(Ogre::Light::LT_POINT);
					}
					
					Real AttenuationRange = Ogre::StringConverter::parseReal(xLightNode.getAttribute("AttenuationRange"));
					Real AttenuationConstant = Ogre::StringConverter::parseReal(xLightNode.getAttribute("AttenuationConstant"));
					Real AttenuationLinear = Ogre::StringConverter::parseReal(xLightNode.getAttribute("AttenuationLinear"));
					Real AttenuationQuadratic = Ogre::StringConverter::parseReal(xLightNode.getAttribute("AttenuationQuadratic"));

					mCLight->mLight->setAttenuation(AttenuationRange,AttenuationConstant,AttenuationLinear,AttenuationQuadratic);

					ColourValue DiffColour = Ogre::StringConverter::parseColourValue(xLightNode.getAttribute("DiffuseColour"));
					ColourValue SpecColour = Ogre::StringConverter::parseColourValue(xLightNode.getAttribute("SpecularColour"));

					mCLight->mLight->setDiffuseColour(DiffColour);
					mCLight->mLight->setSpecularColour(SpecColour);

					
					go->setComponent(mCLight);

				}
				if(!xObjNode.getChildNode("CPosition").isEmpty()) {
					mCPos = new CPosition();
					XMLNode xPosNode = xObjNode.getChildNode("CPosition");

					mCPos->Position.x = Ogre::StringConverter::parseReal(xPosNode.getAttribute("x"));
					mCPos->Position.y = Ogre::StringConverter::parseReal(xPosNode.getAttribute("y"));
					mCPos->Position.z = Ogre::StringConverter::parseReal(xPosNode.getAttribute("z"));

					go->setComponent(mCPos);
					
				}
				if(!xObjNode.getChildNode("COrientation").isEmpty()) {
					mCOrient = new COrientation();
					XMLNode xOrientNode = xObjNode.getChildNode("COrientation");

					mCOrient->Orientation.w = Ogre::StringConverter::parseReal(xOrientNode.getAttribute("w"));
					mCOrient->Orientation.x = Ogre::StringConverter::parseReal(xOrientNode.getAttribute("x"));
					mCOrient->Orientation.y = Ogre::StringConverter::parseReal(xOrientNode.getAttribute("y"));
					mCOrient->Orientation.z = Ogre::StringConverter::parseReal(xOrientNode.getAttribute("z"));

					go->setComponent(mCOrient);
					
				}
				if(!xObjNode.getChildNode("CMesh").isEmpty()) {
					
					XMLNode xMeshNode = xObjNode.getChildNode("CMesh");
					std::string meshFileName = xMeshNode.getAttribute("meshFileName");
					
					mCMesh = new CMesh(meshFileName);
					
					
					go->setComponent(mCMesh);
					
				} else {
					mCMesh = new CMesh("arrow.mesh");
					go->setComponent(mCMesh);
				}
				
				if(!xObjNode.getChildNode("CPhysics").isEmpty()) {
					XMLNode xActorNode = xObjNode.getChildNode("CPhysics");

					Ogre::String mShapeType = xActorNode.getAttribute("ShapeType");
					Ogre::String mMeshFileName = xActorNode.getAttribute("MeshFileName");
					bool mIsDynamic = Ogre::StringConverter::parseBool(xActorNode.getAttribute("IsDynamic"));
					bool mIsBody = Ogre::StringConverter::parseBool(xActorNode.getAttribute("IsBody"));
					Real mMass = Ogre::StringConverter::parseReal(xActorNode.getAttribute("Mass"));
					Vector3 mShapeSize = Ogre::StringConverter::parseVector3(xActorNode.getAttribute("ShapeSize"));
					Ogre::String mName = xActorNode.getAttribute("Name");

					mCActor = new CActor(mShapeType,mMeshFileName,mIsDynamic,mIsBody,mMass,mShapeSize,mName);

					go->setComponent(mCActor);

				}

				go->setup();
				addObject(go);

			}

		}


		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//Child nodes
		i = 0;
		myIterator=0;
		for (i=0; i<n; i++) {

			XMLNode xObjNode = xNode.getChildNode("Object",&myIterator);

			if(xObjNode.getChildNode("CRoom").isEmpty()) {

				std::string objName = xObjNode.getAttribute("objName");

				CRender *mCRender;
				CPosition *mCPos;
				COrientation *mCOrient;
				CLight *mCLight;
				CMesh* mCMesh;
				CActor* mCActor;
				CRoom* mCRoom;
				CPortal* mCPortal;

				GameObject* go = new GameObject(objName);

				if(!xObjNode.getChildNode("CRoom").isEmpty()) {
					XMLNode xRoomNode = xObjNode.getChildNode("CRoom");

					Ogre::Vector3 roomSize = Ogre::StringConverter::parseVector3(xRoomNode.getAttribute("RoomSize"));
					Ogre::String roomName = xRoomNode.getAttribute("Name");
					mCRoom = new CRoom(roomSize,roomName);
					go->setComponent(mCRoom);
				}

				if(!xObjNode.getChildNode("CRender").isEmpty()) {
					XMLNode xRenderNode = xObjNode.getChildNode("CRender");
					bool isChild = Ogre::StringConverter::parseBool(xRenderNode.getAttribute("IsChild"));

					if(!xObjNode.getChildNode("CPhysics").isEmpty()) {
						bool isDynamic = Ogre::StringConverter::parseBool(xObjNode.getChildNode("CPhysics").getAttribute("IsDynamic"));
						if(isDynamic)
							isChild = false;
						else
							isChild = true;

					} else {
						isChild = false;
					}

					mCRender = new CRender("",isChild,xRenderNode.getAttribute("ParentName"));
					go->setComponent(mCRender);				
				}
				if(!xObjNode.getChildNode("CPortal").isEmpty()) {
					XMLNode xPortalNode = xObjNode.getChildNode("CPortal");

					Real length = Ogre::StringConverter::parseReal(xPortalNode.getAttribute("length"));
					Real width = Ogre::StringConverter::parseReal(xPortalNode.getAttribute("width"));
					Ogre::String room1 = xPortalNode.getAttribute("ParentRoom1");
					Ogre::String room2 = xPortalNode.getAttribute("ParentRoom2");
					mCPortal = new CPortal(length,width,room1,room2);
					go->setComponent(mCPortal);				
				}

				if(!xObjNode.getChildNode("CLight").isEmpty()) {
					mCLight = new CLight();

					XMLNode xLightNode = xObjNode.getChildNode("CLight");

					unsigned int lt = Ogre::StringConverter::parseUnsignedInt(xLightNode.getAttribute("Light_Type"));

					if(lt == Ogre::Light::LT_DIRECTIONAL) {
						mCLight->mLight->setType(Ogre::Light::LT_DIRECTIONAL);
					} else if (lt == Ogre::Light::LT_POINT) {
						mCLight->mLight->setType(Ogre::Light::LT_POINT);
					} else if(lt == Ogre::Light::LT_SPOTLIGHT) {
						mCLight->mLight->setType(Ogre::Light::LT_SPOTLIGHT);

						Real SpotInner = Ogre::StringConverter::parseReal(xLightNode.getAttribute("SpotLightRangeInner"));
						Real SpotOuter = Ogre::StringConverter::parseReal(xLightNode.getAttribute("SpotLightRangeOuter"));

						Ogre::Radian SpotInnerRad = (Ogre::Radian)Ogre::Math::AngleUnitsToRadians(SpotInner);
						Ogre::Radian SpotOuterRad = (Ogre::Radian)Ogre::Math::AngleUnitsToRadians(SpotOuter);

						mCLight->mLight->setSpotlightRange(SpotInnerRad,SpotOuterRad);


					} else {
						mCLight->mLight->setType(Ogre::Light::LT_POINT);
					}

					Real AttenuationRange = Ogre::StringConverter::parseReal(xLightNode.getAttribute("AttenuationRange"));
					Real AttenuationConstant = Ogre::StringConverter::parseReal(xLightNode.getAttribute("AttenuationConstant"));
					Real AttenuationLinear = Ogre::StringConverter::parseReal(xLightNode.getAttribute("AttenuationLinear"));
					Real AttenuationQuadratic = Ogre::StringConverter::parseReal(xLightNode.getAttribute("AttenuationQuadratic"));

					mCLight->mLight->setAttenuation(AttenuationRange,AttenuationConstant,AttenuationLinear,AttenuationQuadratic);

					ColourValue DiffColour = Ogre::StringConverter::parseColourValue(xLightNode.getAttribute("DiffuseColour"));
					ColourValue SpecColour = Ogre::StringConverter::parseColourValue(xLightNode.getAttribute("SpecularColour"));

					mCLight->mLight->setDiffuseColour(DiffColour);
					mCLight->mLight->setSpecularColour(SpecColour);


					go->setComponent(mCLight);

				}
				if(!xObjNode.getChildNode("CPosition").isEmpty()) {
					mCPos = new CPosition();
					XMLNode xPosNode = xObjNode.getChildNode("CPosition");

					mCPos->Position.x = Ogre::StringConverter::parseReal(xPosNode.getAttribute("x"));
					mCPos->Position.y = Ogre::StringConverter::parseReal(xPosNode.getAttribute("y"));
					mCPos->Position.z = Ogre::StringConverter::parseReal(xPosNode.getAttribute("z"));

					go->setComponent(mCPos);

				}
				if(!xObjNode.getChildNode("COrientation").isEmpty()) {
					mCOrient = new COrientation();
					XMLNode xOrientNode = xObjNode.getChildNode("COrientation");

					mCOrient->Orientation.w = Ogre::StringConverter::parseReal(xOrientNode.getAttribute("w"));
					mCOrient->Orientation.x = Ogre::StringConverter::parseReal(xOrientNode.getAttribute("x"));
					mCOrient->Orientation.y = Ogre::StringConverter::parseReal(xOrientNode.getAttribute("y"));
					mCOrient->Orientation.z = Ogre::StringConverter::parseReal(xOrientNode.getAttribute("z"));

					go->setComponent(mCOrient);

				}
				if(!xObjNode.getChildNode("CMesh").isEmpty()) {

					XMLNode xMeshNode = xObjNode.getChildNode("CMesh");
					std::string meshFileName = xMeshNode.getAttribute("meshFileName");

					mCMesh = new CMesh(meshFileName);


					go->setComponent(mCMesh);

				} else {
					mCMesh = new CMesh("arrow.mesh");
					go->setComponent(mCMesh);
				}

				if(!xObjNode.getChildNode("CPhysics").isEmpty()) {
					XMLNode xActorNode = xObjNode.getChildNode("CPhysics");

					Ogre::String mShapeType = xActorNode.getAttribute("ShapeType");
					Ogre::String mMeshFileName = xActorNode.getAttribute("MeshFileName");
					bool mIsDynamic = Ogre::StringConverter::parseBool(xActorNode.getAttribute("IsDynamic"));
					bool mIsBody = Ogre::StringConverter::parseBool(xActorNode.getAttribute("IsBody"));
					Real mMass = Ogre::StringConverter::parseReal(xActorNode.getAttribute("Mass"));
					Vector3 mShapeSize = Ogre::StringConverter::parseVector3(xActorNode.getAttribute("ShapeSize"));
					Ogre::String mName = xActorNode.getAttribute("Name");

					mCActor = new CActor(mShapeType,mMeshFileName,mIsDynamic,mIsBody,mMass,mShapeSize,mName);

					go->setComponent(mCActor);

				}

				go->setup();
				addObject(go);
			}
		}
*/
	return true;
}
