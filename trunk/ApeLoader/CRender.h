#ifndef _CRENDER_H_
#define _CRENDER_H_

#include "Ogre.h"

using namespace Ogre;

class GameComponent;

#include "ObjectManager.h"
#include "OgreRender.h"

class ObjectManager;
class OgreRender;

class CRender : public GameComponent {
public:

	Ogre::SceneNode *mNode;
	String mRenderName;
	String mParentZoneName;
	//bool mIsChild;
	String mTextureFileName;
	String mTextureTiling_U;
	String mTextureTiling_V;

	CRender(Ogre::String renderName,Ogre::String parentZoneName = "");
	
	~CRender();

	void setup();
	void update();
	Ogre::SceneNode* getNode();
	Ogre::String getNodeName();
	void setNode(Ogre::SceneNode* node);
	
	void updateMaterial(Ogre::Entity* ent, bool shadows = true);

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}

	GameComponent* makeComponent();

private:
	static std::string mFamilyID;
	static std::string mComponentID;
	

	ObjectManager* mObjMan;
	OgreRender* mOgre;

};

#endif
