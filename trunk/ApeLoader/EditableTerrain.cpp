#include "EditableTerrain.h"
#include "ETTerrainManager.h"
#include "Physics.h"
#include "ApeManager.h"

#include <stdio.h>
#include <fstream>
#include <ios>
#include <string.h>

//#include "MessageManager.h"

ET::TerrainManager* EditableTerrain::mTerrainMgr = 0;
ET::SplattingManager* EditableTerrain::mSplatMgr = 0;
const ET::TerrainInfo* EditableTerrain::mTerrainInfo = 0;
Ogre::SceneNode* EditableTerrain::mPointer = 0;

bool EditableTerrain::mDeform = true;

ET::Brush EditableTerrain::mEditBrush = ET::Brush();
Ogre::Image EditableTerrain::terrainBrushImage = Ogre::Image();
Ogre::Image EditableTerrain::paintBrushImage = Ogre::Image();
DecalCursor *EditableTerrain::mPincelDecal = 0;

//string TerrainSystem::mHeightmapFileName = "";

bool EditableTerrain::enablePainting = true;
bool EditableTerrain::riseTerrain = true;
bool EditableTerrain::paintTerrain = true;
bool EditableTerrain::smoothTerrain = true;

std::string EditableTerrain::textureList[6] = {"","","","","",""};

//EditableTerrain* EditableTerrain::ms_Singleton = 0;

template<> EditableTerrain* Ogre::Singleton<EditableTerrain>::ms_Singleton = 0;
EditableTerrain* EditableTerrain::getSingletonPtr(void)
{
	return ms_Singleton;
}
EditableTerrain& EditableTerrain::getSingleton(void)
{  
	//assert( ms_Singleton );  
	return ( *ms_Singleton );  
}


EditableTerrain::EditableTerrain() : mOgre(0)
{
	//mInput = ;
	resetParameters();
}

/*
void EditableTerrain::OnOgreRender_Created(OgreRender* ogre) {
	mOgre = ogre;
}

void EditableTerrain::OnInput_Created(InputHandler* input) {
	mInput = input;
}
*/
/*
void EditableTerrain::initialize() {
	makeConnections();
	
}
*/
/*
void EditableTerrain::makeConnections() {
	Physics* mPhysics = ApeManager::getSingleton().getPhysicsImp();
	
	sig_TerrainCreated.connect(mPhysics, &Physics::OnEditableTerrain_Generated);	

}
*/


void EditableTerrain::update() { 
	paint();
}

EditableTerrain::~EditableTerrain() {
	delete mTerrainMgr;
	delete mSplatMgr;
	
	delete mPincelDecal;
	delete mTerrainInfo;
	//delete mPointer;

	Ogre::ResourcePtr rm = TextureManager::getSingleton().getByName("ETLightmap");
	TextureManager::getSingleton().remove(rm);
}

void EditableTerrain::initialize() {
	
	mOgre = OgreRender::getSingletonPtr();
}

void EditableTerrain::addTexture(const std::string name) {

		//if(
	
	if(!mIsTerrainLoaded) {
		//OgreQueueText::instance()->
		//OgreQueueText::instance()->Add("Create the terrain first");
		//OgreQueueText::instance()
		return;
	}

	if(mMaxSplattingTextures==mCurrentSplattingTextures)
		return;

	FileInfoListPtr finfo =  ResourceGroupManager::getSingleton().findResourceFileInfo("ET", name);
	FileInfoList::iterator it = finfo->begin();
	if (it != finfo->end())
	{
		(mCurrentSplattingTextures)++;

		Ogre::String completeFileName ((it)->archive->getName() + "/" + name);

		for(unsigned int i = 0; i < mMaxSplattingTextures;i++) {
			if(textureList[i] == "") {
				Ogre::String newName = "splatting" + Ogre::StringConverter::toString(i) + ".png";
				Ogre::String outfileName ((it)->archive->getName() + "/" + newName);
				textureList[i] = newName;
				CopyFile((LPCSTR)completeFileName.c_str(),(LPCSTR)outfileName.c_str(),0);
				return;
			}
		}
	}
}
void EditableTerrain::removeTexture(const std::string name) {

	if(mCurrentSplattingTextures==0)
		return;

	FileInfoListPtr finfo =  ResourceGroupManager::getSingleton().findResourceFileInfo("ET", name);
	FileInfoList::iterator it = finfo->begin();
	if (it != finfo->end())
	{
		Ogre::String completeFileName ((it)->archive->getName() + "/" + name); 
		for(unsigned int i = 0; i<mMaxSplattingTextures;i++) {
			std::string currTexture = textureList[i];
			if(currTexture == name) {
 				textureList[i] = "";
				//currTextures--;
				(mCurrentSplattingTextures)--;

				remove(completeFileName.c_str());
			}
		}
	}
}

