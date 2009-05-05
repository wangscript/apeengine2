#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "Ogre.h"
//#include "OgreOggSound.h"

#include "irrKlang.h"
using namespace irrklang;

using namespace Ogre;
//using namespace OgreOggSound;

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

	ISoundEngine* getManager();
	

private:
	//OgreOggISound* newSound;

	ISoundEngine* mEngine;

	//OgreOggSoundManager *mSoundManager;
};


#endif
