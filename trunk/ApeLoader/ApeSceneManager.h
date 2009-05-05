#ifndef _APE_SCENE_H
#define _APE_SCENE_H

//#include "Caelum.h"
//#include "Receiver.h"
#include "OgreRender.h"
#include "xmlParser.h"

class OgreRender;

using namespace Ogre;

class ApeSceneManager : public Ogre::Singleton<ApeSceneManager> , public Ogre::SceneManager::Listener, public Ogre::WindowEventListener, public Ogre::CompositorInstance::Listener 
{
private:
	
	bool mIsLoaded;
	bool mManageLights;
	Real mTimeScale;
	Real mCloudsSpeed;
	Real mCloudsCover;
	Real mCloudsBendTime;
	ColourValue mAmbientLight;
	ColourValue mDiffuseLight;
	ColourValue mSpecularLight;
	ColourValue mBackgroundColour;
	Real mNearClip;
	Real mAspectRatio;
	Real mFarClip;
	Ogre::FogMode mFogType;
	Real mFogLineStart;
	Real mFogLineEnd;
	Real mFogDensity;
	ColourValue mFogColour;
	Ogre::ProjectionType mProjType;
	Radian mFOVy;
	Ogre::String mSkyMode;
	Ogre::String mSkyBoxName;
	Ogre::Real mSkyBoxDistance;
	Ogre::Vector3 mCamPos;
	Ogre::Real mCamVel;

	OgreRender* mOgre;
	//caelum::CaelumSystem *mCaelumSystem;

public:
	
	bool mUseZoneManager;
	bool mBlurCompositorFlag;

	//void OnOgreRender_Created(OgreRender* ogre);
	ApeSceneManager();
	~ApeSceneManager();

	static ApeSceneManager& getSingleton(void);
	static ApeSceneManager* getSingletonPtr(void);

	void initialize();
	void makeConnections();

	bool loadSettings(XMLNode xMainNode);
	void setupSkyBox();
	void destroySkyBox();
	void setupScene();
	
	//void saveAttrib();
	
	//void setAttribute(std::string name,std::string value);

	void setDefaultConfig();

	void createSky();
	void UpdateSun();

	//Under construction
	/*void setupCaelum(void);*/
	void destroySky(void);

	//void initShadow
	void initSoftShadows();

	//Soft shadows
	void shadowTextureCasterPreViewProj(Ogre::Light *light, Ogre::Camera *cam, size_t iteration);
	void shadowTexturesUpdated(size_t) {}
	void shadowTextureReceiverPreViewProj(Ogre::Light*, Ogre::Frustum*) {}
	void preFindVisibleObjects (Ogre::SceneManager *source, Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport *v) {}
	void postFindVisibleObjects (Ogre::SceneManager *source, Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport *v) {}

	//compositor
	virtual void notifyMaterialSetup(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat) {};
	virtual void notifyMaterialRender(Ogre::uint32 pass_id, Ogre::MaterialPtr &mat) {};

	// this tells us if the window closed (or alt-f4, for example)
	void windowClosed(Ogre::RenderWindow *window) {
		// stop running.  we don't compare any windows
		// since we only make 1 window anyways
		//running = false;
	}

};

#endif