void EditableTerrain::searchDiskForTextures() {

	mCurrentSplattingTextures = 0;

	StringVectorPtr resourceNames = ResourceGroupManager::getSingleton().findResourceNames("ET","splatting*.png" );
	std::vector<Ogre::String>::const_iterator itResourceName = resourceNames->begin();
	while ( itResourceName != resourceNames->end() )
	{
		if(mCurrentSplattingTextures < mMaxSplattingTextures) {
			for(unsigned int i = 0; i < mMaxSplattingTextures;i++) {
				std::string texNum = (*itResourceName).substr(9,1);

				std::string r = (*itResourceName).substr(10,5);
				
				int itmp = mCurrentSplattingTextures;
				
				textureList[mCurrentSplattingTextures] = "splatting" + texNum + ".png";
				mCurrentSplattingTextures++;
				break;
			}
		}
		++itResourceName;
	} 	
}

void EditableTerrain::resetParameters()
{
	mIsTerrainLoaded = false;
	mHeightmapFileName == "";
	mTerrainSizeX = 1000;
	mTerrainSizeY = 300;
	mTerrainSizeZ = 1000;
	mLODMorphFactor = 0.2f;
	mLODMorphing = true;
	mLODErrorMargin = 2.0f;
	mMaxSplattingTextures = 6;
	mCurrentSplattingTextures = 0;

}

