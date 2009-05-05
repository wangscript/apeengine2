//Caelum
#include "ApeSceneManager.h"
#include "OgrePCZSceneManager.h"

template<> ApeSceneManager* Ogre::Singleton<ApeSceneManager>::ms_Singleton = 0;
ApeSceneManager* ApeSceneManager::getSingletonPtr(void)
{
	return ms_Singleton;
}
ApeSceneManager& ApeSceneManager::getSingleton(void)
{  
	//assert( ms_Singleton );
	return ( *ms_Singleton );  
}

ApeSceneManager::ApeSceneManager() :
						mIsLoaded(false),
						mManageLights(false),
						mTimeScale(0),
						mCloudsSpeed(0),
						mCloudsCover(0),
						mCloudsBendTime(0),
						mAmbientLight(ColourValue::ZERO),
						mDiffuseLight(ColourValue::ZERO),
						mSpecularLight(ColourValue::ZERO),
						mBackgroundColour(ColourValue::ZERO),
						mNearClip(0),
						mAspectRatio(0),
						mFarClip(0),
						mFogType(Ogre::FogMode::FOG_NONE),
						mFogLineStart(0),
						mFogLineEnd(0),
						mFogDensity(0),
						mFogColour(0),
						mProjType(Ogre::ProjectionType::PT_PERSPECTIVE),
						mFOVy(0),
						mSkyBoxDistance(0),
						mCamPos(Vector3::ZERO),
						mCamVel(0),
						mOgre(0)
						//mCaelumSystem(0)

{

	setDefaultConfig();

}

ApeSceneManager::~ApeSceneManager()
{
	
}
/*
void ApeScene::OnOgreRender_Created(OgreRender* ogre) {
	mOgre = ogre;
}
*/
void ApeSceneManager::initialize() {
	mOgre = OgreRender::getSingletonPtr();

}
void ApeSceneManager::makeConnections() {

}

void ApeSceneManager::UpdateSun()
{
    // Update the haze sun light position
    //if (mCaelumSystem->getSun ()) {
	   // Ogre::MaterialPtr mat = static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton ().getByName ("CaelumDemoTerrain"));
    //    assert(mat->getTechnique (0)->getPass ("CaelumHaze"));
	   // mat->getTechnique (0)->getPass ("CaelumHaze")->getVertexProgramParameters ()->setNamedConstant ("sunDirection", mCaelumSystem->getSun ()->getSunDirection ());
    //}
}

void ApeSceneManager::setDefaultConfig() {

	//Ogre::PCZSceneManager* mPZSM = (Ogre::PCZSceneManager*)mOgre->getSceneManager();
	//mPZSM->enableSky(true);

	mUseZoneManager = false;

	mIsLoaded = false;
	mAmbientLight = Ogre::ColourValue(0.5, 0.5, 0.5);
	mDiffuseLight = Ogre::ColourValue(3.0, 3.0, 2.7);
	mSpecularLight = Ogre::ColourValue(5.0, 5.0, 5.0);
	mManageLights = true;
	mCloudsSpeed = 0.000005;
	mCloudsCover = 0.5;
	mCloudsBendTime = 24;
	mTimeScale = 400;

	mBackgroundColour = Ogre::ColourValue(0.5, 0.5, 0.5);
	mNearClip = 1.0f;
	mAspectRatio = 1.33333f;
	mFarClip = 2000.0;

	mFogType = Ogre::FOG_NONE;
	mFogLineStart = 0.0f;
	mFogLineEnd = 0.0f;
	mFogDensity = 0.0f;
	mFogColour = Ogre::ColourValue(0.5, 0.5, 0.5);

	mProjType = Ogre::ProjectionType::PT_PERSPECTIVE;
	mFOVy = Radian(Degree(45));

	mSkyMode = "Skybox";
	mSkyBoxName = "";
	mSkyBoxDistance = 1000;
}

