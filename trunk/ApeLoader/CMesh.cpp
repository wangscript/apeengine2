#include "CMesh.h"
#include "CCharacter.h"

std::string CMesh::mFamilyID = "CMesh";
std::string CMesh::mComponentID = "CMesh";

CMesh::CMesh() : mEntity(0),
													   mObjMan(0),
													   mOgre(0)
{
	mOgre = OgreRender::getSingleton().getSingletonPtr();
	mObjMan = ObjectManager::getSingleton().getSingletonPtr();
}
CMesh::CMesh(Ogre::String meshName,Ogre::String entName) :	mEntity(0),
											mObjMan(0),
											mOgre(0)
{
	mOgre = OgreRender::getSingleton().getSingletonPtr();
	mObjMan = ObjectManager::getSingleton().getSingletonPtr();
	mMeshName = meshName;
	mEntityName = entName;

}
CMesh::CMesh(Ogre::Entity* entity) :	mEntity(0),
																					mObjMan(0),
																					mOgre(0)
{
	mOgre = OgreRender::getSingleton().getSingletonPtr();
	mObjMan = ObjectManager::getSingleton().getSingletonPtr();
	mEntity = entity;
	mMeshName = entity->getName();
	mEntityName = entity->getName() + ".mesh";

}

Ogre::Entity* CMesh::getEntity() {
	return mEntity;
}

CMesh::~CMesh()
{
	//ResourceGroupManager::getSingleton().er
	//mEntity->_deinitialise();
	//delete mEntity;
}

void CMesh::update() {

}

void CMesh::setup() {
	//This is to keep track of objects, when i cast rays on meshes, i get the name of the owner
	//std::string objectName;
	//objectName = getOwnerObject()->getID().c_str();

	//mEntity->setUserAny( Ogre::Any(objectName) );

	//CCharacter * mCChar = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));
	//CRender* mCRender = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

	//if(mCChar) {
	//	mEntity = mOgre->getSceneManager()->createEntity(mCRender->getNodeName(),mMeshName);
	//}
	
}