void EditableTerrain::generateTerrain() {

	if(mIsTerrainLoaded)
		return;

	MaterialManager::getSingleton().unloadAll();
	MaterialManager::getSingleton().reloadAll();

	searchDiskForTextures();

	mIsTerrainLoaded = true;

	SceneManager *mSceneMgr = mOgre->getSceneManager();
	Camera *mCamera = mOgre->getCamera();

	// create terrain manager
	mTerrainMgr = new ET::TerrainManager(mSceneMgr);


	//if(mHeightmapFileName == "")
	if(ApeManager::getSingleton().mCurrentMapName == "")
		mHeightmapFileName = "ETterrain000.png";

	mTerrainMgr->setLODErrorMargin(mLODErrorMargin
									, mCamera->getViewport()->getActualHeight());
	
	mTerrainMgr->setUseLODMorphing(mLODMorphing
									,mLODMorphFactor, "morphFactor");
	
	// create a fresh, mid-high terrain for editing
	ET::TerrainInfo terrainInfo(mHeightmapWidth, mHeightmapHeight
								, vector<float>((mHeightmapWidth) * (mHeightmapHeight), 0.5f));

	// set position and size of the terrain
	terrainInfo.setExtents(AxisAlignedBox(0, 0, 0, mTerrainSizeX, mTerrainSizeY, mTerrainSizeZ));

	// now render it
	mTerrainMgr->destroyTerrain();
	mTerrainMgr->createTerrain(terrainInfo,33,255,true,true);

	mSplatMgr = new ET::SplattingManager("ETSplatting", "ET", 128, 128, 3);
	// specify number of splatting textures we need to handle
	mSplatMgr->setNumTextures(mMaxSplattingTextures);
	
	// create a manual lightmap texture
	Ogre::TexturePtr alightmapTex = TextureManager::getSingleton().createManual(
	"ETLightmap", "ET", TEX_TYPE_2D, 128, 128, 1, PF_BYTE_RGB);
	Ogre::Image lightmap;
	ET::createTerrainLightmap(terrainInfo, lightmap, 128, 128, Ogre::Vector3(1, -1, 1), ColourValue::White,
	Ogre::ColourValue(0.3, 0.3, 0.3));
	alightmapTex->getBuffer(0, 0)->blitFromMemory(lightmap.getPixelBox(0, 0));

	// load the terrain material and assign it
	MaterialPtr material (MaterialManager::getSingleton().getByName("ETTerrainMaterial"));
	material->setReceiveShadows(true);
	//material->setCa
	mTerrainMgr->setMaterial(material);
	
	Ogre::Image image;
	
	//std::string t2 = GameSystemManager::getSingleton()->getTerrain()->mHeightmapFileName;
	
	std::string t1 = mHeightmapFileName;


	if(ApeManager::getSingleton().mCurrentMapName != "")
		image.load("../../Media/Maps/" + mHeightmapFileName, "ET");
	else
		image.load("ETterrain000.png", "ET");

	//image.load("terrain_ETM.png", "ET");

	ET::TerrainInfo info;
	ET::loadHeightmapFromImage(info, image);
	//info.setExtents(AxisAlignedBox(0, 0, 0, 1500, 300, 1500));
	info.setExtents(AxisAlignedBox(0, 0, 0, mTerrainSizeX, mTerrainSizeY, mTerrainSizeZ));
	mTerrainMgr->createTerrain(info,33,255,true,true);
	mTerrainInfo = & mTerrainMgr->getTerrainInfo();
	
	// now load the splatting maps
	for (Ogre::uint i = 0; i < mSplatMgr->getNumMaps(); ++i)
	{
		if(ApeManager::getSingleton().mCurrentMapName != "")
			image.load("../../Media/Maps/" + ApeManager::getSingleton().mCurrentMapName + "_ETcoverage."+StringConverter::toString(i)+".png", "ET");
		else
			image.load("ETcoverage."+StringConverter::toString(i)+".png", "ET");

		mSplatMgr->loadMapFromImage(i, image);
	}

	//Entity* pointer = GameSceneManager::getSingleton()->getSceneManager()->createEntity("Pointer", "arrow.mesh");
	mPointer = mOgre->getSceneManager()->getRootSceneNode()->createChildSceneNode("PointerNode");
	//mPointer->attachObject(pointer);

	mPincelDecal = new DecalCursor(mOgre->getSceneManager()
									,material,Vector2(64,64),"decal2.png");
	//, mTerrainMgr

	setTerrainEditBrush(5);
	//mChosenTexture = 1;

	Physics::getSingleton().createTerrainActor();

	//sig_TerrainCreated(true);
	//GameSystemManager::getSingleton()->createPaging();
}



void EditableTerrain::updateLightmap()
{
	if(!mIsTerrainLoaded)
		return;

	Image lightmap;
	ET::createTerrainLightmap(*mTerrainInfo, lightmap, 128, 128, Vector3(1, -1, 1), ColourValue(1,1,1),
	ColourValue(0.3, 0.3,  0.3));

	// get our dynamic texture and update its contents
	TexturePtr tex = TextureManager::getSingleton().getByName("ETLightmap");
	tex->getBuffer(0, 0)->blitFromMemory(lightmap.getPixelBox(0, 0));
}

Ogre::Real EditableTerrain::getTerrainHeightAt(Real x,Real z) {
	
	
	//po->pageBounds = TBounds(0, 0, 
	Ogre::Real mapX = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().x;
	Ogre::Real mapY = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().y;
	Ogre::Real mapZ = EditableTerrain::getSingleton().getTerrainManager()->getTerrainInfo().getExtents().getSize().z;
	
	if( (x > mapX || z > mapZ) || (x < 0 || z < 0) )
		return 0;

	Ray ray;
	//ray.setOrigin(Vector3(x, -(mapY+1), z));
	//ray.setDirection(Vector3::UNIT_Y);

	ray.setOrigin(Vector3(x, (mapY), z));
	ray.setDirection(Vector3::NEGATIVE_UNIT_Y);


	std::pair<bool, Vector3> result = mTerrainInfo->rayIntersects(ray);
	if (result.first)
	{
		return result.second.y;
	}
	//LogManager::getSingleton().logMessage("No hay resultados para: X = " + StringConverter::toString(result.second.x) + " Y = " + StringConverter::toString(result.second.y) + " Z = " + StringConverter::toString(result.second.z) ); 

	return 0.0f;
}

