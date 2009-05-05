#ifndef _COBJECT_SOUND_H_
#define _COBJECT_SOUND_H_

#include "GameComponent.h"
#include "Ogre.h"
#include "OgreRender.h"
#include "ApeManager.h"
#include "OgreOggSound.h"
#include "SoundManager.h"

#include <map>

using namespace Ogre;
using namespace OgreOggSound;

class OgreRender;
class ApeManager;
class GameComponent;
class SoundManager;
//class OgreOggSound;

namespace ObjectSoundType
{
	enum objectSoundType {
		//NONE = 0,
		SOUND_PHYSICS_DEFAULT
		//SOUND_JUMP
	}; 
}

class ApeObjectSound  {
public:

	ApeObjectSound();
	//ApeObjectSound(const std::string name,const std::string fileName,Real minDelay = 0);
	ApeObjectSound(Ogre::String soundType, Ogre::String soundSize, Ogre::String soundName);

	~ApeObjectSound();
	
	void addSound(const std::string name,const std::string fileName,Real minDelay = 0, Ogre::String nodeName = "");
	void play();
	void stop();
	bool timeIsUp();

	//Ogre::String getSoundFileName();
/*
	Ogre::String mSoundType;
	Ogre::String mSoundSize;
	Ogre::String mSoundFileName;
	Ogre::String mSoundCategory;
*/

private:

	bool mIsInitialized;

	unsigned int mSoundCount;
	unsigned int mCurrentSound;
	Real mMinDelay;
	Real mLastTime;


	std::map<unsigned int,OgreOggISound*> mSoundFileList;

};

class ApeObjectSound;

class CObjectSound : public GameComponent {
public:
	CObjectSound(Ogre::String soundType, Ogre::String soundSize, Ogre::String soundName);
	~CObjectSound();

	void update();
	void setup();
	void play();
	void stop();
	void setupSounds();
	

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}

	ApeObjectSound* getSound(ObjectSoundType::objectSoundType sound);

	Ogre::String mSoundType;
	Ogre::String mSoundSize;
	Ogre::String mSoundFileName;
	Ogre::String mSoundCategory;

private:

	bool mIsInitialized;

	static const std::string mFamilyID;
	static const std::string mComponentID;
	
	std::map<ObjectSoundType::objectSoundType,ApeObjectSound*> mSoundList;

};

#endif
