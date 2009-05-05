#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

#include "Ogre.h"
#include "GameObject.h"
//#include "Receiver.h"
#include "OgreRender.h"
#include "xmlParser.h"
#include "Physics.h"

class GameObject;
class OgreRender;
class Physics;

using namespace Ogre;

class ObjectManager : public Ogre::Singleton<ObjectManager>
{
	//Component interface
public:
	ObjectManager(); //Physics* physics,OgreRender* ogre
	~ObjectManager();

	static ObjectManager& getSingleton(void);
	static ObjectManager* getSingletonPtr(void);

	std::map<const std::string, GameObject*> getGOs();
	
	int numComponents;
	
	//void OnOgreRender_Created(OgreRender* ogre);

	GameObject* createCharacter(Ogre::String characterFileName);

	int getNextCompIndex();
	GameObject* getGO(const std::string &id);
	void deleteGO(const std::string &id);
	void reloadGO(std::string goName);
	GameObject* addObject(GameObject*);
	void clearGameObjects();
	void update();
	//void addCustomGO(std::string objName, bool isMesh,bool isLight,bool isRagdoll, std::string meshFileName, float xScale = 1.0f, float yScale = 1.0f, float zScale = 1.0f, float xPosition = 0.0f, float yPosition = 0.0f, float zPosition  = 0.0f);
	//void addCustomGO(std::string objName, bool isMesh,bool isLight, Ogre::Light::LightTypes lightType, std::string meshFileName, float xPosition, float yPosition, float zPosition);
	void addCustomGO();
	
	bool loadObjectsFromXML(XMLNode xMainNode);
	void loadDotSceneFile(std::string file);

	void initialize();

	GameObject* mMainCharacter;

private:
	
	OgreRender* mOgre;
	Physics* mPhysics;

	std::map<const std::string, GameObject*> mGOs; //Game objects collection
};

#endif