Ogre::Vector3 EditableTerrain::rayIntersectsTerrain() {
	int width = mInput->getMouseStat().width;
	int height = mInput->getMouseStat().height;
	int Xabs = mInput->getMouseStat().X.abs;
	int Yabs = mInput->getMouseStat().Y.abs;
	
	Ray mouseRay = mOgre->getCamera()->getCameraToViewportRay(Xabs/float(width), Yabs/float(height));
	std::pair<bool, Vector3> result = mTerrainInfo->rayIntersects(mouseRay);
	if (result.first)
	{
		return result.second;
	}
	return Vector3::ZERO;
}

void EditableTerrain::updateBrush(const OIS::MouseEvent &evt) { //Ogre::Real screenX,Ogre::Real screenY
	// Update CEGUI with the mouse motion
	//CEGUI::System::getSingleton().injectMouseMove( arg.state.X.rel, arg.state.Y.rel );
	if(!mIsTerrainLoaded)
		return;
	
	//if(!GameSystemManager::getSingleton()->getInput()->isLeftButtonDown())
	//	return;

	// whenever the mouse is moved, we update the position on the
	// terrain to which the mouse is currently pointing
	int width = mInput->getMouseStat().width;
	int height = mInput->getMouseStat().height;
	int Xabs = mInput->getMouseStat().X.abs;
	int Yabs = mInput->getMouseStat().Y.abs;

	//evt.state.X.abs/float(evt.state.width)
	//evt.state.Y.abs/float(evt.state.height)

	Ray mouseRay = mOgre->getCamera()->getCameraToViewportRay(evt.state.X.abs/float(evt.state.width), evt.state.Y.abs/float(evt.state.height));
	//Ray mouseRay = GameSceneManager::getSingleton()->getCamera()->getCameraToViewportRay(Xabs/float(width), Yabs/float(height));
	// since ETM is no longer a scene manager, we don't use a ray scene query,
	// but instead query the terrain info directly
	std::pair<bool, Vector3> result = mTerrainInfo->rayIntersects(mouseRay);
	if (result.first)
		mPointer->setPosition(result.second);

}

void EditableTerrain::paint() {

	if(!mIsTerrainLoaded || !enablePainting)
		return;

	
	//if(GameSceneManager::getSingleton()->getBrush() == BRUSH_PAINT || GameSceneManager::getSingleton()->getBrush() == BRUSH_DEFORM || GameSceneManager::getSingleton()->getBrush() == BRUSH_FOLIAGE && mIsTerrainLoaded) {
	if(mIsTerrainLoaded) {
		mPincelDecal->setPosition(mPointer->getPosition());
		mPincelDecal->show();
	} else {
		mPincelDecal->hide();
	}
	

	if (mInput->isLeftButtonDown() && mIsTerrainLoaded) // || mRMouseDown
	{
		Real time = mOgre->getTimeSinceLastFrame();
		//if(GameSceneManager::getSingleton()->getBrush() == BRUSH_DEFORM)
		//{
			if(!smoothTerrain) {
				float brushIntensity = time * (mTerrainBrushIntensity) * (riseTerrain ? 1 : -1); //0.4
				Vector3 deformPos = mPointer->getPosition();
				int x = mTerrainInfo->posToVertexX(deformPos.x);
				int z = mTerrainInfo->posToVertexZ(deformPos.z);
				mTerrainMgr->deform(x, z, mEditBrush, brushIntensity);
			} else {
				float brushIntensity = time * (mTerrainBrushIntensity) * 4; //0.4
				Vector3 deformPos = mPointer->getPosition();
				int x = mTerrainInfo->posToVertexX(deformPos.x);
				int z = mTerrainInfo->posToVertexZ(deformPos.z);
				mTerrainMgr->setHeights(x,z,averageFilter(x,z,mEditBrush,brushIntensity));
				mTerrainMgr->deform(x, z, mEditBrush, 0);
			}
		//}
		//if(GameSceneManager::getSingleton()->getBrush() == BRUSH_PAINT)
		//{
			float brushIntensity = time * (mPaintBrushIntensity) * (paintTerrain? 1 : 2) * (paintTerrain? 1 : -1); //5.0
			Vector3 paintPos = mPointer->getPosition();
			int x = mTerrainInfo->posToVertexX(paintPos.x);
			int z = mTerrainInfo->posToVertexZ(paintPos.z);
			mSplatMgr->paint(mChosenTexture, x, z, mEditBrush, brushIntensity);
		//}
	}
}

