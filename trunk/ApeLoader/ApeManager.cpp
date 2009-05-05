#include "ApeManager.h"
#include "xmlParser.h"

#include "ZoneManager.h"

template<> ApeManager* Ogre::Singleton<ApeManager>::ms_Singleton = 0;
ApeManager* ApeManager::getSingletonPtr(void)
{
	return ms_Singleton;
}
ApeManager& ApeManager::getSingleton(void)
{  
	//assert( ms_Singleton );  
	return ( *ms_Singleton );  
}

ApeManager::ApeManager() 
{
	/*
	: 	mOgre(0),
	mInput(0),
	mTerrain(0),
	mPhysics(0),
	mScene(0),
	mObjectManager(0),
	mZoneMan(0)
	*/
}

ApeManager::~ApeManager()
{ 
	//delete mObjectManager;
	//delete mInput;
	//delete mPhysics;
	//delete mTerrain;
	//delete mScene;
	//delete mOgre;
}

void ApeManager::update() {
	ObjectManager::getSingleton().update();
	OgreRender::getSingleton().update();
	
}

void ApeManager::initialize() {
	

	/*
	mOgre = OgreRender::getSingleton().getSingletonPtr();
	mInput = InputHandler::getSingleton().getSingletonPtr();
	mTerrain = EditableTerrain::getSingleton().getSingletonPtr();
	mPhysics = Physics::getSingleton().getSingletonPtr();
	mScene = ApeSceneManager::getSingleton().getSingletonPtr();
	mObjectManager = ObjectManager::getSingleton().getSingletonPtr();
	mZoneMan = ZoneManager::getSingleton().getSingletonPtr();
	*/

}

void ApeManager::start() {
	
	ObjectManager::getSingleton().addCustomGO();
	//loadApeMap("a");
	
	//ZoneManager::getSingleton().createZones();

}

/*
ApeManager ApeManager::getSingleton() {
	if(mInstance == NULL)
		mInstance = new ApeManager();
	return *mInstance;
}
*/
bool ApeManager::isEditorMode() {
	return mIsEditorMode;
}

bool ApeManager::loadApeMap(Ogre::String mapFileName) {
	
	//mapFileName += ".xml";

	std::string mFilePath = "../../Media/Maps/" + mapFileName + ".xml";
	
	mCurrentMapName = mapFileName;
	//GameSceneManager::getSingleton()->currentMapName

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
	
	//EditableTerrain::getSingleton().loadSettings(xMainNode);
	ApeSceneManager::getSingleton().loadSettings(xMainNode);
	//ObjectManager::getSingleton().loadObjectsFromXML(xMainNode);

	ApeSceneManager::getSingleton().createSky();

	//EditableTerrain::getSingleton().generateTerrain();

	//PagingSystem::getSingleton().loadSettings(xMainNode);

	return true;
}
