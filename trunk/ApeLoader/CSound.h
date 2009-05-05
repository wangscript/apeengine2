#ifndef _CSOUND_H_
#define _CSOUND_H_

#include "GameComponent.h"
#include "Ogre.h"
#include "OgreRender.h"
#include "ApeManager.h"
#include "SoundManager.h"

#include <map>
#include <list>

using namespace Ogre;

class OgreRender;
class ApeManager;
class GameComponent;
class SoundManager;
//class OgreOggSound;

class CSound : public GameComponent {
public:
	CSound(std::string soundType,std::string soundSize, std::string soundFileName);
	CSound();
	~CSound();

	void update();
	void setup();

	virtual const std::string& familyID() const { 
		return mFamilyID; 
	}
	virtual const std::string& componentID() const { 
		return mComponentID; 
	}

	//ApeSound* getSound(std::string sound);
	void stopSound();
	void playSound(std::string sound);
	void playSound();

	std::string getSoundCategory() {
		return mSoundCategory;
	}

private:
	static const std::string mFamilyID;
	static const std::string mComponentID;
	
	std::string mSoundCategory;
	
	int mCurrentSoundIndex;

	//std::string mLastSoundPlayed;
	//std::map<SoundType::soundType,ApeSound*> mSoundList;
	//std::map<std::string,std::list<std::string>> mSoundList;
	std::map<std::string,std::list<ISoundSource*>> mSoundList;
	


};

#endif
