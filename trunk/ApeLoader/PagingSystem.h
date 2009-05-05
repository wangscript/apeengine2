#ifndef _PAGED_GEOMETRY_H
#define _PAGED_GEOMETRY_H

//Include PagedGeometry headers that will be needed
#include "PagedGeometry.h"
#include "GrassLoader.h"
#include "BatchPage.h"
#include "ImpostorPage.h"
#include "TreeLoader2D.h"
#include "EditableTerrain.h"
#include "Ogre.h"
#include "xmlParser.h"

//#include "GameSceneManager.h"

using namespace Ogre;
using namespace Forests;

//class PagedGeometry;
//class GrassLoader;
class TerrainSystem;
/*
struct Paging_Config {
	bool initialized;

	bool paintMode;
	bool eraseMode;

	std::string selectedTreeMesh;
	std::string selectedGrassImg;
	std::string selectedPagedTrees;
	std::string selectedPagedGrass;
	
	Real brushHeight;
	Real brushWidth;

};

extern Paging_Config PagingConfig;
*/

class PagedObjects {
public:
	PagedObjects();
	~PagedObjects();

	std::string name;
	std::string meshName;
	bool isTree;
	std::string entityName;
	Real pageSize;
	Real batchDistance;
	Real batchFade;
	Real impostorDist;
	Real impostorFade;
	unsigned int quantity;
	Real minScale;
	Real maxScale;
	TBounds pageBounds;
	Entity *entity;
	PagedGeometry *geometry;
	TreeLoader2D *treeLoader;
	Vector3 position;
	//Grass properties (i will change this, will have its own grass "type")
	bool isGrass;
	GrassLoader *grassLoader;
	GrassLayer *grassLayer;
	std::string materialName;
	bool animated;
	Real swayLenght;
	Real swaySpeed;
	Real density;
	GrassTechnique grt;
	FadeTechnique ft;
};
extern std::map<std::string,PagedObjects*> mFoliage;

class PagingSystem : public Ogre::Singleton<PagingSystem> 
{
public:
	PagingSystem();
	~PagingSystem();
	
	static PagingSystem& getSingleton(void);
	static PagingSystem* getSingletonPtr(void);

	//void load();	//Loads the 3D scene
	void unload();	//Unloads the 3D scene cleanly
	void update();		//Runs the simulation
	void initialize();

	void removeAllPagedObjects();
	
	bool loadSettings(XMLNode xMainNode);

	//void loadGameObjectsToXML(TiXmlElement* mElem);
	//void saveGameObjectsToXML(TiXmlElement* mElem);
	void updateTreeBrush();
	void treeBrush();
	void setBrushSize(Real size);

	//void addResources();

	void addSingleTreePage(std::string pageName,Vector3 pos);
	void removePagedObject(std::string name);
	void randomizeTreePage(std::string name);
	PagedGeometry* addTreePage(std::string name,Real pageSize,Real batchDistance, Real batchFade, Real impostorDist, Real impostorFade, std::string meshName, unsigned int quantity, Real minScale, Real maxScale);
	PagedGeometry* addGrassPage(std::string name,Real pageSize,Real batchDistance, std::string materialName, Real minScale, Real maxScale, bool animated, Real swayLenght, Real swaySpeed, Real density, GrassTechnique grt, FadeTechnique ft);

	//Return collection of foliage objects, contains ALL paged geometry.
	std::map<std::string,PagedObjects*> getFoliage();
	PagedObjects* PagingSystem::getFoliageByName(std::string name);

private:
	void render();			//Renders a single frame, updating PagedGeometry and Ogre

	//std::map<std::string,PagedObjects*> mFoliage;

	static bool running;	//A flag which, when set to false, will terminate a simulation started with run()

	//Various pointers to Ogre objects are stored here:
	Root *root;
	RenderWindow *window;
	Viewport *viewport;
	SceneManager *sceneMgr;
	Camera *camera;

	//Variables used to keep track of the camera's rotation/etc.
	Radian camPitch, camYaw;

	//Pointers to PagedGeometry class instances:
	//PagedGeometry *trees, *grass, *bushes;
	//GrassLoader *grassLoader;
};

#endif