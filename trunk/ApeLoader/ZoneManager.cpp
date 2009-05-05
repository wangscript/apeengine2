#include "ZoneManager.h"

//ZoneManager* ZoneManager::ms_Singleton = 0;
template<> ZoneManager* Ogre::Singleton<ZoneManager>::ms_Singleton = 0;
ZoneManager* ZoneManager::getSingletonPtr(void)
{
	return ms_Singleton;
}
ZoneManager& ZoneManager::getSingleton(void)
{  
	//assert( ms_Singleton );
	return ( *ms_Singleton );  
}

ZoneManager::ZoneManager() : 	mPZSM(0),
								mObjMan(0),
								mOgre(0)
{

}

ZoneManager::~ZoneManager() {


}

void ZoneManager::initialize() {
	mObjMan = ObjectManager::getSingletonPtr();
	mOgre = OgreRender::getSingletonPtr();
}

void ZoneManager::updateObjectsToZones() {
	
	std::map<const std::string, GameObject*> gos;
	gos = mObjMan->getGOs();

	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = gos.begin(); iter != gos.end(); iter++) {

		GameObject* obj;
		obj = iter->second;

		CRender* mCRender = dynamic_cast<CRender*>(obj->getComponent("CRender"));
		CActor* mCActor = dynamic_cast<CActor*>(obj->getComponent("CActor"));
		CLight* mCLight = dynamic_cast<CLight*>(obj->getComponent("CLight"));

		if(mCActor && mCRender) {
			//if(!mCActor->isStatic()) {
				
				
				
				PCZSceneNode* n = (PCZSceneNode*)(mCActor->mPhysicsActor->mNode);
				
				n->setHomeZone(mPZSM->getZoneByName(mCRender->mParentZoneName));
				//mPZSM->_updateHomeZone(n,true);			
		}
		if(mCRender && mCLight) {
			PCZSceneNode* n = (PCZSceneNode*)mCRender->mNode;
			n->setHomeZone(mPZSM->getZoneByName(mCRender->mParentZoneName));
		}
	}
}