void ApeSceneManager::createSky() {
	//Setup Ogre viewport
	setupScene();

	//Setup Sky system
	if(mIsLoaded) {
		//if(mSkyMode == "Caelum")
			//setupCaelum();
		//else
			setupSkyBox();

		mIsLoaded = true;
	} 
}

void ApeSceneManager::setupSkyBox() {
	
	if(mSkyBoxName != "") {
		if(ApeSceneManager::getSingleton().mUseZoneManager) {
			
			Ogre::PCZSceneManager* mPCZSM = dynamic_cast<Ogre::PCZSceneManager*>(mOgre->getSceneManager());

			//Ogre::PCZSceneNode* mSkyNode = mPCZSM->getRootSceneNode()->createChildSceneNode("sky");// getDefaultZone()->creat ->_addNode()

			//mPCZSM->getDefaultZone()->_addNode(mSkyNode);
			
			mPCZSM->_setSkyBox(true, mSkyBoxName, mSkyBoxDistance);

			mPCZSM->enableSky(true);
			mPCZSM->setSkyZone(mPCZSM->getDefaultZone()); // getDefaultZone()->add
			
			
			
			//mPCZSM->setSkyBox(true, mSkyBoxName, mSkyBoxDistance);
		}
		else {
			mOgre->getSceneManager()->setSkyBox(true, mSkyBoxName, mSkyBoxDistance);
		}
		
	}
	
}
void ApeSceneManager::destroySkyBox() {
	if(mSkyBoxName != "") {
		if(ApeSceneManager::getSingleton().mUseZoneManager) {
			Ogre::PCZSceneManager* mPCZSM = dynamic_cast<Ogre::PCZSceneManager*>(mOgre->getSceneManager());
			//Ogre::PCZSceneNode* mSkyNode = mPCZSM->getRootSceneNode()->createChildSceneNode("sky");// getDefaultZone()->creat ->_addNode()
			//mPCZSM->getDefaultZone()->_addNode(mSkyNode);
			mPCZSM->enableSky(true);
			mPCZSM->setSkyZone(mPCZSM->getDefaultZone()); // getDefaultZone()->add
			mPCZSM->_setSkyBox(true, mSkyBoxName, mSkyBoxDistance);
			//mPCZSM->setSkyBox(true, mSkyBoxName, mSkyBoxDistance);
		} else {
			mOgre->getSceneManager()->setSkyBox(false, mSkyBoxName, mSkyBoxDistance);
		}
	}
}

