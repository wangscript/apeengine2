#include "CCharacterSound.h"

/*static*/ 
const std::string CCharacterSound::mFamilyID = "CCharacterSound";
const std::string CCharacterSound::mComponentID = "CCharacterSound";

ApeSound::ApeSound() {
	mSoundCount = 0;
	mInitialized = false;
}
ApeSound::ApeSound(const std::string name,const std::string fileName,Real minDelay) {
	mSoundCount = 1;
	mCurrentSound = 1;
	mMinDelay = minDelay;
	mLastTime = OgreRender::getSingleton().getTimeMS();
	mSoundFileList[mSoundCount] = SoundManager::getSingleton().getManager()->createSound(name, fileName, false, false, true);
	mInitialized = false;
}

ApeSound::~ApeSound() {
	
}

void ApeSound::addSound(const std::string name,const std::string fileName,Real minDelay, Ogre::String nodeName, bool loopSound) {
	mSoundCount++;
	mCurrentSound = mSoundCount;
	mMinDelay = minDelay;
	mLastTime = OgreRender::getSingleton().getTimeMS();
	mIsLooped = loopSound;

	//mSoundFileList[mSoundCount] = SoundManager::getSingleton().getManager()->createSound(name, fileName, false, false, false);
	mSoundFileList[mSoundCount] = SoundManager::getSingleton().getManager()->createSound(name, fileName, false,false,loopSound);
	//mSoundFileList[mSoundCount]->set
	
	if(nodeName != "") {
		Ogre::SceneNode* sNode = OgreRender::getSingleton().getSceneManager()->getSceneNode(nodeName);
		sNode->attachObject(mSoundFileList[mSoundCount]);
		//mSoundFileList[mSoundCount]->setRolloffFactor(2.0f);
		//mSoundFileList[mSoundCount]->setRelativeToListener(true);
		//mSoundFileList[mSoundCount]->setPriority(1);
		
		mSoundFileList[mSoundCount]->setReferenceDistance(50.f);
		mSoundFileList[mSoundCount]->setVolume(0.1);
		mSoundFileList[mSoundCount]->setMinVolume(0.0f);
		mSoundFileList[mSoundCount]->setMaxDistance(150);

		
		//SoundManager::getSingleton().getManager()->attachEffectToSound(name, 0, "Auditorium");


	}
	
	mInitialized = true;
}
OgreOggISound* ApeSound::getSound(unsigned int sound) {
	if(mInitialized) {
		return mSoundFileList[sound];
	}
}

bool ApeSound::timeIsUp() {
	if(mInitialized) {
		if(OgreRender::getSingleton().getTimeMS() >= (mLastTime + mMinDelay))
			return true;
		else
			return false;
	}
}

bool ApeSound::play() {
	if(mInitialized) {

		//SoundManager::getSingleton().getManager()->getSound(mSoundFileList[mCurrentSound]->getName())->is

		if( (OgreRender::getSingleton().getTimeMS() >= (mLastTime + mMinDelay)) || mIsLooped) {

			if(mSoundFileList[mSoundCount]->isPlaying()) {
				SoundManager::getSingleton().getManager()->stopSound(mSoundFileList[mCurrentSound]->getName());
			}

			SoundManager::getSingleton().getManager()->playSound(mSoundFileList[mCurrentSound]->getName());
			
			mCurrentSound++;
			if(mCurrentSound > mSoundCount)
				mCurrentSound = 1;

			mLastTime = OgreRender::getSingleton().getTimeMS();
			return true;
		
		}

	}
	return false;
}


CCharacterSound::CCharacterSound()
{
	//mLastSoundPlayed = 
}

CCharacterSound::~CCharacterSound()
{

}

void CCharacterSound::update() {
//	if(OgreRender::getSingleton().getTimeMS() >= (mLastTime + mMinDelay)) {
//	}
	//if(mInitialized)
	//if(mSoundList[ObjectSoundType::objectSoundType::SOUND_PHYSICS_DEFAULT]->timeIsUp())
	//	mSoundList[ObjectSoundType::objectSoundType::SOUND_PHYSICS_DEFAULT]->stop();

	//std::map<std::string,ApeSound*>::iterator iter;
	//for(iter = mSoundList.begin(); iter != mSoundList.end(); iter++) {
		
	//	if(OgreRender::getSingleton().getTimeMS() >= (mLastTime + mMinDelay)) {
			
	//	}
		//iter->second->setup();
		//ObjectManager::getSingleton().addObject(iter->second);
	//}

}

void CCharacterSound::setup() {

	//CMesh *mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	//mSoundList[]

	ApeSound* walkSound_grass = new ApeSound();
	walkSound_grass->addSound("WalkSound1","fst_grass_01.ogg",400,"MainNode");
	walkSound_grass->addSound("WalkSound2","fst_grass_02.ogg",400,"MainNode");

	ApeSound* walkSound_wood = new ApeSound();
	walkSound_wood->addSound("WalkSound9","fst_wood_07.ogg",400,"MainNode");
	walkSound_wood->addSound("WalkSound10","fst_wood_08.ogg",400,"MainNode");

	ApeSound* walkSound_stone = new ApeSound();
	walkSound_stone->addSound("WalkSound11","fst_stone_07.ogg",400,"MainNode");
	walkSound_stone->addSound("WalkSound12","fst_stone_08.ogg",400,"MainNode");

	ApeSound* walkSound_earth = new ApeSound();
	walkSound_earth->addSound("WalkSound13","fst_earth_07.ogg",400,"MainNode");
	walkSound_earth->addSound("WalkSound14","fst_earth_08.ogg",400,"MainNode");

	ApeSound* walkSound_metal = new ApeSound();
	walkSound_metal->addSound("WalkSound15","fst_metal_03.ogg",400,"MainNode");
	walkSound_metal->addSound("WalkSound16","fst_metal_04.ogg",400,"MainNode");

	ApeSound* walkSound_snow = new ApeSound();
	walkSound_snow->addSound("WalkSound17","fst_snow_01.ogg",400,"MainNode");
	walkSound_snow->addSound("WalkSound18","fst_snow_02.ogg",400,"MainNode");

	ApeSound* jumpSound = new ApeSound();
	jumpSound->addSound("JumpSound19","fst_dodge.ogg",400,"MainNode");

	mSoundList["grass"] = walkSound_grass; //ApeSound::SOUND_WALK
	mSoundList["wood"] = walkSound_wood; //ApeSound::SOUND_WALK
	mSoundList["stone"] = walkSound_stone; //ApeSound::SOUND_WALK
	mSoundList["earth"] = walkSound_earth; //ApeSound::SOUND_WALK
	mSoundList["metal"] = walkSound_metal; //ApeSound::SOUND_WALK
	mSoundList["snow"] = walkSound_snow; //ApeSound::SOUND_WALK
	
	mSoundList["jump"] = jumpSound; //ApeSound::SOUND_WALK

}

ApeSound* CCharacterSound::getSound(std::string sound) { //ApeSound sound
	return mSoundList[sound];
}

void CCharacterSound::playSound(std::string sound) { //ApeSound sound
	//stopSound();
	if(mSoundList[sound]->play() == true) {
		mLastSoundPlayed = sound;
	}
}

void CCharacterSound::stopSound() { //ApeSound sound
	if(mLastSoundPlayed != "") {
		for(unsigned int i = 1; i <= mSoundList[mLastSoundPlayed]->mSoundCount; i++)
			SoundManager::getSingleton().getManager()->stopSound(mSoundList[mLastSoundPlayed]->getSound(i)->getName());	
	}
}
