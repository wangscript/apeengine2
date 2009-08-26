#include "VideoManager.h"

template<> Nebula::VideoManager* Ogre::Singleton<Nebula::VideoManager>::ms_Singleton = 0;

#define VIDEO_FILE "konqi.ogg"


#define EVENT(wnd_name,function) \
	CEGUI::WindowManager::getSingleton().getWindow(wnd_name)->subscribeEvent( \
	CEGUI::PushButton::EventClicked, \
	CEGUI::Event::Subscriber(&function,this));

#define EVENT_EX(wnd_name,function,type) \
	CEGUI::WindowManager::getSingleton().getWindow(wnd_name)->subscribeEvent( \
	type, CEGUI::Event::Subscriber(&function,this));

namespace Nebula {

	VideoManager::VideoManager()
	{
	
	}
	VideoManager::~VideoManager()
	{

	}
	
	void VideoManager::setBindings() {
		//lua_State* lua = LuaStateManager::getSingleton().getState();
		//module( lua )
		//	[
		//		class_< GuiManager >( "GuiManager" )
		//		.def("setWallpaper", (void(GuiManager::*)(const std::string&))&GuiManager::setWallpaper )
		//		.def( "getSingleton", &GuiManager::getSingleton ) // like this
		//	];

		//   getConsole()->registerConsoleDelegate("GuiManager", MyGUI::newDelegate(this, &GuiManager::command));
		////getConsole()->registerConsoleDelegate("GuiManager:", MyGUI::newDelegate(this, &GuiManager::command));
		//getConsole()->registerConsoleDelegate("GuiManager:setWallpaper", MyGUI::newDelegate(this, &GuiManager::command));

		//object global_vars = globals(lua);
		//global_vars["GuiManager"] = &GuiManager::getSingleton(); 
	}

	void VideoManager::createQuad(String name,String material_name,float left,float top,float right,float bottom)
	{
		ManualObject* model = OgreManager::getSingleton().getSceneManager()->createManualObject(name);
		model->begin(material_name);

		model->position(right,bottom,0); model->textureCoord(1,1);
		model->position(right,top   ,0); model->textureCoord(1,0);
		model->position(left ,top   ,0); model->textureCoord(0,0);
		model->position(left ,top   ,0); model->textureCoord(0,0);
		model->position(right,bottom,0); model->textureCoord(1,1);
		model->position(left, bottom,0); model->textureCoord(0,1);

		model->end();
		// make the model 2D
		model->setUseIdentityProjection(true);
		model->setUseIdentityView(true);
		// and atach it to the root node
		SceneNode* node = OgreManager::getSingleton().getSceneManager()->getRootSceneNode()->createChildSceneNode();
		node->attachObject(model);
	}