ET::Brush EditableTerrain::averageFilter(int x, int z, ET::Brush shape, float fIntensity)
{
      // When you're doing a loop possibly thousands of times, it's worth setting these
      // aside rather than calling a function every iteration.
   size_t iWidth = shape.getWidth();
   size_t iHeight = shape.getHeight();

      // Faster to presize than resize
   std::vector<float> vecReturnBuffer(iWidth * iHeight);
   std::vector<float> vecHeightBuffer(iWidth * iHeight);
   ET::Brush brushReturn = ET::Brush(vecReturnBuffer, iWidth, iHeight);
   ET::Brush brushHeights = ET::Brush(vecHeightBuffer, iWidth, iHeight);

   mTerrainMgr->getHeights(x, z, brushHeights);

   float fSumHeights = 0.0f;
   size_t iNumHeights = iWidth * iHeight;

      // Find the sum of all the heights within the sample
   for (Ogre::uint i = 0; i < iWidth; i++)
   {
      for(Ogre::uint j = 0; j < iHeight; j++)
      {
         fSumHeights += brushHeights.at(i, j);
      }
   }

      // Find the average height within the sample
   float fAvgHeight = fSumHeights / iNumHeights;

   for (Ogre::uint i = 0; i < iWidth; i++)
   {
      for(Ogre::uint j = 0; j < iHeight; j++)
      {
         float fHeight = brushHeights.at(i, j);
         float fDelta = fHeight - fAvgHeight;
         float fShapeMask = shape.at(i, j);

         fDelta = (fDelta * fShapeMask * fIntensity);

         brushReturn.at(i, j) = fHeight - fDelta;
      }
   }

   return brushReturn;
}

void EditableTerrain::setMapSize(Ogre::Vector3 terrainSize) {
	mTerrainSizeX = terrainSize.x;
	mTerrainSizeY = terrainSize.y;
	mTerrainSizeZ = terrainSize.z;

	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainSizeX")->setValue(terrainSize.x);
	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainSizeY")->setValue(terrainSize.y);
	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainSizeZ")->setValue(terrainSize.z);

}

ET::TerrainManager* EditableTerrain::getTerrainManager(){
	return mTerrainMgr;
}

void EditableTerrain::removeTerrain() {
	if(!mIsTerrainLoaded)
	return;

	if(mSplatMgr)
		mSplatMgr->~SplattingManager();
	
	if(mTerrainMgr)
		mTerrainMgr->~TerrainManager();

	//SceneNode *pn = GameSceneManager::getSingleton()->getSceneManager()->getSceneNode("PointerNode");
	//pn->detachAllObjects();

	//GameSceneManager::getSingleton()->getSceneManager()->destroySceneNode("PointerNode");
	mOgre->getSceneManager()->destroySceneNode("PointerNode");

	//GameSceneManager::getSingleton()->getSceneManager()->destroyMovableObject((MovableObject*)pn);// getSceneNode("PointerNode")->detachAllObjects();// getRootSceneNode()->detachObject("PointerNode");
	mOgre->getSceneManager()->destroyEntity("Pointer");// getEntity("Pointer")-> _deinitialise();// detachObject("PointerNode");
	//Ogre::ResourcePtr rm = Ogre::ResourceManager::getByName("Pointer"); //TextureManager::getSingleton().getByName("ETLightmap");
	//Ogre::ResourceManager::remove(rm);

	//if(!lightmapTex.isNull()) {
		Ogre::ResourcePtr rm = TextureManager::getSingleton().getByName("ETLightmap");
		TextureManager::getSingleton().remove(rm);
	//}
	//if(mTerrainMgr)
	//	mTerrainMgr->~SplattingManager();
		
	mIsTerrainLoaded = false;
}

