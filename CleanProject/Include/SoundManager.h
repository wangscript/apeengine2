/*!
	@file
	@author		Pablo Nuñez
	@date		13/2009
	@module
*//*
	This file is part of the Nebula Engine.
	
	Nebula Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Nebula Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Nebula Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

//#include "Ogre.h"
//#include "OgreOggSound.h"

#include "EnginePrerequisites.h"



using namespace Ogre;
//using namespace OgreOggSound;
namespace Nebula {

	class ISoundSource;
	class ISoundEffectControl;

	//enum NebulaDllPrivate SoundFX
	//{
	//	NONE = 0,
	//	REVERB = 1,
	//	DELAY = 2
	//};

	struct NebulaDllPrivate CustomSound
	{
		CustomSound() //const std::string path,const unsigned int fx, bool ambient
		{
			//soundPath = path;
			//currentFX = fx;
			//isAmbient = ambient;
			soundSource = 0;
			sound = 0;
			fx = 0;
		}

		std::string soundPath;
		irrklang::ISoundSource* soundSource;
		irrklang::ISound* sound;
		unsigned int currentFX;
		bool isAmbient;
		irrklang::ISoundEffectControl* fx;

		//float rotationSpeed;
	};

	class NebulaDllPrivate SoundManager : public Ogre::Singleton<SoundManager>, 
										  public ITask
	{
	public:

		SoundManager(); 
		~SoundManager();

		static SoundManager& getSingleton(void);
		static SoundManager* getSingletonPtr(void);
		
		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();

		//void test();
		bool initialize();
		void update(Ogre::Real time);
		void updateSoundObjects();

		irrklang::ISoundEngine* getManager();
		
		//ISoundSource* createSound2D(const unsigned int soundFX,const std::string path);
		void createSingleSound(const unsigned int soundFX,const std::string path,const Vector3,const bool isAmbient);
		void play(const std::string path);
		//void play3D(const std::string path);

	private:
		//OgreOggISound* newSound;
		
		std::map<const std::string,CustomSound> mSoundList;

		irrklang::ISoundEngine* mEngine;

		//irrklang::ISoundEffectControl* mFx;

		//Set Lua bindings
		void setBindings();

		
		//OgreOggSoundManager *mSoundManager;
	};

} //end namespace

#endif
