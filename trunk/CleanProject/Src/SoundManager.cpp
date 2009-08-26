#include "SoundManager.h"

template<> Nebula::SoundManager* Ogre::Singleton<Nebula::SoundManager>::ms_Singleton = 0;

namespace Nebula {

	SoundManager* SoundManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}
	SoundManager& SoundManager::getSingleton(void)
	{  
		//return ( *ms_Singleton );  
		assert( ms_Singleton );  
		return ( *ms_Singleton );  
	}

	SoundManager::SoundManager() : mEngine(0)
	{
		initialize();
	}
	SoundManager::~SoundManager() {
	
	}
	
	//ISoundSource* SoundManager::createSound(const unsigned int soundFX,const std::string path) {
	//	mSoundList[path] = getManager()->addSoundSourceFromFile(path.c_str());
	//}

	void SoundManager::createSingleSound(const unsigned int soundFX,const std::string path,const Vector3,const bool isAmbient) {
		//mSoundList[path] = getManager()->addSoundSourceFromFile(path.c_str());

		if(!mSoundList.empty()) {
			if(mSoundList[path].soundSource)
				return;
		}

		//path,soundFX,isAmbient
		CustomSound sound; // = CustomSound();
		sound.soundPath = path;
		sound.soundSource = getManager()->addSoundSourceFromFile(path.c_str(),irrklang::ESM_AUTO_DETECT);
		sound.currentFX = soundFX;
		sound.isAmbient = isAmbient;
		
		bool fx = false;
		if(soundFX != 0)
			fx = true;
		
		sound.sound = 0;
		if(fx) {
			sound.sound = getManager()->play2D(sound.soundSource,isAmbient,false,false,fx);
			getManager()->stopAllSounds();
		}

		mSoundList[path] = sound;
		
		
		//return mSoundList[path];
	}

	void SoundManager::play(const std::string path) {
		//irrklang::ISoundSource* soundSource = mSoundList[path].soundSource;
		
			
		bool fx = false;

		irrklang::ISound* soundSource = 0;
		if(mSoundList[path].sound) {
			soundSource = mSoundList[path].sound;

			if(mSoundList[path].currentFX == 1) {
				mSoundList[path].fx = 0;				
				if (soundSource)
					mSoundList[path].fx = soundSource->getSoundEffectControl();

				if (!mSoundList[path].fx)
				{
					// some sound devices do not support sound effects.
					//printf("This device or sound does not support sound effects.\n");
					//continue;
				} else {
					if (!mSoundList[path].fx->isWavesReverbSoundEffectEnabled()) {
						mSoundList[path].fx->enableWavesReverbSoundEffect(0,-15,300,0.0);
						fx = true;
					}

				}	
			}
		}

		if(soundSource) {
			//mSoundList[path].isAmbient;
			
			//if(mSoundList[path].isAmbient)
			//	fx = false;

			getManager()->play2D(mSoundList[path].soundSource,mSoundList[path].isAmbient,false,false,fx); //,pos

			//SoundManager::getSingleton().getManager()->play2D(ambientSoundFileName1.c_str(),true, false, true, ESM_AUTO_DETECT, true);

		}
	}

	//void SoundManager::play3D(const std::string path) {
	//	
	//}

	void SoundManager::setBindings() {
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

	bool SoundManager::start() {
		
		//setBindings();
		return true;
	}
	void SoundManager::onSuspend() {
		
	}
	void SoundManager::update() {
		
	}
	void SoundManager::onResume() {
		
	}

	void SoundManager::stop() {

	}
	
	void SoundManager::updateSoundObjects() {

	}

	//Initialize Ogre API
	bool SoundManager::initialize() {
		mEngine = irrklang::createIrrKlangDevice();

		if (!mEngine)
			return 0; // error starting up the engine
		
		//mEngine->setListenerPosition(vec3df(0,0,0), vec3df(0,0,1));
		
		return true;
	}

	irrklang::ISoundEngine* SoundManager::getManager() {
		
		return mEngine;
	}

	void SoundManager::update(Ogre::Real time) {
		Ogre::Vector3 p = OgreManager::getSingleton().getCamera()->getDerivedPosition();
		irrklang::vec3df pos = irrklang::vec3df(p.x,p.y,p.z);

		Ogre::Vector3 d = OgreManager::getSingleton().getCamera()->getDerivedDirection();
		//vec3df dir = vec3df(d.x,d.y,d.z);
		irrklang::vec3df dir = irrklang::vec3df(0,0,-1);

		pos.Y = 0;
		pos.Z = 0;

		mEngine->setListenerPosition(pos, dir);

	}

} //end namespace