//void TerrainSystem::setBrushSize()
//{
//	mEditBrush
//}
void EditableTerrain::setTerrainEditBrushIntensity(float size)
{
	//terrainBrushIntensity = size;
	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainBrushIntensity")->setValue(size);	
	mTerrainBrushIntensity = size;

}
void EditableTerrain::setPaintEditBrushIntensity(float size)
{
	//paintBrushIntensity = size;
	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("paintBrushIntensity")->setValue(size);	
	mPaintBrushIntensity = size;
}

void EditableTerrain::setTerrainEditBrush(unsigned short size)
{
	if(size==0)
		return;

	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainBrushHeight")->setValue(size);	
	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("terrainBrushWidth")->setValue(size);	

	mTerrainBrushHeight = (unsigned int)size;
	mTerrainBrushWidth = (unsigned int)size;

	if(mPincelDecal)
		mPincelDecal->setSize(Vector2(size * 10,size * 10));

	terrainBrushImage.load("brush.png", "ET");
	terrainBrushImage.resize(size,size);
	mEditBrush = ET::loadBrushFromImage(terrainBrushImage);
}
void EditableTerrain::setPaintEditBrush(unsigned short size)
{
	if(size==0)
		return;

	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("paintBrushHeight")->setValue(size);	
	//GameSystemManager::getSingleton()->getSystem("TerrainSystem")->getParam("paintBrushWidth")->setValue(size);	

	mPaintBrushHeight = size;
	mPaintBrushWidth = size;

	if(mPincelDecal)
		mPincelDecal->setSize(Vector2(size * 7,size * 7));

	paintBrushImage.load("brush.png", "ET");
	paintBrushImage.resize(size,size);
	mEditBrush = ET::loadBrushFromImage(paintBrushImage);
}

void EditableTerrain::mouseButtonDownNotification(bool controledByGui,unsigned int button) {
	if(button == OIS::MB_Left) {
		if(controledByGui)
			enablePainting = false; //GameSystemManager::getSingleton()->getTerrain()->
		else
			enablePainting = true; //GameSystemManager::getSingleton()->getTerrain()->
	}
}
void EditableTerrain::mouseButtonUpNotification(bool controledByGui,unsigned int button) {
	if(button == OIS::MB_Left) {
		//if(GameSceneManager::getSingleton()->getBrush() == BrushType::BRUSH_DEFORM)
			//updateLightmap(); //GameSystemManager::getSingleton()->getTerrain()->
	}
}

