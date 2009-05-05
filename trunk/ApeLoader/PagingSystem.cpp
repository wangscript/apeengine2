#include "PagingSystem.h"
//#include "GameSceneManager.h"
//#include "GameSystemManager.h"
#include "EditableTerrain.h"
//#include "GameObjectManager.h"
//#include "TextOutput.h"

#include "heightFunction.h"

//Paging_Config PagingConfig;

bool PagingSystem::running = false;
std::map<std::string,PagedObjects*> mFoliage;

PagedObjects::PagedObjects() { }
PagedObjects::~PagedObjects() { }

template<> PagingSystem* Ogre::Singleton<PagingSystem>::ms_Singleton = 0;

PagingSystem* PagingSystem::getSingletonPtr(void)
{
	return ms_Singleton;
}
PagingSystem& PagingSystem::getSingleton(void)
{  
	return ( *ms_Singleton );  
}

PagingSystem::PagingSystem()
{
	//addResources();

	//Setup Ogre::Root and the scene manager
	//root = OgreRender::getSingleton().getRoot();
	//window = OgreRender::getSingleton().getWindow();
	//sceneMgr = OgreRender::getSingleton().getSceneManager();
	//camera = OgreRender::getSingleton().getCamera();
	//viewport = OgreRender::getSingleton().getViewport();
	running = false;
	
	//PagingConfig.paintMode = true;
	//PagingConfig.eraseMode = false;

	/*
	//Load media (trees, grass, etc.)
	ResourceGroupManager::getSingleton().addResourceLocation("../../media/trees2", "FileSystem");
	ResourceGroupManager::getSingleton().addResourceLocation("../../media/terrain2", "FileSystem");
	ResourceGroupManager::getSingleton().addResourceLocation("../../media/grass", "FileSystem");
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	*/

	/*
	//Initialize OIS
	size_t windowHnd;
	window->getCustomAttribute("WINDOW", &windowHnd);
	inputManager = OIS::InputManager::createInputSystem(windowHnd);
	
	keyboard = (OIS::Keyboard*)inputManager->createInputObject(OIS::OISKeyboard, false);
	mouse = (OIS::Mouse*)inputManager->createInputObject(OIS::OISMouse, false);
	*/
	//Reset camera orientation
	camPitch = 0;
	camYaw = 0;

	//load();		//Load world
	//run();		//Display world

}

void PagingSystem::initialize() {
	//Setup Ogre::Root and the scene manager
	
	root = OgreRender::getSingleton().getRoot();
	window = OgreRender::getSingleton().getWindow();
	sceneMgr = OgreRender::getSingleton().getSceneManager();
	camera = OgreRender::getSingleton().getCamera();
	viewport = OgreRender::getSingleton().getViewport();
	
	running = true;

	camPitch = 0;
	camYaw = 0;
}

PagingSystem::~PagingSystem()
{
	//Shut down OIS
	//inputManager->destroyInputObject(keyboard);
	//inputManager->destroyInputObject(mouse);
	//OIS::InputManager::destroyInputSystem(inputManager);

	unload();
}

std::map<std::string,PagedObjects*> PagingSystem::getFoliage() {
	//if(mFoliage.empty())
		return mFoliage;
	//else
	//	return NULL;
}
PagedObjects* PagingSystem::getFoliageByName(std::string name) {
	//return mFoliage[name];

	//if(mFoliage.empty())
	//	return NULL;

	std::map<std::string, PagedObjects*>::iterator iter = mFoliage.begin();
	iter = mFoliage.find(name);
	if(iter != mFoliage.end()) {
		return iter->second;
	}

	return NULL;
}

void PagingSystem::removePagedObject(std::string name) {
	std::map<std::string, PagedObjects*>::iterator iter = mFoliage.begin();
	iter = mFoliage.find(name);
	
	if(iter != mFoliage.end()) {
		sceneMgr->destroyEntity(iter->second->entityName);
		delete iter->second->geometry->getPageLoader();
		delete iter->second->geometry;
		mFoliage.erase(iter);
		//PagingConfig.selectedPagedTrees = "";
	}	
}
void PagingSystem::removeAllPagedObjects() {
	std::map<std::string, PagedObjects*>::iterator iter;
	for(iter = mFoliage.begin(); iter != mFoliage.end(); iter++) {
		if(iter->second) {
			sceneMgr->destroyEntity(iter->second->entityName);
			delete iter->second->geometry->getPageLoader();
			delete iter->second->geometry;
		}
	}
	mFoliage.clear();
}

