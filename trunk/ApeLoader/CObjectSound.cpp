#include "CObjectSound.h"

/*static*/ 
const std::string CObjectSound::mFamilyID = "CObjectSound";
const std::string CObjectSound::mComponentID = "CObjectSound";

ApeObjectSound::ApeObjectSound() {
	mSoundCount = 0;
	mMinDelay = 0;
	mLastTime = 0;

	mIsInitialized = false;
}

ApeObjectSound::ApeObjectSound(Ogre::String soundType, Ogre::String soundSize, Ogre::String soundName) {
	mSoundCount = 0;
	mMinDelay = 0;
	mLastTime = 0;
/*
	mSoundType = soundType;
	mSoundFileName = "";
	mSoundCategory = "";

	if(mSoundType == "predefined") {
		
		mSoundCategory = soundName;
		mSoundSize = soundSize;
		
		mSoundFileName = "phy_" + mSoundCategory + "_" + mSoundSize.substr(0,1) + "_" + "02" + ".ogg";

	} else {
		mSoundCategory = "custom";
		mSoundFileName = soundName;
	}
*/
	mIsInitialized = false;
}

/*
Ogre::String ApeObjectSound::getSoundFileName() {
	return mSoundFileName;
}
*/

/*
ApeObjectSound::ApeObjectSound(const std::string name,const std::string fileName,Real minDelay) {
	mSoundCount = 1;
	mCurrentSound = 1;
	mMinDelay = minDelay;
	mLastTime = OgreRender::getSingleton().getTimeMS();
	mSoundFileList[mSoundCount] = SoundManager::getSingleton().getManager()->createSound(name, fileName, true, false, false);

	//mIsInitialized = false;
}
*/
ApeObjectSound::~ApeObjectSound() {
	
}

void ApeObjectSound::addSound(const std::string name,const std::string fileName,Real minDelay, Ogre::String nodeName) {
	mSoundCount++;
	mCurrentSound = mSoundCount;
	mMinDelay = minDelay;
	mLastTime = OgreRender::getSingleton().getTimeMS();

	//mSoundFileList[mSoundCount] = SoundManager::getSingleton().getManager()->createSound(name, fileName, false, false, false);
	mSoundFileList[mSoundCount] = SoundManager::getSingleton().getManager()->createSound(name, fileName, false, false, true);
	//mSoundFileList[mSoundCount]->set
	
	if(nodeName != "") {
		Ogre::SceneNode* sNode = OgreRender::getSingleton().getSceneManager()->getSceneNode(nodeName);
		sNode->attachObject(mSoundFileList[mSoundCount]);
		//mSoundFileList[mSoundCount]->setRolloffFactor(2.0f);
		//mSoundFileList[mSoundCount]->setRelativeToListener(true);
		//mSoundFileList[mSoundCount]->setPriority(1);
		
		mSoundFileList[mSoundCount]->setReferenceDistance(50.f);
		mSoundFileList[mSoundCount]->setVolume(0.1);
		
		
		//mSoundFileList[mSoundCount]->setMaxDistance(100.0f);
		mSoundFileList[mSoundCount]->setMinVolume(0.0f);
		
		mSoundFileList[mSoundCount]->setMaxDistance(150);
		
		mIsInitialized = true;
		//SoundManager::getSingleton().getManager()->attachEffectToSound(name, 0, "Auditorium");


	}

}

