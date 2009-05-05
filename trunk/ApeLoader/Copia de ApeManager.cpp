#include "ApeManager.h"
#include "xmlParser.h"

#include "ZoneManager.h"

//#include "ObjectManager.h"

InputHandler* ApeManager::mInput = NULL;
OgreRender* ApeManager::mOgre = NULL;
EditableTerrain* ApeManager::mTerrain = NULL;
Physics* ApeManager::mPhysics = NULL;
ApeManager* ApeManager::mInstance = NULL;
ApeScene* ApeManager::mScene = NULL;
ObjectManager* ApeManager::mObjectManager = NULL;

bool ApeManager::mIsEditorMode = false;

ApeManager::ApeManager()
{

	
	

}

ApeManager::~ApeManager()
{ 

}

void ApeManager::update() {
	mObjectManager->update();
}

void ApeManager::initialize() {

	mOgre = new OgreRender();
	mInput = new InputHandler(mOgre);
	mPhysics = new Physics(mOgre);
	mTerrain = new EditableTerrain();
	mScene = new ApeScene();
	mObjectManager = new ObjectManager(mPhysics,mOgre);

	mOgre->initialize();
	mInput->initialize();
	mPhysics->initialize();
	mTerrain->initialize();
	mScene->initialize();
	mObjectManager->initialize();

	mObjectManager->addCustomGO();

	ZoneManager *mZM = new ZoneManager(mOgre,mObjectManager);

	loadApeMap("a");


}

ApeManager ApeManager::getSingleton() {
	if(mInstance == NULL)
		mInstance = new ApeManager();
	return *mInstance;
}

bool ApeManager::isEditorMode() {
	return mIsEditorMode;
}

bool ApeManager::loadApeMap(Ogre::String mapFileName) {
	
	//mapFileName += ".xml";

	std::string mFilePath = "../../Media/Maps/" + mapFileName + ".xml";
	
	XMLNode xMainNode;

	try {
		xMainNode=XMLNode::openFileHelper(mFilePath.c_str(),"ApeEngine"); //,"PMML"
	} catch(...) {
		Ogre::LogManager::getSingleton().logMessage("*** Error loading Ape map file ***");
		return false;
	}
	
	//XMLNode xNode=xMainNode.getChildNode("Terrain");
	//const char* n = xNode.getAttribute("mIsTerrainLoaded");
	//printf("  Name is: '%s' (note that &lt; has been replaced by '<')\n", xNode.getChildNode("Application").getAttribute("name"));
	
	mTerrain->loadSettings(xMainNode);
	mScene->loadSettings(xMainNode);
	mObjectManager->loadObjectsFromXML(xMainNode);

	mScene->createSky();
	mTerrain->generateTerrain();
	return true;
}