PagedGeometry* PagingSystem::addGrassPage(std::string name,Real pageSize,Real batchDistance, std::string materialName, Real minScale, Real maxScale, bool animated, Real swayLenght, Real swaySpeed, Real density, GrassTechnique grt, FadeTechnique ft) {

	//PagedObjects *po = getFoliageByName(name);
	PagedObjects *po;
	//if(getFoliage() == NULL) {
	//	po = getFoliageByName(name);
	//	if(po) {
	//		//OgreQueueText::instance()->Add("Paged Object with that name already exists");
	//		return NULL;
	//	}
	//}

	po = new PagedObjects();

	po->name = name;
	po->isGrass = true;
	po->isTree = false;
	po->pageSize = pageSize;
	po->batchDistance = batchDistance;
	po->materialName = materialName;
	po->minScale = minScale;
	po->maxScale = maxScale;
	po->animated = animated;
	po->swayLenght = swayLenght;
	po->swaySpeed = swaySpeed;
	po->density = density;
	po->grt = grt;
	po->ft = ft;
	po->pageBounds = TBounds(0, 0, 
		(EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().x), 
		(EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().z)); //Now only square terrains supported, kinda sucks
		//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainSizeZ")->toFloat()-7);

	PagedGeometry *grass = new PagedGeometry(camera, pageSize);
	grass->addDetailLevel<GrassPage>(batchDistance);

	po->grassLoader = new GrassLoader(grass);
	grass->setPageLoader(po->grassLoader);	//Assign the "treeLoader" to be used to load geometry for the PagedGeometry instance

	HeightFunction::initialize(sceneMgr);
	po->grassLoader->setHeightFunction(&HeightFunction::getTerrainHeight);

	po->grassLayer = po->grassLoader->addLayer(materialName);

	po->grassLayer->setMinimumSize(minScale, minScale);
	po->grassLayer->setMaximumSize(maxScale, maxScale);
	po->grassLayer->setAnimationEnabled(animated);		//Enable animations
	po->grassLayer->setSwayDistribution(7.0f);		//Sway fairly unsynchronized
	po->grassLayer->setSwayLength(swayLenght);				//Sway back and forth 0.5 units in length
	po->grassLayer->setSwaySpeed(swaySpeed);				//Sway 1/2 a cycle every second
	po->grassLayer->setDensity(density);				//Relatively dense grass
	po->grassLayer->setRenderTechnique(grt);
	po->grassLayer->setFadeTechnique(ft);	//Distant grass should slowly raise out of the ground when coming in range
	po->grassLayer->setColorMap("a_ETbase.jpg"); //terrain_texture2.jpg
	
	//po->grassLayer->setMinimumSize(50,20);

	//std::string densityMapName = "densitymap" + 
	Real rnd = (Math::UnitRandom()); //(1, 4));
	Ogre::String dmap;
	if(rnd <= 0.25)
		dmap = "densitymap1.png";
	if(rnd > 0.25 && rnd <= 0.5)
		dmap = "densitymap2.png";
	if(rnd > 0.5 && rnd <= 0.75)
		dmap = "densitymap3.png";
	if(rnd > 0.75)
		dmap = "densitymap4.png";

	MapChannel mc;
	//rnd = (Math::UnitRandom()); //(1, 4));
	//if(rnd <= 0.25)
		mc = CHANNEL_ALPHA;
	//if(rnd > 0.25 && rnd <= 0.5)
	//	mc = CHANNEL_BLUE;
	//if(rnd > 0.5 && rnd <= 0.75)
	//	mc = CHANNEL_GREEN;
	//if(rnd > 0.75)
	//	mc = CHANNEL_RED;

	po->grassLayer->setDensityMap(dmap,mc);
	
	//MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("grass_test");
	//Ogre::String n;
	//n = material->getName();

	
	po->grassLayer->setMapBounds(po->pageBounds);

	po->geometry = grass;

	mFoliage[name] = po;

	return grass;
}

