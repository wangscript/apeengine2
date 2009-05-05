#include "CSound.h"

/*static*/ 
const std::string CSound::mFamilyID = "CSound";
const std::string CSound::mComponentID = "CSound";

CSound::CSound()
{

}
CSound::CSound(std::string soundType, std::string soundSize, std::string soundName) {

	//
	//if(soundFileName = "stone")
	//	mSoundList[soundFileName] = "";

	//mSoundCategory = soundType;

	//mSoundType = soundType;
	//mSoundFileName = "";
	
	
	if(soundType == "predefined") {
		
		//mSoundCategory = soundName;
		//mSoundSize = soundSize;
		mSoundCategory = soundName;

		//"../../Media/Sounds/"
		Ogre::String soundFileName = Ogre::String("../../Media/Sounds/") + "phy_" + mSoundCategory + "_" + soundSize.substr(0,1) + "_" + "02" + ".ogg";
		
		//ISoundSource* s;
		//s->
		
		ISoundSource* sound = SoundManager::getSingleton().getManager()->addSoundSourceFromFile(soundFileName.c_str());
		

		//ISound* sound = SoundManager::getSingleton().getManager()->play3D
		//	(soundFileName.c_str(),vec3df(0,0,0), true, false, true);

		std::list<ISoundSource*> soundList;
		soundList.push_back(sound);
		mSoundList[soundName] = soundList;

	} else {
		mSoundCategory = "custom";
		//mSoundFileName = soundName;
		std::string soundFileName = "../../Media/Sounds/" + soundName;

		std::list<ISoundSource*> soundList;
		
		ISoundSource* sound = SoundManager::getSingleton().getManager()->addSoundSourceFromFile(soundFileName.c_str());

		//ISound* sound = SoundManager::getSingleton().getManager()->play3D
		//	(soundFileName.c_str(),vec3df(0,0,0), true, false, true);

		soundList.push_back(sound);

		mSoundList[soundName] = soundList;

	}


}

CSound::~CSound()
{

}

void CSound::update() {

}

