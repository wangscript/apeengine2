#include "SoundManager.h"
#include "OgreRender.h"
//#include "CObjectSound.h"

//class OgreRender;

template<> SoundManager* Ogre::Singleton<SoundManager>::ms_Singleton = 0;

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
	
}
SoundManager::~SoundManager() {

}
void SoundManager::updateSoundObjects() {

}

//Initialize Ogre API
bool SoundManager::initialize() {
	mEngine = createIrrKlangDevice();

	if (!mEngine)
		return 0; // error starting up the engine

	//mEngine->setListenerPosition(vec3df(0,0,0), vec3df(0,0,1));
	
	return true;
}

ISoundEngine* SoundManager::getManager() {
	return mEngine;
}

void SoundManager::update(Ogre::Real time) {
	Ogre::Vector3 p = OgreRender::getSingleton().getCamera()->getDerivedPosition();
	vec3df pos = vec3df(p.x,p.y,p.z);

	Ogre::Vector3 d = OgreRender::getSingleton().getCamera()->getDerivedDirection();
	//vec3df dir = vec3df(d.x,d.y,d.z);
	vec3df dir = vec3df(0,0,-1);

	pos.Y = 0;
	pos.Z = 0;

	mEngine->setListenerPosition(pos, dir);

}