void PagingSystem::updateTreeBrush() {
	
	//if (GameSystemManager::getSingleton()->getInput()->isLeftButtonDown() &&  terrain_config.mIsTerrainLoaded )
	//{
	//	if(GameSceneManager::getSingleton()->getBrush() == BRUSH_FOLIAGE)
	//	{
	//		treeBrush();
	//	}

	//}
}

void PagingSystem::treeBrush() {
	//if(PagingConfig.selectedPagedTrees!= "") {
		//PagedObjects *po = getFoliageByName(PagingConfig.selectedPagedTrees);
		PagedObjects *po = getFoliageByName("");
		if(po) {

			Degree yaw = Degree(Math::RangeRandom(0, 360));

			Real scale = Math::RangeRandom(po->minScale,po->maxScale);

			//Vector3 pos = GameSystemManager::getSingleton()->getTerrain()->mPointer->getPosition();
			
			Vector3 pos = Vector3(0,0,0); //GameSystemManager::getSingleton()->getTerrain()->mPointer->getPosition();

			Radian rndAng = Radian(Math::RangeRandom(0, Math::TWO_PI));
			Real rndLen = Math::RangeRandom(0,10); //PagingConfig.brushHeight
			pos.x += Math::Sin(rndAng) * rndLen;
			pos.z += Math::Cos(rndAng) * rndLen;
			
			//if(PagingConfig.paintMode)
			//	po->treeLoader->addTree(po->entity, pos, yaw, scale);

			//if(PagingConfig.eraseMode)
			//	po->treeLoader->deleteTrees(pos,PagingConfig.brushHeight);

		}
	//}
}

PagedGeometry* PagingSystem::addTreePage(std::string name,Real pageSize,Real batchDistance, Real batchFade, Real impostorDist, Real impostorFade, std::string meshName, unsigned int quantity, Real minScale, Real maxScale) {

	PagedObjects *po; // = getFoliageByName(name);
	//if(po) {
		//OgreQueueText::instance()->Add("Paged Object with that name already exists");
	//	return NULL;
	//}

	PagedGeometry *trees = new PagedGeometry();
	
	po = new PagedObjects();
	
	po->name = name;
	po->meshName = meshName;
	po->pageSize = pageSize;
	po->batchDistance = batchDistance;
	po->batchFade = batchFade;
	po->impostorDist = impostorDist;
	po->impostorFade = impostorFade;
	po->quantity = quantity;
	po->minScale = minScale;
	po->maxScale = maxScale;

	trees->setCamera(OgreRender::getSingleton().getCamera());	//Set the camera so PagedGeometry knows how to calculate LODs
	trees->setPageSize(pageSize);	//Set the size of each page of geometry
	trees->setInfinite();		//Use infinite paging mode
	trees->addDetailLevel<BatchPage>(batchDistance, batchFade);		//Use batches up to 150 units away, and fade for 30 more units
	trees->addDetailLevel<ImpostorPage>(impostorDist, impostorFade);	//Use impostors up to 400 units, and for for 50 more units
	
	//Real terrX = 1000; //terrain_config.mTerrainSizeX;
	//Real terrZ = 1000; //terrain_config.mTerrainSizeZ;

	Real terrX = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().x;
	Real terrZ = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().z;

	//Real terrX = GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainSizeX")->toFloat();
	//Real terrZ = GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainSizeZ")->toFloat();

	po->pageBounds = TBounds(0, 0, terrX, terrZ);

	TreeLoader2D *treeLoader = new TreeLoader2D(trees, po->pageBounds);
	trees->setPageLoader(treeLoader);	//Assign the "treeLoader" to be used to load geometry for the PagedGeometry instance

	HeightFunction::initialize(OgreRender::getSingleton().getSceneManager());
	treeLoader->setHeightFunction(&HeightFunction::getTerrainHeight);

	treeLoader->setColorMap("terrain_lightmap.jpg");

	po->entityName = "Foliage_" + name; //std::string("1") GameObjectManager::getSingleton()->getNextCompIndex();
	po->entity = OgreRender::getSingleton().getSceneManager()->createEntity(po->entityName, meshName);
	po->isTree = true;
	po->isGrass = false;
	po->geometry = trees;
	po->treeLoader = treeLoader;

	mFoliage[name] = po;

	return trees;
}

