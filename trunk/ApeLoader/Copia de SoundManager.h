#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "Ogre.h"
#include "OgreOggSound.h"

using namespace Ogre;
using namespace OgreOggSound;

class SoundManager : public Ogre::Singleton<SoundManager>
{
public:

	SoundManager(); 
	~SoundManager();

	static SoundManager& getSingleton(void);
	static SoundManager* getSingletonPtr(void);
	
	//void test();
	bool initialize();
	void update(Ogre::Real time);
	void updateSoundObjects();

	OgreOggSoundManager* getManager();

private:
	OgreOggISound* newSound;

	OgreOggSoundManager *mSoundManager;
};


#endif