void ZoneManager::createZones() {
	
	mPZSM = (Ogre::PCZSceneManager*)mOgre->getSceneManager();
	//mPZSM->enableSky(true);
	mPZSM->setDisplaySceneNodes(false);
	mPZSM->showBoundingBoxes(false);

	std::map<const std::string, GameObject*> gos;
	gos = mObjMan->getGOs();

	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		CRoom *mCRoom;
		GameObject* obj;
		obj = iter->second;

		mCRoom = dynamic_cast<CRoom*>(obj->getComponent("CRoom"));
		if(mCRoom) {
			CRender* mCRenderParentRoom = dynamic_cast<CRender*>(obj->getComponent("CRender"));
			if(mCRenderParentRoom) {
				
				Ogre::String zoneType = "ZoneType_Default";
				Ogre::String zoneName = mCRenderParentRoom->getNodeName() + "_room1_zone";
				PCZone * newZone;
				newZone = mPZSM->createZone(zoneType, zoneName);
				Ogre::SceneNode* roomNode = mCRenderParentRoom->getNode();
				roomNode->showBoundingBox(false);
				newZone->setEnclosureNode((PCZSceneNode*)roomNode);
				
				mPZSM->addPCZSceneNode((PCZSceneNode*)mCRenderParentRoom->getNode(), newZone);
				mCRoom->mRoomZone = newZone;
				mCRoom->mZoneName = zoneName;
				mCRoom->mZoneType = zoneType;
					
				Ogre::LogManager::getSingleton().logMessage("##### Creating Zone " + zoneName);

			}		
		}
	}

	//std::map<const std::string, GameObject*>::iterator iter;
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		GameObject* obj;
		obj = iter->second;

		CPortal * mCPortal = dynamic_cast<CPortal*>(obj->getComponent("CPortal"));
		if(mCPortal) {
			//CPortal* mCPortal = dynamic_cast<CPortal*>(obj->getComponent("CPortal"));
			//if(mCPortal) {
			//}
			CRoom* mRoom1 = getRoom(mCPortal->mRoom1);
			CRoom* mRoom2 = getRoom(mCPortal->mRoom2);
			
			CRender* mCRenderPortal = dynamic_cast<CRender*>(obj->getComponent("CRender"));

			//if(mRoom1) {

				Ogre::String portalName = mCRenderPortal->getNodeName() + Ogre::String("_Portal");
				Portal * p = mPZSM->createPortal(portalName);
				
				Ogre::Real w = mCPortal->mWidth / 2;
				Ogre::Real h = mCPortal->mLength / 2;
				Ogre::Real z = 0; //mCPortal->mWidth / 2
				Vector3 portalPos = Vector3::ZERO;
				
				CPosition* mCPortalPos = dynamic_cast<CPosition*>(obj->getComponent("CPosition"));
				if(mCPortalPos) {
					portalPos = mCPortalPos->Position;
				}


				Ogre::Vector3 points[4];
				
				//or = quat;
				
				//Quaternion quat;
				//quat = or;
				//or = or * Vector3::UNIT_Z;

				//Ogre::Radian p = or.getPitch();
				//Vector3 localY = or * Vector3::NEGATIVE_UNIT_Z;
				//Quaternion quat = localY.getRotationTo(or * Vector3::UNIT_Z);
				//Quaternion f; // = (quat *  or);
				//f = Quaternion::IDENTITY;

				//f.w = sqrt(0.5):
				//f.x = 0;
				//f.y = 0;
				//f.z = sqrt(0.5);

				//quat = qu

				Ogre::Quaternion or = Ogre::Quaternion::IDENTITY;
				COrientation* mCPortalOrient = dynamic_cast<COrientation*>(obj->getComponent("COrientation"));
				if(mCPortalOrient) {
					or = mCPortalOrient->Orientation;
				}
				Quaternion q(Degree(90), Vector3::UNIT_X);
				or = or * q; // * Vector3::NEGATIVE_UNIT_Z
				
				
				if(mCRenderPortal->getNodeName() == "Portal04") {
					Vector3 t = or * Vector3::NEGATIVE_UNIT_Z;
					
					Ogre::Vector3 scale = Vector3(1.0,1.0,1.0);
					Ogre::String name;
					name = "sp1" + Ogre::StringConverter::toString( ObjectManager::getSingleton().getNextCompIndex() );
					Ogre::Entity* mEnt1 = mOgre->getSceneManager()->createEntity(name,"arrow.mesh");
					Ogre::SceneNode* sn1 = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(name + "node",points[0]);
					sn1->attachObject(mEnt1);
					sn1->setPosition(t);
					//sn1->setScale(0.03,0.03,0.03);
					sn1->setScale(scale);
					//sn1->setOrientation(or);

					Ogre::LogManager::getSingleton().logMessage("##### Portal: " + mCRenderPortal->getNodeName() + " - " +  "Direction: " + Ogre::StringConverter::toString(t) );
				}

				// * Vector3::NEGATIVE_UNIT_Z 
				points[0] = portalPos + ( (or) * Ogre::Vector3(-w, h, z));
				points[1] = portalPos + ( (or) * Ogre::Vector3(-w, -h, z));
				points[2] = portalPos + ( (or) * Ogre::Vector3(w, -h, z));
				points[3] = portalPos + ( (or) * Ogre::Vector3(w, h, z));
				

				/*
				points[0] = portalPos + ( (or) * Ogre::Vector3(-w, h, z) * Vector3::NEGATIVE_UNIT_Z );
				points[1] = portalPos + ( (or) * Ogre::Vector3(-w, -h, z) * Vector3::NEGATIVE_UNIT_Z );
				points[2] = portalPos + ( (or) * Ogre::Vector3(w, -h, z) * Vector3::NEGATIVE_UNIT_Z );
				points[3] = portalPos + ( (or) * Ogre::Vector3(w, h, z) * Vector3::NEGATIVE_UNIT_Z );
				*/

				/*
				Ogre::Vector3 scale = Vector3(1.0,1.0,1.0);
				Ogre::String name;
				name = "sp1" + Ogre::StringConverter::toString( ObjectManager::getSingleton().getNextCompIndex() );
				Ogre::Entity* mEnt1 = mOgre->getSceneManager()->createEntity(name,"arrow.mesh");
				Ogre::SceneNode* sn1 = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(name + "node",points[0]);
				sn1->attachObject(mEnt1);
				sn1->setPosition(points[0]);
				//sn1->setScale(0.03,0.03,0.03);
				sn1->setScale(scale);
				sn1->setOrientation(or);
				
				name = "sp1" + Ogre::StringConverter::toString( ObjectManager::getSingleton().getNextCompIndex() );
				Ogre::Entity* mEnt2 = mOgre->getSceneManager()->createEntity(name,"arrow.mesh");
				Ogre::SceneNode* sn2 = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(name + "node",points[1]);
				sn2->attachObject(mEnt2);
				sn2->setPosition(points[1]);
				sn2->setScale(scale);
				sn2->setOrientation(or);

				
				name = "sp1" + Ogre::StringConverter::toString( ObjectManager::getSingleton().getNextCompIndex() );
				Ogre::Entity* mEnt3 = mOgre->getSceneManager()->createEntity(name,"arrow.mesh");
				Ogre::SceneNode* sn3 = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(name + "Node",points[2]);
				sn3->attachObject(mEnt3);
				sn3->setPosition(points[2]);
				sn3->setScale(scale);
				sn3->setOrientation(or);

				name = "sp1" + Ogre::StringConverter::toString( ObjectManager::getSingleton().getNextCompIndex() );
				Ogre::Entity* mEnt4 = mOgre->getSceneManager()->createEntity(name,"arrow.mesh");
				Ogre::SceneNode* sn4 = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode(name + "node",points[3]);
				sn4->attachObject(mEnt4);
				sn4->setPosition(points[3]);
				sn4->setScale(scale);
				sn4->setOrientation(or);
				*/

				p->setCorners(points);
				// associate the portal with the roomnode
				

				if(mCPortal->mRoom2 != "defaultZone") {
					Ogre::SceneNode* roomNode = getRoomNode(mCPortal->mRoom1);
					p->setNode(roomNode);
				} else {
					Ogre::SceneNode* roomNode = OgreRender::getSingleton().getSceneManager()->getRootSceneNode();
					p->setNode(roomNode);
				}

				if(mRoom1)
					mRoom1->mRoomZone->_addPortal(p);
				else
					mPZSM->getDefaultZone()->_addPortal(p);

				
				// update derived values for the portal
				p->updateDerivedValues();

			//}
			//if(mRoom2) {
				//Ogre::String portalName = mRoom2->mName + Ogre::String("_Portal");
				portalName = mCRenderPortal->getNodeName() + Ogre::String("_Portal");
				p = mPZSM->createPortal(portalName);

				w = mCPortal->mWidth / 2;
				h = mCPortal->mLength / 2;
				z = 0; //mCPortal->mWidth / 2;

				//portalPos = Vector3::ZERO;
				//CRender* mCRenderPortal = dynamic_cast<CRender*>(obj->getComponent("CRender"));
				//CPosition* mCPortalPos = dynamic_cast<CPosition*>(obj->getComponent("CPosition"));
				//if(mCPortalPos) {
				//	portalPos = mCPortalPos->Position;
				//}
				

				//Ogre::Quaternion or = Ogre::Quaternion::IDENTITY;
				//COrientation* mCPortalOrient = dynamic_cast<COrientation*>(obj->getComponent("COrientation"));
				//if(mCPortalOrient) {
				//	or = mCPortalOrient->Orientation;
				//}
				//or.Inverse();

				//Ogre::Vector3 points[4];
				//or = or * Ogre::Vector3::NEGATIVE_UNIT_Z;
				

				
				//Vector3 localY = or * Vector3::NEGATIVE_UNIT_Z;
				//Quaternion quat;
				//quat = or;
				//or = or * quat;
				//Vector3 = or * Vector3::UNIT_Z;

				//Vector3 localY = or * Vector3::NEGATIVE_UNIT_Z;
				//Quaternion quat = localY.getRotationTo(or * Vector3::UNIT_Y);                        
				//or = quat;
				//Quaternion q(Degree(90), Vector3::UNIT_X);
				//or = or * q;

				//or = Ogre::Quaternion::IDENTITY;
				//or = mCPortalOrient->Orientation;
				//q = Quaternion(Degree(90), Vector3::UNIT_X);
				//or = or * q * Vector3::UNIT_Z;

				points[0] = portalPos + ( or * Ogre::Vector3(w, h, z));
				points[1] = portalPos + ( or * Ogre::Vector3(w, -h, z));
				points[2] = portalPos + ( or * Ogre::Vector3(-w, -h, z));
				points[3] = portalPos + ( or * Ogre::Vector3(-w, h, z));
				

				/*
				points[0] = (portalPos + Ogre::Vector3(w, h, z));
				points[1] = (portalPos + Ogre::Vector3(w, -h, z));
				points[2] = (portalPos + Ogre::Vector3(-w, -h, z));
				points[3] = (portalPos + Ogre::Vector3(-w, h, z));
				*/

				p->setCorners(points);
				// associate the portal with the roomnode
				
				if(mCPortal->mRoom2 != "defaultZone") {
					Ogre::SceneNode* roomNode = getRoomNode(mCPortal->mRoom2);
					p->setNode(roomNode);
				} else {
					Ogre::SceneNode* roomNode = OgreRender::getSingleton().getSceneManager()->getRootSceneNode();
					p->setNode(roomNode);
				}

				// add the portal to the zone

				if(mRoom2)
					mRoom2->mRoomZone->_addPortal(p);
				else
					mPZSM->getDefaultZone()->_addPortal(p);

				// update derived values for the portal
				p->updateDerivedValues();
				
				//Ogre::LogManager::getSingleton().logMessage("##### Creating Portal: " + mCRenderPortal->getNodeName() + " - " + mCPortal->mRoom1 + " - 2:" + mCPortal->mRoom2 );

			//}
			
		}
	}


	//OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->getChildIterator()

	//SceneNode::ChildNodeIterator it = OgreRender::getSingleton().getSceneManager()->getRootSceneNode()->getChildIterator();
	//Ogre::LogManager::getSingleton().logMessage("##### Root -" );
	//while(it.hasMoreElements())
	//{
		//Node* obj = it.getNext();
		//String type = obj->getMovableType();
		 
		//Ogre::LogManager::getSingleton().logMessage("##### Child -" + obj->getName() );
		/*
		if(type=="Entity")
		{
			Entity* ent = (Entity*) obj;
			int num = ent->getNumSubEntities();
			for(int i = 0; i < num; i++)
			{
				ent->getSubEntity(i)->setUseIdentityView(true);
			}
		}
		*/
	//} 


	mPZSM->connectPortalsToTargetZonesByLocation();
}



CRoom* ZoneManager::getRoom(Ogre::String roomName) {
	std::map<const std::string, GameObject*> gos;
	gos = mObjMan->getGOs();
	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		GameObject* obj;
		obj = iter->second;

		CRoom *mCRoom = dynamic_cast<CRoom*>(obj->getComponent("CRoom"));
		if(mCRoom) {
			if(mCRoom->mName == roomName) {
				return mCRoom;
			}
		}

	}

}
Ogre::SceneNode* ZoneManager::getRoomNode(Ogre::String roomName) {
	std::map<const std::string, GameObject*> gos;
	gos = mObjMan->getGOs();
	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		GameObject* obj;
		obj = iter->second;

		CRoom *mCRoom = dynamic_cast<CRoom*>(obj->getComponent("CRoom"));
		if(mCRoom) {
			if(mCRoom->mName == roomName) {
				CRender* mCRenderRoom = dynamic_cast<CRender*>(obj->getComponent("CRender"));
				if(mCRenderRoom) {
					return mCRenderRoom->getNode();
				}
			}
		}

	}

}