void ApeSceneManager::setupScene() {
	/*
	Ogre::Overlay* crosshair = OverlayManager::getSingleton().getByName("Crosshair");
	crosshair->show();
	*/

//////////////////////////////////////////////////////////////////////////

	//create Overlays
	/*
	OverlayContainer *container = (OverlayContainer*) OverlayManager::getSingletonPtr()->createOverlayElement("Panel", "Crosshair/Container");
	container->setMaterialName("Core/CrosshairMat");
	container->setPosition(0, 0); 
	container->setMetricsMode(GuiMetricsMode::GMM_PIXELS);
	container->setHorizontalAlignment(GuiHorizontalAlignment::GHA_CENTER);
	container->setVerticalAlignment(GuiVerticalAlignment::GVA_CENTER);
	container->setHeight(50.0f);
	container->setWidth(50.0f);
	
	//container->show();
	
	Ogre::Overlay* mOverlay = OverlayManager::getSingletonPtr()->create("Crosshair/Overlay");
	mOverlay->setZOrder(600);
	mOverlay->add2D(container);
	mOverlay->show();
	*/

//////////////////////////////////////////////////////////////////////////

	mOgre->getSceneManager()->setAmbientLight(mAmbientLight);
	mOgre->getViewport()->setBackgroundColour(mBackgroundColour);
	mOgre->getCamera()->setNearClipDistance(mNearClip);
	mOgre->getCamera()->setFarClipDistance(mFarClip);
	mOgre->getCamera()->setAspectRatio(mAspectRatio);
	mOgre->getCamera()->setFOVy(mFOVy);
	mOgre->getCamera()->setProjectionType(mProjType);
	
//////////////////////////////////////////////////////////////////////////
	
	Ogre::SceneManager* sceneMgr;
	if(ApeSceneManager::getSingleton().mUseZoneManager)
		sceneMgr = dynamic_cast<Ogre::PCZSceneManager*>(mOgre->getSceneManager());
	else
		sceneMgr = mOgre->getSceneManager();

	/*
	sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	sceneMgr->setShadowFarDistance(475);
	sceneMgr->setShadowColour(ColourValue(0.7, 0.7, 0.7));
	*/
	
	//Removed
	//sceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
	//sceneMgr->setShadowTechnique(SHADOWTYPE_NONE);
	//sceneMgr->setShadowFarDistance(1500);
	//sceneMgr->setShadowColour(ColourValue(0.8, 0.8, 0.8));

	//sceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	//sceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
	//sceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);


	/*
	sceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);
	//sceneMgr->setShadowTechnique(SHADOWTYPE_NONE);
	sceneMgr->setShadowTextureSize(2048);
	sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	if (mOgre->getRoot()->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_HWRENDER_TO_TEXTURE))
	{
		sceneMgr->setShadowTextureSettings(2048, 2);
	}
	else
	{
		//Use 512x512 texture in GL since we can't go higher than the window res
		sceneMgr->setShadowTextureSettings(512, 2);
	}

	//Shadow camera setup
	Ogre::LiSPSMShadowCameraSetup * shadowCameraSetup = new Ogre::LiSPSMShadowCameraSetup();
	shadowCameraSetup->setOptimalAdjustFactor(50);

	sceneMgr->setShadowCameraSetup(Ogre::ShadowCameraSetupPtr(shadowCameraSetup));
	sceneMgr->setShadowFarDistance(50);
	sceneMgr->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5));
	sceneMgr->setShadowTexturePixelFormat(Ogre::PF_L8);
	sceneMgr->setShadowTextureCasterMaterial(Ogre::StringUtil::BLANK);
	sceneMgr->setShadowTextureReceiverMaterial(Ogre::StringUtil::BLANK);
	sceneMgr->setShadowTextureSelfShadow(false); 
*/
//////////////////////////////////////////////////////////////////////////

	//GameSceneManager::getSingleton()->getCamera()->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight())); 
	
	//CVelocity *obj_vel = dynamic_cast<CVelocity*>(GameObjectManager::getSingleton()->getGO("Camera")->getComponent("CVelocity"));
	//if(obj_vel)
	//	obj_vel->Velocity = sky_config.camVel;

	//mOgre->getCamera()->setPosition(mCamPos);

	//sky_config.ProjectionType = Ogre::ProjectionType::PT_ORTHOGRAPHIC;
	//sky_config.FOVy = Radian(Degree(45));

	//setFOVy()

	Ogre::FogMode fog_type;

	if(mFogType == 0)
		fog_type = Ogre::FOG_NONE;
		
	if(mFogType == 1)
		fog_type = Ogre::FOG_EXP;

	if(mFogType == 2)
		fog_type = Ogre::FOG_EXP2;

	if(mFogType == 3)
		fog_type = Ogre::FOG_LINEAR;

	
	initSoftShadows();

	mOgre->getSceneManager()->setFog(fog_type,mFogColour,mFogDensity,mFogLineStart,mFogLineEnd);

	//Compositor
	Ogre::CompositorManager::getSingleton().addCompositor(OgreRender::getSingleton().getViewport(), "Bloom", -1);
	mBlurCompositorFlag = false;
}

void ApeSceneManager::destroySky() {
	if(mIsLoaded) {
		//if(mSkyMode == "Caelum")
		//	mCaelumSystem->shutdown();
		//else
			destroySkyBox();
	}
}

