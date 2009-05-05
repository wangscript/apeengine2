#ifndef _CCHARACTER_SOUND_H_
#define _CCHARACTER_SOUND_H_

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

namespace SoundType
{
	enum soundType {
		//NONE = 0,
		SOUND_WALK,
		SOUND_JUMP
	}; 
}

class ApeSound  {
public:

	ApeSound();
	ApeSound(const std::string name,const std::string fileName,Real minDelay = 0);
	~ApeSound();

	void addSound(const std::string name,const std::string fileName,Real minDelay = 0, Ogre::String nodeName = "", bool loopSound = false);
	bool play();
	bool timeIsUp();
	OgreOggISound* getSound(unsigned int);
	unsigned int mSoundCount;

private:
	
	unsigned int mCurrentSound;
	Real mMinDelay;
	Real mLastTime;
	bool mIsLooped;

	bool mInitialized;
	std::map<unsigned int,OgreOggISound*> mSoundFileList;

};

class ApeSound;

class CCharacterSound : public GameComponent {
public:
	CCharacterSound();
	~CCharacterSound();

	void update();
	void setup();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}

	ApeSound* getSound(std::string sound);
	void stopSound();
	void playSound(std::string sound);

private:
	static const std::string mFamilyID;
	static const std::string mComponentID;
	
	std::string mLastSoundPlayed;
	//std::map<SoundType::soundType,ApeSound*> mSoundList;
	std::map<std::string,ApeSound*> mSoundList;

};

#endif