void CSound::setup() {

	//ApeSound* walkSound_grass = new ApeSound();
	//walkSound_grass->addSound("WalkSound1","fst_grass_01.ogg",400,"MainNode");
	//walkSound_grass->addSound("WalkSound2","fst_grass_02.ogg",400,"MainNode");
	
	mCurrentSoundIndex = 0;

	CCharacter* mCChar = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));
	if(mCChar) {


		//std::list<std::string> grassSoundList;
		
		mCurrentSoundIndex = 1;

		std::string path = "../../Media/Sounds/";

		//Ambient
		ISoundEffectControl* fx = 0;
		std::string ambientSoundFileName1 = path + "amb_dungeon2d_lp_01.wav";
		ISound* ambient = SoundManager::getSingleton().getManager()->play2D(ambientSoundFileName1.c_str(),true, false, true, ESM_AUTO_DETECT, true);
		//ambient->setIsLooped(true);



		std::string stoneSoundFileName1 = path + "fst_stone_07.ogg";
		ISoundSource* stoneSound1 = SoundManager::getSingleton().getManager()->addSoundSourceFromFile(stoneSoundFileName1.c_str());
		//ISound* stoneSound1 = SoundManager::getSingleton().getManager()->play3D
		//	(stoneSoundFileName1.c_str(),vec3df(0,0,0), true, false, true);
		


		//stoneSound1->setDefaultMinDistance(75.0f);

		std::string stoneSoundFileName2 = path + "fst_stone_08.ogg";
		ISoundSource* stoneSound2 = SoundManager::getSingleton().getManager()->addSoundSourceFromFile(stoneSoundFileName2.c_str());
		//ISound* stoneSound2 = SoundManager::getSingleton().getManager()->play3D
		//	(stoneSoundFileName2.c_str(),vec3df(0,0,0), true, false, true);

		//stoneSound2->setDefaultMinDistance(75.0f);

		//grassSoundList.push_back("fst_grass_01.ogg");
		//grassSoundList.push_back("fst_grass_02.ogg");

		std::list<ISoundSource*> stoneSoundList;
		stoneSoundList.push_back(stoneSound1);
		stoneSoundList.push_back(stoneSound2);

		mSoundList["stone"] = stoneSoundList; //ApeSound::SOUND_WALK

		//ApeSound* walkSound_wood = new ApeSound();
		//walkSound_wood->addSound("WalkSound9","fst_wood_07.ogg",400,"MainNode");
		//walkSound_wood->addSound("WalkSound10","fst_wood_08.ogg",400,"MainNode");

		//ApeSound* walkSound_stone = new ApeSound();
		//walkSound_stone->addSound("WalkSound11","fst_stone_07.ogg",400,"MainNode");
		//walkSound_stone->addSound("WalkSound12","fst_stone_08.ogg",400,"MainNode");

		//ApeSound* walkSound_earth = new ApeSound();
		//walkSound_earth->addSound("WalkSound13","fst_earth_07.ogg",400,"MainNode");
		//walkSound_earth->addSound("WalkSound14","fst_earth_08.ogg",400,"MainNode");

		//ApeSound* walkSound_metal = new ApeSound();
		//walkSound_metal->addSound("WalkSound15","fst_metal_03.ogg",400,"MainNode");
		//walkSound_metal->addSound("WalkSound16","fst_metal_04.ogg",400,"MainNode");

		//ApeSound* walkSound_snow = new ApeSound();
		//walkSound_snow->addSound("WalkSound17","fst_snow_01.ogg",400,"MainNode");
		//walkSound_snow->addSound("WalkSound18","fst_snow_02.ogg",400,"MainNode");

		//ApeSound* jumpSound = new ApeSound();
		//jumpSound->addSound("JumpSound19","fst_dodge.ogg",400,"MainNode");

		//mSoundList["grass"] = grassSoundList; //ApeSound::SOUND_WALK
		//mSoundList["wood"] = walkSound_wood; //ApeSound::SOUND_WALK
		//mSoundList["stone"] = stoneSoundList; //ApeSound::SOUND_WALK
		//mSoundList["earth"] = walkSound_earth; //ApeSound::SOUND_WALK
		//mSoundList["metal"] = walkSound_metal; //ApeSound::SOUND_WALK
		//mSoundList["snow"] = walkSound_snow; //ApeSound::SOUND_WALK
		
		//mSoundList["jump"] = jumpSound; //ApeSound::SOUND_WALK
	}

}

void CSound::playSound(std::string sound) { //ApeSound sound
	std::list<ISoundSource*> soundList = mSoundList[sound];
	std::list<ISoundSource*>::iterator it;

	int i = 1;

	for(it=soundList.begin();it!=soundList.end();it++)
	{
		CCharacter* mCChar = dynamic_cast<CCharacter*>(getOwnerObject()->getComponent("CCharacter"));
		if(mCChar) {
			vec3df pos = vec3df(mCChar->getCharacterPosOgre().x,mCChar->getCharacterPosOgre().y,mCChar->getCharacterPosOgre().z);
			//(*it)->
			//pos.Y = 0;
			pos.Z = 0;
			pos.X = 0;

			if(i == mCurrentSoundIndex) {
				ISound* sound = SoundManager::getSingleton().getManager()->play2D((*it),false,false,false,true); //,pos
				
				ISoundEffectControl* fx = 0;				
				if (sound)
					fx = sound->getSoundEffectControl();
					
				if (!fx)
				{
					// some sound devices do not support sound effects.
					printf("This device or sound does not support sound effects.\n");
					continue;
				} else {
					if (!fx->isWavesReverbSoundEffectEnabled())
						fx->enableWavesReverbSoundEffect(0,-15,300,0.0);
					
				}	

				//mCurrentSoundIndex = i;
				mCurrentSoundIndex++;
				
				if(mCurrentSoundIndex > soundList.size())
					mCurrentSoundIndex = 1;

				return;
			}
			i++;
			//SoundManager::getSingleton().getManager()->play3D(
			//std::string soundfile = std::string("../../Media/Sounds/") + *it;
			//SoundManager::getSingleton().getManager()->play3D(soundfile.c_str(),pos);
		}
	}

}
void CSound::playSound() { //ApeSound sound

}

void CSound::stopSound() { //ApeSound sound

}