	bool VideoManager::start()
	{
		//setBindings();

		OgreManager::getSingleton().getCamera()->lookAt(Vector3(0,0,-300));
		OgreManager::getSingleton().getCamera()->setNearClipDistance(5);

		mhWnd = OgreManager::getSingletonPtr()->getWindowHandler();

		if(mhWnd ==0)
			return false;

		OIS::ParamList pl;
		pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(mhWnd)));

		mInputManager = OIS::InputManager::createInputSystem( pl );
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true));

		mMouse->setEventCallback(this);
		mKeyboard->setEventCallback(this);


		mGUIRenderer = new CEGUI::OgreCEGUIRenderer(OgreManager::getSingleton().getWindow(),Ogre::RENDER_QUEUE_OVERLAY, false, 3000, OgreManager::getSingleton().getSceneManager());
		mGUISystem = new CEGUI::System(mGUIRenderer);
		CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);
		// load scheme and set up defaults
		CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");
		mGUISystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
		mGUISystem->setDefaultFont((CEGUI::utf8*)"BlueHighway-10");


		CEGUI::Window* sheet = CEGUI::WindowManager::getSingleton().loadWindowLayout((CEGUI::utf8*)"SimpleDemo.layout"); 
		CEGUI::System::getSingleton().setGUISheet(sheet);

		//EVENT("rgb_button",DemoApp::OnRGB); 
		//EVENT("yuv_button",DemoApp::OnYUV); 
		//EVENT("grey_button",DemoApp::OnGrey);
		//EVENT("shaders_button",DemoApp::OnShaders); 
		EVENT("Play/Pause",VideoManager::OnPlayPause);
		EVENT_EX("seeker",VideoManager::OnSeekStart,CEGUI::Scrollbar::EventThumbTrackStarted);
		EVENT_EX("seeker",VideoManager::OnSeekEnd,CEGUI::Scrollbar::EventThumbTrackEnded);

		createQuad("video_quad","video_material",-0.5,1,1,-0.94);

		TheoraVideoManager* mgr=TheoraVideoManager::getSingletonPtr();

		mgr->setInputName(VIDEO_FILE);
		mgr->createDefinedTexture("video_material");


		//dshowMovieTextureSystem = new OgreUtils::DirectShowMovieTexture(640, 480);


		//Ogre::String movieName="D:\Devel\#PROJECTS\Ogre\CleanProject\CleanProject\Media\Textures\1.avi");

		//dshowMovieTextureSystem->loadMovie(movieName);
		//dshowMovieTextureSystem->playMovie();
		////dshowMovieTextureSystem->pauseMovie();
		////dshowMovieTextureSystem->stopMovie();
		////dshowMovieTextureSystem->rewindMovie();


		//bool isPlaying=dshowMovieTextureSystem->isPlayingMovie();

		//dshowMovieTextureSystem->updateMovieTexture();


		//createQuad("video_quad","video_material",-0.5,1,1,-0.94);

		//TheoraVideoManager* mgr=TheoraVideoManager::getSingletonPtr();

		//mgr->setInputName(VIDEO_FILE);
		//mgr->createDefinedTexture("video_material");

		

		//createQuad("video_quad","video_material",-0.5,1,1,-0.94);
		//
		//OgreManager::getSingleton().getCamera()->lookAt(Vector3(0,0,-300));
		//OgreManager::getSingleton().getCamera()->setNearClipDistance(5);
		//
		//mTheoraManager = TheoraVideoManager::getSingletonPtr();

		//mTheoraManager->setInputName("konqi.ogg");
		//mTheoraManager->createDefinedTexture("video_material");
		//mSeeking = true;
		//
		//TheoraVideoClip* tmpClip= mTheoraManager->getVideoClipByName("konqi.ogg");
		//tmpClip->load("konqi.ogg",);
		//tmpClip->play();

		//
		//MaterialPtr mat=MaterialManager::getSingleton().getByName("video_material");
		//Pass* pass=mat->getTechnique(0)->getPass(0);

		////wnd->setText("Shader yuv2rgb = on");
		////pass->setFragmentProgram("TheoraVideoPlugin/yuv2rgb");

		//tmpClip->setOutputMode(TH_RGB);

		//tmpClip->play();

		return true;
	}
	TheoraVideoClip* VideoManager::getClip(String name)
	{
		TheoraVideoManager* mgr = TheoraVideoManager::getSingletonPtr();
		return mgr->getVideoClipByName("konqi.ogg");
	}

	bool VideoManager::OnSeekStart(const CEGUI::EventArgs& e)
	{
		if (!mPaused) 
			getClip(VIDEO_FILE)->pause();
		mSeeking=true;
		return true;
	}
	bool VideoManager::OnSeekEnd(const CEGUI::EventArgs& e)
	{
		if (!mPaused) 
			getClip(VIDEO_FILE)->play();
		mSeeking=false;
		return true;
	}

	bool VideoManager::OnPlayPause(const CEGUI::EventArgs& e)
	{
		TheoraVideoClip* clip=getClip(VIDEO_FILE);

		if (!clip->isPaused())
		{
			mPaused=1;
			clip->pause();
		}
		else
		{
			mPaused=0;
			clip->play();
		}
		return true;
	}
	void VideoManager::onSuspend()
	{

	}

	void VideoManager::update()
	{
		//OgreManager::getSingleton().getRoot()->_fireFrameStarted();
		//OgreManager::getSingleton().getRoot()->
		
		TheoraVideoManager* mgr = TheoraVideoManager::getSingletonPtr();

		Ogre::FrameEvent fe;
		fe.timeSinceLastEvent = OgreManager::getSingleton().getTimeSinceLastFrame();
		fe.timeSinceLastFrame = OgreManager::getSingleton().getTimeSinceLastFrame();

		mgr->frameStarted(fe);

		mKeyboard->capture();
		mMouse->capture();

		CEGUI::Window* wnd=CEGUI::WindowManager::getSingleton().getWindow("cFrame");
		
		TheoraVideoClip* clip=mgr->getVideoClipByName(VIDEO_FILE);
		float dur=clip->getDuration();
		String s=StringConverter::toString(dur);
		String s2=StringConverter::toString(clip->getTimePosition(),4);
		wnd->setText("duration: "+s+" seconds");
		CEGUI::WindowManager::getSingleton().getWindow("droppedFrames")->setText("time position: "+s2+" seconds");

		String np=StringConverter::toString(clip->getNumPrecachedFrames());
		CEGUI::WindowManager::getSingleton().getWindow("precached")->setText("Precached: "+np);


		float cTime=clip->getTimePosition();
		float duration=clip->getDuration();
		int pos=1024*(cTime/duration);

		if (!mSeeking)
		{
			CEGUI::Window* wnd2=CEGUI::WindowManager::getSingleton().getWindow("seeker");
			wnd2->setProperty("ScrollPosition",StringConverter::toString(pos));
		}
		else
		{
			CEGUI::Window* wnd=CEGUI::WindowManager::getSingleton().getWindow("seeker");
			TheoraVideoClip* clip=getClip(VIDEO_FILE);
			float dur=clip->getDuration();

			CEGUI::String prop=wnd->getProperty("ScrollPosition");
			int step=StringConverter::parseInt(prop.c_str());
			if (abs(step-mSeekStep) > 10)
			{
				mSeekStep=step;
				float seek_time=((float) step/1024)*dur;

				clip->seek(seek_time);
			}
		}

		//dshowMovieTextureSystem->updateMovieTexture();


		//TheoraVideoClip* tmpClip= mTheoraManager->getVideoClipByName("konqi.ogg");
		//tmpClip->play();
		//CEGUI::Window* wnd=CEGUI::WindowManager::getSingleton().getWindow("cFrame");
		//mTheoraManager = TheoraVideoManager::getSingletonPtr();
		//TheoraVideoClip* tmpClip= mTheoraManager->getVideoClipByName("konqi.ogg");
		//float dur=clip->getDuration();
		//String s=StringConverter::toString(dur);
		//String s2=StringConverter::toString(clip->getTimePosition(),4);
		//wnd->setText("duration: "+s+" seconds");
		//CEGUI::WindowManager::getSingleton().getWindow("droppedFrames")->setText("time position: "+s2+" seconds");

		//String np=StringConverter::toString(clip->getNumPrecachedFrames());
		//CEGUI::WindowManager::getSingleton().getWindow("precached")->setText("Precached: "+np);


		//float cTime=tmpClip->getTimePosition();
		//float duration=tmpClip->getDuration();
		//int pos=1024*(cTime/duration);

		//if (!mSeeking)
		//{
			//CEGUI::Window* wnd2=CEGUI::WindowManager::getSingleton().getWindow("seeker");
			//wnd2->setProperty("ScrollPosition",StringConverter::toString(pos));
		//}
		//else
		//{
			//CEGUI::Window* wnd=CEGUI::WindowManager::getSingleton().getWindow("seeker");
			//TheoraVideoClip* tmpClip=mTheoraManager-> getClip("konqi.ogg");
			//float dur=tmpClip->getDuration();

			//CEGUI::String prop=wnd->getProperty("ScrollPosition");
			//int step=StringConverter::parseInt(prop.c_str());
			//if (abs(step-mSeekStep) > 10)
			//{
				//mSeekStep=step;
				//float t = OgreManager::getSingleton().getTimeSinceLastFrame();
				//float seek_time=(t / 1024) * dur;
				//tmpClip->seek(seek_time);

			//}
		//}


	}

	void VideoManager::onResume()
	{

	}

	void VideoManager::stop()
	{

	}
	VideoManager* VideoManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}

	VideoManager& VideoManager::getSingleton(void)
	{
		assert( ms_Singleton );  
		return ( *ms_Singleton );
	}

	bool VideoManager::mouseMoved( const OIS::MouseEvent &arg )
	{
		CEGUI::System::getSingleton().injectMouseMove( arg.state.X.rel, arg.state.Y.rel );
		return true;
	}

	CEGUI::MouseButton convertOISMouseButtonToCegui(int buttonID)
	{
		switch (buttonID)
		{
		case 0: return CEGUI::LeftButton;
		case 1: return CEGUI::RightButton;
		case 2:	return CEGUI::MiddleButton;
		case 3: return CEGUI::X1Button;
		default: return CEGUI::LeftButton;
		}
	}

	bool VideoManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		CEGUI::System::getSingleton().injectMouseButtonDown(convertOISMouseButtonToCegui(id));
		return true;
	}

	bool VideoManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		CEGUI::System::getSingleton().injectMouseButtonUp(convertOISMouseButtonToCegui(id));
		return true;
	}

	bool VideoManager::keyPressed( const OIS::KeyEvent &arg )
	{
		//if( arg.key == OIS::KC_ESCAPE ) 
		//	mShutdownRequested = true;
		CEGUI::System::getSingleton().injectKeyDown( arg.key );
		CEGUI::System::getSingleton().injectChar( arg.text );
		return true;
	}

	bool VideoManager::keyReleased( const OIS::KeyEvent &arg )
	{
		CEGUI::System::getSingleton().injectKeyUp( arg.key );
		return true;
	}

} //end namespace