void EditableTerrain::saveTerrain(std::string mFileName)
{
	// just for demonstration, we'll save anything we can
	// start with the terrain
	Image image;
	ET::saveHeightmapToImage(*mTerrainInfo, image);
	//image.save("ETterrain.png");
	
	mHeightmapFileName = mFileName + ".png";

	//ResourceGroupManager::getSingleton().getResourceGroup()

	image.save("../../Media/Maps/" + mHeightmapFileName);

	// now save the splatting maps
	for (uint i = 0; i < mSplatMgr->getNumMaps(); ++i)
	{
		mSplatMgr->saveMapToImage(i, image);
		image.save("../../Media/Maps/" + mFileName + "_ETcoverage."+StringConverter::toString(i)+".png");
	}

	// now the lightmap
	Image lightmap;
	ET::createTerrainLightmap(*mTerrainInfo, lightmap, 512, 512, Vector3(1, -1, 1), ColourValue(1,1,1),
	ColourValue(0.3, 0.3,  0.3));
	lightmap.save("../../Media/Maps/" + mFileName + "_ETlightmap.png");

	// generate a base texture for this terrain (could be used for older hardware instead of splatting)
	// create an ImageList of our splatting textures.
	ET::ImageList textures (6);
	
	for (int i = 0; i < 6; ++i)
		textures[i].load("splatting"+StringConverter::toString(i)+".png", "ET");

	// create the base texture
	Image baseTexture;
	mSplatMgr->createBaseTexture(baseTexture, 512, 512, textures, 20, 20);
	baseTexture.save("../../Media/Maps/" + mFileName + "_ETbase.png");

	// finally create a minimap using the lightmap and the generated base texture
	Image minimap = ET::createMinimap(baseTexture, lightmap);
	minimap.save("../../Media/Maps/" + mFileName + "_ETminimap.png");

	//lightmap.save("../../Media/Maps/" + mFileName + "_ETlightmap.png");
}
/*
bool TerrainSystem::saveToXML() {
	
	saveTerrain();

	XMLHandler *xml = GameSystemManager::getSingleton()->getXMLHandler();

	TiXmlElement* parent = xml->createParentElement("TerrainConfig");
	
	TiXmlElement* wnd = xml->createChildElement(parent,"TerrainInfo");
	wnd->SetAttribute("Name", "ETM");
	return true;
}
*/

bool EditableTerrain::loadSettings(XMLNode xMainNode) {

	XMLNode xNode=xMainNode.getChildNode("Terrain");
	
	try {
		mTerrainSizeX = Ogre::StringConverter::parseReal(xNode.getAttribute("mTerrainSizeX"));
		mTerrainSizeY = Ogre::StringConverter::parseReal(xNode.getAttribute("mTerrainSizeY"));
		mTerrainSizeZ = Ogre::StringConverter::parseReal(xNode.getAttribute("mTerrainSizeZ"));
		mHeightmapFileName = xNode.getAttribute("mHeightmapFileName");
		mHeightmapHeight = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mHeightmapHeight"));
		mHeightmapWidth = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mHeightmapWidth"));
		mTerrainBrushImage = xNode.getAttribute("mTerrainBrushImage");
		mTerrainBrushWidth = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mTerrainBrushWidth"));
		mTerrainBrushHeight = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mTerrainBrushHeight"));
		mTerrainBrushIntensity = Ogre::StringConverter::parseReal(xNode.getAttribute("mTerrainBrushIntensity"));
		mSplatTextureName = xNode.getAttribute("mSplatTextureName");
		mSplatTextureHeight = Ogre::StringConverter::parseReal(xNode.getAttribute("mSplatTextureHeight"));
		mSplatTextureWidth = Ogre::StringConverter::parseReal(xNode.getAttribute("mSplatTextureWidth"));
		mMaxSplattingTextures = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mMaxSplattingTextures"));
		mCurrentSplattingTextures = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mCurrentSplattingTextures"));
		mChosenTexture = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mChosenTexture"));
		mPaintBrushImage = xNode.getAttribute("mPaintBrushImage");
		mPaintBrushWidth = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mPaintBrushWidth"));
		mPaintBrushHeight = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mPaintBrushHeight"));
		mPaintBrushIntensity = Ogre::StringConverter::parseReal(xNode.getAttribute("mPaintBrushIntensity"));
		mLightmapHeight = Ogre::StringConverter::parseReal(xNode.getAttribute("mLightmapHeight"));
		mLightmapWidth = Ogre::StringConverter::parseReal(xNode.getAttribute("mLightmapWidth"));
		mLODErrorMargin = Ogre::StringConverter::parseUnsignedInt(xNode.getAttribute("mLODErrorMargin"));
		mLODMorphing = Ogre::StringConverter::parseBool(xNode.getAttribute("mLODMorphing"));
		mLODMorphFactor = Ogre::StringConverter::parseReal(xNode.getAttribute("mLODMorphFactor"));
		mCursorMesh = xNode.getAttribute("mCursorMesh");

	} catch (...) {
		Ogre::LogManager::getSingleton().logMessage("*** Error loading Terrain data from Ape map file ***");
		return false;
	}

	return true;
}