void PagingSystem::randomizeTreePage(std::string name) {
	if(name != "") {
		if(!mFoliage[name])
			return;
		Ogre::Vector3 position = Ogre::Vector3::ZERO;
		Radian yaw;
		Real scale;
		for (unsigned int i = 0; i < mFoliage[name]->quantity; i++){
			yaw = Degree(Math::RangeRandom(0, 360));

			//Real terrX = 0; //terrain_config.mTerrainSizeX;
			//Real terrZ = 0; //terrain_config.mTerrainSizeZ;

			Real terrX = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().x;
			Real terrZ = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().z;

			position.x = Math::RangeRandom(0,terrX-50);
			position.z = Math::RangeRandom(0,terrZ-50);

			scale = Math::RangeRandom(mFoliage[name]->minScale, mFoliage[name]->maxScale);

			mFoliage[name]->position = position;
			mFoliage[name]->treeLoader->addTree(mFoliage[name]->entity, position, yaw, scale);
		}
	}
}

void PagingSystem::addSingleTreePage(std::string pageName,Vector3 pos) {
	if(mFoliage[pageName]) {
		Radian yaw;
		Real scale;
		//for (unsigned int i = 0; i < mFoliage[pageName]->quantity; i++){
			
			yaw = Degree(Math::RangeRandom(0, 360));

			Real terrX = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().x;
			Real terrZ = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().z;

			//position.x = Math::RangeRandom(0,terrX-50);
			//position.z = Math::RangeRandom(0,terrZ-50);

			Ogre::Real minScale = mFoliage[pageName]->minScale;
			Ogre::Real maxScale = mFoliage[pageName]->maxScale;

			scale = Math::RangeRandom(minScale, maxScale);

			mFoliage[pageName]->position = pos;
			mFoliage[pageName]->treeLoader->addTree(mFoliage[pageName]->entity, pos, yaw, scale);
			//->getAttachedObjectIterator()


				// do whatever there is to do with the entity...
			

		//}
	}
}

void PagingSystem::unload()
{

	removeAllPagedObjects();
}
void PagingSystem::setBrushSize(Real size) {
	
	//bool terrainLoaded = terrain_config.mIsTerrainLoaded;

	//if(!terrainLoaded || size == 0)
	//	return;
	
	//PagingConfig.brushHeight = size;
	//PagingConfig.brushWidth = size;

	//GameSystemManager::getSingleton()->getTerrain()->mPincelDecal->setSize(Vector2(size * 2,size * 2));

	//static_cast<TerrainSystem*>(GameSystemManager::getSingleton()->getSystem("TerrainSystem"))->mPincelDecal->setSize(Vector2(size * 2,size * 2));
	//GameSystemManager::getSingleton()->getTerrain()->mPincelDecal->setSize(Vector2(size * 2,size * 2));

}
void PagingSystem::update()
{
	if(running) {
		render();
		//updateTreeBrush();
	}
}

void PagingSystem::render()
{
	//[NOTE] PagedGeometry::update() is called every frame to keep LODs, etc. up-to-date
	//grass->update();
	//trees->update();
	//bushes->update();

	std::map<std::string, PagedObjects*>::iterator iter;
	for(iter = mFoliage.begin(); iter != mFoliage.end(); iter++) {
		iter->second->geometry->update(); // second->update();
		
	}

}