bool ApeSceneManager::loadSettings(XMLNode xMainNode) {

	XMLNode xNode=xMainNode.getChildNode("Sky");

	try {
		mIsLoaded = Ogre::StringConverter::parseBool(xNode.getAttribute("isLoaded"));
		mAmbientLight.r = Ogre::StringConverter::parseReal(xNode.getAttribute("ambientLightRed"));
		mAmbientLight.g = Ogre::StringConverter::parseReal(xNode.getAttribute("ambientLightGreen"));
		mAmbientLight.b = Ogre::StringConverter::parseReal(xNode.getAttribute("ambientLightBlue"));
		mDiffuseLight.r = Ogre::StringConverter::parseReal(xNode.getAttribute("diffuseLightRed"));
		mDiffuseLight.g = Ogre::StringConverter::parseReal(xNode.getAttribute("diffuseLightGreen"));
		mDiffuseLight.b = Ogre::StringConverter::parseReal(xNode.getAttribute("diffuseLightBlue"));
		mSpecularLight.r = Ogre::StringConverter::parseReal(xNode.getAttribute("specularLightRed"));
		mSpecularLight.g = Ogre::StringConverter::parseReal(xNode.getAttribute("specularLightGreen"));
		mSpecularLight.b = Ogre::StringConverter::parseReal(xNode.getAttribute("specularLightBlue"));

		mManageLights = Ogre::StringConverter::parseReal(xNode.getAttribute("manageLights"));
		mCloudsSpeed = Ogre::StringConverter::parseReal(xNode.getAttribute("cloudsSpeed"));
		mCloudsCover = Ogre::StringConverter::parseReal(xNode.getAttribute("cloudsCover"));
		mCloudsBendTime = Ogre::StringConverter::parseReal(xNode.getAttribute("cloudsBendTime"));
		mTimeScale = Ogre::StringConverter::parseReal(xNode.getAttribute("timeScale"));
		mBackgroundColour = Ogre::StringConverter::parseColourValue(xNode.getAttribute("backgroundColour"));
		mNearClip = Ogre::StringConverter::parseReal(xNode.getAttribute("NearClip"));
		mAspectRatio = Ogre::StringConverter::parseReal(xNode.getAttribute("AspectRatio"));
		mFarClip = Ogre::StringConverter::parseReal(xNode.getAttribute("FarClip"));
		
		Ogre::String fogType = xNode.getAttribute("FogType");
		if(fogType == "FOG_NONE")
			mFogType = Ogre::FogMode::FOG_NONE;
		if(fogType == "FOG_EXP")
			mFogType = Ogre::FogMode::FOG_EXP;
		if(fogType == "FOG_EXP2")
			mFogType = Ogre::FogMode::FOG_EXP2;
		if(fogType == "FOG_LINEAR")
			mFogType = Ogre::FogMode::FOG_LINEAR;


		mFogLineStart = Ogre::StringConverter::parseReal(xNode.getAttribute("FogLineStart"));
		mFogLineEnd = Ogre::StringConverter::parseReal(xNode.getAttribute("FogLineEnd"));
		mFogDensity = Ogre::StringConverter::parseReal(xNode.getAttribute("FogDensity"));
		mFogColour = Ogre::StringConverter::parseColourValue(xNode.getAttribute("FogColour"));

		Ogre::String projType = xNode.getAttribute("ProjectionType");
		
		if(projType == "PERSPECTIVE")
			mProjType = Ogre::ProjectionType::PT_PERSPECTIVE;

		if(projType == "ORTHOGRAPHIC")
			mProjType = Ogre::ProjectionType::PT_ORTHOGRAPHIC;

		//mFarClip = Ogre::StringConverter::parseReal(xNode.getAttribute("ProjectionType"));
		mFOVy = Radian(Degree(Ogre::StringConverter::parseReal(xNode.getAttribute("FOVy"))));
		mSkyMode = xNode.getAttribute("SkyMode");
		mSkyBoxName = xNode.getAttribute("SkyBoxName");
		mSkyBoxDistance = Ogre::StringConverter::parseReal(xNode.getAttribute("SkyDistance"));

	} catch (...) {
		Ogre::LogManager::getSingleton().logMessage("*** Error loading ApeScene data from Ape map file ***");
		return false;
	}

	return true;
}