void ApeObjectSound::play() {
	if(mIsInitialized) {
		if(OgreRender::getSingleton().getTimeMS() >= (mLastTime + mMinDelay)) {
			//Ogre::LogManager::getSingleton().logMessage("*** Playing Sound - " + Ogre::StringConverter::toString(mLastTime + mMinDelay) );

			//mSoundFileList[mCurrentSound]->
			
			//mSoundFileList[mSoundCount]->stop();
			if(mSoundFileList[mSoundCount]->isPlaying())
				SoundManager::getSingleton().getManager()->stopSound(mSoundFileList[mCurrentSound]->getName());

			//mSoundFileList[mCurrentSound]->play();
			SoundManager::getSingleton().getManager()->playSound(mSoundFileList[mCurrentSound]->getName());
			//mCurrentSound++;
			//if(mCurrentSound > mSoundCount)
			//	mCurrentSound = 1;

			mLastTime = OgreRender::getSingleton().getTimeMS();
		}
	}
}
void ApeObjectSound::stop() {
	if(mIsInitialized) {
		//if(OgreRender::getSingleton().getTimeMS() >= (mLastTime + mMinDelay)) {
			//Ogre::LogManager::getSingleton().logMessage("*** Playing Sound - " + Ogre::StringConverter::toString(mLastTime + mMinDelay) );

			//mSoundFileList[mCurrentSound]->

		//	if(mSoundFileList[mSoundCount]->isPlaying())
				mSoundFileList[mSoundCount]->stop();

		//	mSoundFileList[mCurrentSound]->play();
			//mCurrentSound++;
			//if(mCurrentSound > mSoundCount)
			//	mCurrentSound = 1;

		//	mLastTime = OgreRender::getSingleton().getTimeMS();
		//}
	}
}
bool ApeObjectSound::timeIsUp() {
	if(mIsInitialized) {
		if(OgreRender::getSingleton().getTimeMS() >= (mLastTime + mMinDelay))
			return true;
		else
			return false;
	}
}

CObjectSound::CObjectSound(Ogre::String soundType, Ogre::String soundSize, Ogre::String soundName)
{
	mSoundType = soundType;
	mSoundFileName = "";
	mSoundCategory = "";

	if(mSoundType == "predefined") {

		mSoundCategory = soundName;
		mSoundSize = soundSize;

		mSoundFileName = "phy_" + mSoundCategory + "_" + mSoundSize.substr(0,1) + ".ogg";
		
	} else {
		mSoundCategory = "custom";
		mSoundFileName = soundName;
	}


	mIsInitialized = false;
}

CObjectSound::~CObjectSound()
{

}

void CObjectSound::update() {
	if(mIsInitialized)
		if(mSoundList[ObjectSoundType::objectSoundType::SOUND_PHYSICS_DEFAULT]->timeIsUp())
			mSoundList[ObjectSoundType::objectSoundType::SOUND_PHYSICS_DEFAULT]->stop();

}

void CObjectSound::play() {
	if(mIsInitialized)
		mSoundList[ObjectSoundType::objectSoundType::SOUND_PHYSICS_DEFAULT]->play();
}

void CObjectSound::stop() {
	if(mIsInitialized)
		mSoundList[ObjectSoundType::objectSoundType::SOUND_PHYSICS_DEFAULT]->stop();
}

void CObjectSound::setupSounds() {
	//CMesh *mesh = dynamic_cast<CMesh*>(getOwnerObject()->getComponent("CMesh"));
	CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));
	CActor *actor = dynamic_cast<CActor*>(getOwnerObject()->getComponent("CActor"));

	Ogre::String mNodeName;
	//mSoundList[]
	
	//if(!render)
	//	return;
	if(!actor)
		return;

	//if(!actor->mPhysicsActor->isDynamic()) {
	//	if(render)
	//		mNodeName = render->mNode->getName();
	//	
	//}
	//else {
		mNodeName = actor->mPhysicsActor->mNode->getName();
	//}
	
	ApeObjectSound* walkSound = new ApeObjectSound();
	//walkSound->addSound("hit1_" + actor->mPhysicsActor->getNode()->getName() ,"phy_wood_l_01.ogg",400,actor->mPhysicsActor->getNode()->getName()); //actor->mPhysicsActor->getNode()->getName()
	walkSound->addSound("hit2_" + actor->mPhysicsActor->mNode->getName() ,mSoundFileName,400,mNodeName);
	//walkSound->addSound("hit3_" + actor->mPhysicsActor->getNode()->getName() ,"phy_wood_l_03.ogg",400,actor->mPhysicsActor->getNode()->getName());

	//ApeSound* walkSound = new ApeSound("WalkSound","stepA.ogg");

	mSoundList[ObjectSoundType::objectSoundType::SOUND_PHYSICS_DEFAULT] = walkSound; //ApeSound::SOUND_WALK	

	mIsInitialized = true;

}

void CObjectSound::setup() {

}

ApeObjectSound* CObjectSound::getSound(ObjectSoundType::objectSoundType sound) { //ApeSound sound
	return mSoundList[sound];
}