bool PagingSystem::loadSettings(XMLNode xMainNode) {

	bool isTree;

	std::string name;
	Real pageSize;
	Real batchDistance;
	std::string materialName;
	Real minScale;
	Real maxScale;
	bool animated;
	Real swayLenght;
	Real swaySpeed;
	Real density;
	GrassTechnique grt;
	FadeTechnique ft;

	std::string meshName;
	Real batchFade;
	Real impostorDist;
	Real impostorFade;
	unsigned int quantity;

	XMLNode xNode=xMainNode.getChildNode("PagedGeometry");

	int PagedObjectIter = 0;
	int TreeIter = 0;

	//XMLNode xPagedObjectNode; // = xNode.getChildNode("PagedObject");
	//xNode.nChildNode("Object")

	//while(!xNode.getChildNode("PagedObject").isEmpty())
	//{
	for(int i = 0;i<xNode.nChildNode("PagedObject");i++) 
	{
		XMLNode xPagedObjectNode = xNode.getChildNode("PagedObject",&PagedObjectIter);

		//XMLNode xPagedObjectNode = xNode.getChildNode("PagedObject");
		
		isTree = Ogre::StringConverter::parseBool(xPagedObjectNode.getAttribute("isTree"));

		if(isTree) {

			name = xPagedObjectNode.getAttribute("name");
			pageSize = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("pageSize"));
			batchDistance = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("batchDistance"));
			batchFade = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("batchFade"));
			impostorDist = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("impostorDist"));
			impostorFade = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("impostorFade"));
			meshName = xPagedObjectNode.getAttribute("meshName");
			quantity = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("quantity"));
			minScale = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("minScale"));
			maxScale = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("maxScale"));
			
			addTreePage(name,pageSize,batchDistance,batchFade,impostorDist,impostorFade,meshName,quantity,minScale,maxScale);

			//while(!xPagedObjectNode.getChildNode("Tree").isEmpty())
			//{
			for(int j = 0;j<xPagedObjectNode.nChildNode("Tree");j++) 
			{
				//XMLNode xTreeNode = xPagedObjectNode.getChildNode("Tree");
				XMLNode xTreeNode = xPagedObjectNode.getChildNode("Tree",&TreeIter);

				//mIsLoaded = Ogre::StringConverter::parseBool(xNode.getAttribute("isLoaded"));
				Vector3 pos;
				//if(xTreeNode)
				pos = Ogre::StringConverter::parseVector3(xTreeNode.getAttribute("position"));

				addSingleTreePage(name,pos);
				
				//xTreeNode = xPagedObjectNode.getChildNode("Tree");

			}
			TreeIter = 0;

		} else {
			
			name = xPagedObjectNode.getAttribute("name");
			pageSize = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("pageSize"));
			batchDistance = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("batchDistance"));
			materialName = xPagedObjectNode.getAttribute("materialName");
			minScale = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("minScale"));
			maxScale = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("maxScale"));
			animated = Ogre::StringConverter::parseBool(xPagedObjectNode.getAttribute("animated"));
			swayLenght = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("swayLenght"));
			swaySpeed = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("swaySpeed"));
			density = Ogre::StringConverter::parseReal(xPagedObjectNode.getAttribute("density"));

			std::string grassTech = xPagedObjectNode.getAttribute("GrassTechnique");

			if(grassTech == "GRASSTECH_QUAD")
				grt = GRASSTECH_QUAD;
			if(grassTech == "GRASSTECH_CROSSQUADS")
				grt = GRASSTECH_CROSSQUADS;
			if(grassTech == "GRASSTECH_SPRITE")
				grt = GRASSTECH_SPRITE;

			std::string fadeTech = xPagedObjectNode.getAttribute("FadeTechnique");

			if(fadeTech == "FADETECH_ALPHA")
				ft = FADETECH_ALPHA;
			if(fadeTech == "FADETECH_ALPHAGROW")
				ft = FADETECH_ALPHAGROW;
			if(fadeTech == "FADETECH_GROW")
				ft = FADETECH_GROW;

			addGrassPage(name,pageSize,batchDistance,materialName,minScale,maxScale,animated,swayLenght,swaySpeed,density,grt,ft);

		}

		//xPagedObjectNode = xNode.getChildNode("PagedObject");

	}

	return true;
}