//Under construction
//void ApeSceneManager::setupCaelum(void)
//{	 
//
//	// Pick components to create in the demo.
//    // You can comment any of those and it should still work
//    // It makes little sense to comment the first three.
//    caelum::CaelumSystem::CaelumComponent componentMask = 
//            static_cast<caelum::CaelumSystem::CaelumComponent> (
//            caelum::CaelumSystem::CAELUM_COMPONENT_SKY_COLOUR_MODEL |
//            caelum::CaelumSystem::CAELUM_COMPONENT_SUN |
//            caelum::CaelumSystem::CAELUM_COMPONENT_SOLAR_SYSTEM_MODEL |
//            caelum::CaelumSystem::CAELUM_COMPONENT_SKY_DOME |
//            caelum::CaelumSystem::CAELUM_COMPONENT_STARFIELD |
//            caelum::CaelumSystem::CAELUM_COMPONENT_CLOUDS |
//            //caelum::CaelumSystem::CAELUM_COMPONENT_GROUND_FOG |
//            0);
//
//	// Initialise Caelum
//	mCaelumSystem = new caelum::CaelumSystem (mOgre->getRoot(),mOgre->getSceneManager(), componentMask); //mRoot
//
//    // KNOWN BUG: The horizon is pure white if setManageFog is false.
//    // I blame it on the transparent skydome.
//    mCaelumSystem->setManageSceneFog(true);
//    mCaelumSystem->setSceneFogDensityMultiplier(0.00015);
//
//	// Setup sun options
//    if (mCaelumSystem->getSun ()) {
//	    mCaelumSystem->getSun ()->setAmbientMultiplier (mAmbientLight);
//	    mCaelumSystem->getSun ()->setDiffuseMultiplier (mDiffuseLight);
//	    // For green terrain:
//	    //mCaelumSystem->getSun ()->setDiffuseMultiplier (Ogre::ColourValue(0.1, 3, 0.1));
//	    mCaelumSystem->getSun ()->setSpecularMultiplier (mSpecularLight);
//	    mCaelumSystem->getSun ()->setManageAmbientLight (mManageLights);
//    }
//
//    // Setup fog options.
//    if (mCaelumSystem->getGroundFog()) {
//        mCaelumSystem->getGroundFog()->findFogPassesByName();
//    }
//
//    // Setup cloud options.
//    // Tweak these settings to make the demo look pretty.
//    if (mCaelumSystem->getClouds ()) {
//        mCaelumSystem->getClouds ()->setCloudSpeed(Ogre::Vector2(mCloudsSpeed, -0.000009));
//        mCaelumSystem->getClouds ()->setCloudBlendTime(3600 * mCloudsBendTime);	
//        mCaelumSystem->getClouds ()->setCloudCover(mCloudsCover);
//    }
//
//	// Setup starfield options
//    if (mCaelumSystem->getStarfield ()) {
//	    mCaelumSystem->getStarfield ()->setInclination (Degree (13));
//    }
//
//	// Set time acceleration.
//	mCaelumSystem->getUniversalClock ()->setTimeScale(mTimeScale);
//
//    // Winter dawn in the southern hemisphere, looking north
//	mCaelumSystem->getUniversalClock ()->setGregorianDateTime (2008, 7, 4, 20, 33, 0);
//    mCaelumSystem->getSolarSystemModel ()->setObserverLongitude (Ogre::Degree(151 + 12.0 / 60));
//
//    // Sidney
//    mCaelumSystem->getSolarSystemModel ()->setObserverLatitude (Ogre::Degree(-33 + 52.0 / 60));
//    // Beyond the southern polar circle, no sunrise
//    //mCaelumSystem->getSolarSystemModel ()->setObserverLatitude (Ogre::Degree(-70));
//    // Beyond the northern polar circle, no sunset
//    //mCaelumSystem->getSolarSystemModel ()->setObserverLatitude (Ogre::Degree(70));
//
//	// Register caelum to the render target
//	mOgre->getWindow()->addListener(mCaelumSystem);
//
//	//std::string terrain_cfg("CaelumDemoTerrain.cfg");
//	//std::string terrain_cfg("Terrain2.cfg");
//	//mSceneMgr->setWorldGeometry (terrain_cfg);
//
//}

