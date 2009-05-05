#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "Ogre.h"
#include "ETTerrainManager.h"
#include "ETTerrainInfo.h"
#include "ETBrush.h"
#include "ETSplattingManager.h"
#include <vector>
#include "Decal.h"
#include "OgreRender.h"
#include "InputHandler.h"
#include "xmlParser.h"

using namespace Ogre;
using namespace ET;
using namespace std;

class ET::TerrainManager;
class ET::Brush;
class ET::TerrainInfo;
class InputHandler;
class ET::TerrainManager;
class OgreRender;

class EditableTerrain : public Ogre::Singleton<EditableTerrain> 
{
public: 

	EditableTerrain(); //OgreRender* ogre
	~EditableTerrain();

	static EditableTerrain& getSingleton(void);
	static EditableTerrain* getSingletonPtr(void);

	//void OnOgreRender_Created(OgreRender* ogre);
	//void OnInput_Created(InputHandler* input);
	

	void initialize();
	//void makeConnections();
	void registerParams();
	void init();
	void setup();
	void update();
	void destroy();
	bool loadSettings(XMLNode xNode);
	void resetParameters();
	void loadTerrain();
	void createETM();
	void generateTerrain();
	void updateLightmap();
	void setMapSize(Ogre::Vector3 mapSize);
	void updateBrush(const OIS::MouseEvent &evt); //Ogre::Real screenX,Ogre::Real screenY
	void paint();
	void removeTerrain();
	void setTerrainEditBrush(unsigned short size);
	void setPaintEditBrush(unsigned short size);
	void setTerrainEditBrushIntensity(float size);
	void setPaintEditBrushIntensity(float size);
	void addTexture(const std::string name);
	void removeTexture(const std::string name);
	void searchDiskForTextures();
	void mouseButtonDownNotification(bool controledByGui,unsigned int button);
	void mouseButtonUpNotification(bool controledByGui,unsigned int button);
	Ogre::Real getTerrainHeightAt(Real x,Real z);
	Ogre::Vector3 rayIntersectsTerrain();
	static ET::TerrainManager* getTerrainManager();
	void saveTerrain(std::string mFileName);
	bool saveToXML();

	static bool enablePainting;
	static bool riseTerrain;
	static bool paintTerrain;
	static bool smoothTerrain;
	static Ogre::SceneNode *mPointer;
	static std::string textureList[6];
	static DecalCursor *mPincelDecal;

private:
	OgreRender* mOgre;
	InputHandler* mInput;

	//signal1<bool> sig_TerrainCreated;

	static ET::TerrainManager* mTerrainMgr;
    static ET::SplattingManager* mSplatMgr;
	static const ET::TerrainInfo* mTerrainInfo;
	
	ET::Brush averageFilter(int x, int z, ET::Brush shape, float fIntensity);

	static Ogre::Image terrainBrushImage;
	static Ogre::Image paintBrushImage;
    static ET::Brush mEditBrush;
    static bool mDeform;
	
	Ogre::TexturePtr lightmapTex;
	
	bool mIsTerrainLoaded;

	//The size of the terrain to be rendered
	float mTerrainSizeX;
	float mTerrainSizeY;
	float mTerrainSizeZ;

	//The size of the heightmap image
	string mHeightmapFileName;
	unsigned int mHeightmapHeight;
	unsigned int mHeightmapWidth;

	string mTerrainBrushImage;
	ushort mTerrainBrushWidth;
	ushort mTerrainBrushHeight;
	float mTerrainBrushIntensity;

	//The size of the splatting textures
	string mSplatTextureName;
	float mSplatTextureHeight;
	float mSplatTextureWidth;
	unsigned int mMaxSplattingTextures;
	unsigned int mCurrentSplattingTextures;

	uint mChosenTexture;

	string mPaintBrushImage;
	ushort mPaintBrushWidth;
	ushort mPaintBrushHeight;
	float mPaintBrushIntensity;

	//The size of the lightmap
	float mLightmapHeight;
	float mLightmapWidth;

	unsigned int mLODErrorMargin;
	bool mLODMorphing;
	float mLODMorphFactor;
	string mCursorMesh ;
};

#endif