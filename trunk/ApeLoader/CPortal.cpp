#include "CPortal.h"


const std::string CPortal::mFamilyID = "CPortal";
const std::string CPortal::mComponentID = "CPortal";

CPortal::CPortal(Ogre::Real portalLength,Ogre::Real portalwidth,Ogre::String room1,Ogre::String room2)
{

	mLength = portalLength;
	mWidth = portalwidth;
	mRoom1 = room1;
	mRoom2 = room2;
	mObjMan = ObjectManager::getSingleton().getSingletonPtr();
	mOgre = OgreRender::getSingleton().getSingletonPtr();
}

CPortal::~CPortal()
{

}

void CPortal::update() {

}

void CPortal::setup() {
	/*
	mPCZSceneMgr = (Ogre::PCZSceneManager*) mOgre->getSceneManager();

	std::map<const std::string, GameObject*> gos;
	gos = mObjMan->getGOs();

	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = gos.begin(); iter != gos.end(); iter++) {
		CRoom *mCRoom;
		GameObject* obj;
		obj = iter->second;
		
		mCRoom = dynamic_cast<CRoom*>(obj->getComponent("CRoom"));
		if(mCRoom) {
			Ogre::Vector3 mRoom1Size1;
			Ogre::Vector3 mRoom1Size2;
			if(mCRoom->mName == mRoom1) {

			 	CRender* mCRenderRoom1 = dynamic_cast<CRender*>(obj->getComponent("CRender"));
				
				mRoom1Size1 = mCRoom->mRoomSize;
				if(mCRenderRoom1)
					mRoom1Node = (PCZSceneNode*)mCRenderRoom1->getNode();

			}
			if(mCRoom->mName == mRoom2) {
				
				CRender* mCRenderRoom2 = dynamic_cast<CRender*>(obj->getComponent("CRender"));

				mRoom1Size2 = mCRoom->mRoomSize;

				if(mCRenderRoom2)
					mRoom2Node = (PCZSceneNode*)mCRenderRoom2->getNode();

			}
		}
	}
	*/

/*
	PCZSceneNode* mRoom1Node;
	PCZSceneNode* mRoom2Node;

	Ogre::String zoneType = "ZoneType_Default";
	Ogre::String zoneName = "asdasd" +"_room1_zone";
	PCZone * newZone = mPCZSceneMgr->createZone(zoneType, zoneName);
	newZone->setEnclosureNode(mRoom1Node);
*/

	Ogre::SceneNode* sn;
	sn = mOgre->getSceneManager()->getRootSceneNode(); //->addChild()

	
		//->getRootSceneNode();

}