void ApeSceneManager::shadowTextureCasterPreViewProj(Ogre::Light *light, Ogre::Camera *cam, size_t iteration) {
	// basically, here we do some forceful camera near/far clip attenuation
	// yeah.  simplistic, but it works nicely.  this is the function I was talking
	// about you ignoring above in the Mgr declaration.
	float range = light->getAttenuationRange();
	cam->setNearClipDistance(range * 0.01);
	cam->setFarClipDistance(range);
	// we just use a small near clip so that the light doesn't "miss" anything
	// that can shadow stuff.  and the far clip is equal to the lights' range.
	// (thus, if the light only covers 15 units of objects, it can only
	// shadow 15 units - the rest of it should be attenuated away, and not rendered)
}
void ApeSceneManager::initSoftShadows() {
	OgreRender::getSingleton().getSceneManager()->setShadowTextureSelfShadow(true);

	// our caster material
	OgreRender::getSingleton().getSceneManager()->setShadowTextureCasterMaterial("shadow_caster");
	// note we have no "receiver".  all the "receivers" are integrated.

	// get the shadow texture count from the cfg file
	//std::string tempData = mgr.cfgFile.getSetting("shadowTextureCount", "renderer");
	// (each light needs a shadow texture)
	OgreRender::getSingleton().getSceneManager()->setShadowTextureCount(4);

	// the size, too (1024 looks good with 3x3 or more filtering)
	//tempData = mgr.cfgFile.getSetting("shadowTextureRes", "renderer");
	OgreRender::getSingleton().getSceneManager()->setShadowTextureSize(512); //512

	OgreRender::getSingleton().getSceneManager()->setShadowFarDistance(475);

	// float 16 here.  we need the R and G channels.
	// float 32 works a lot better with a low/none VSM epsilon (wait till the shaders)
	// but float 16 is "good enough" and supports bilinear filtering on a lot of cards
	// (note we're using floats and not bytes.  bytes, 0-255, won't be
	// able to store our depth data accurately enough.  technically,
	// we can "split" the floats into multiple bytes ourselves, but it's
	// rather "complicated", to put it simply)
	OgreRender::getSingleton().getSceneManager()->setShadowTexturePixelFormat(Ogre::PF_FLOAT16_RGB);

	// big NONO to render back faces for VSM.  it doesn't need any biasing
	// so it's worthless (and rather problematic) to use the back face hack that
	// works so well for normal depth shadow mapping (you know, so you don't
	// get surface acne)
	OgreRender::getSingleton().getSceneManager()->setShadowCasterRenderBackFaces(false);

	const unsigned numShadowRTTs = OgreRender::getSingleton().getSceneManager()->getShadowTextureCount();
	for (unsigned i = 0; i < numShadowRTTs; ++i) {
		Ogre::TexturePtr tex = OgreRender::getSingleton().getSceneManager()->getShadowTexture(i);
		Ogre::Viewport *vp = tex->getBuffer()->getRenderTarget()->getViewport(0);
		vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1, 1));
		vp->setClearEveryFrame(true);
		//Ogre::CompositorManager::getSingleton().addCompositor(vp, "blur");
		//Ogre::CompositorManager::getSingleton().setCompositorEnabled(vp, "blur", true);
	}

	// enable integrated additive shadows
	// actually, since we render the shadow map ourselves, it doesn't
	// really matter whether they are additive or modulative
	// as long as they are integrated v(O_o)v
	OgreRender::getSingleton().getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);


}
