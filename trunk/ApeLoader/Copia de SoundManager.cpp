#include "SoundManager.h"
#include "OgreRender.h"
#include "CObjectSound.h"

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

SoundManager::SoundManager() : mSoundManager(0), newSound(0)
{
	
}
SoundManager::~SoundManager() {

}
void SoundManager::updateSoundObjects() {

	std::map<const std::string, GameObject*> gos;
	gos = ObjectManager::getSingleton().getGOs();

	std::map<const std::string, GameObject*>::iterator iter;
	for(iter = gos.begin(); iter != gos.end(); iter++) {

		GameObject* obj;
		obj = iter->second;

		//CRender* mCRender = dynamic_cast<CRender*>(obj->getComponent("CRender"));
		//CActor* mCActor = dynamic_cast<CActor*>(obj->getComponent("CActor"));
		//CLight* mCLight = dynamic_cast<CLight*>(obj->getComponent("CLight"));
		CObjectSound* sound = dynamic_cast<CObjectSound*>(obj->getComponent("CObjectSound"));

		if(sound)
			sound->setupSounds();

		//if(mCActor && mCRender) {
		//	//if(!mCActor->isStatic()) {
		//	PCZSceneNode* n = (PCZSceneNode*)(mCActor->mPhysicsActor->mNode);

		//	n->setHomeZone(mPZSM->getZoneByName(mCRender->mParentZoneName));
			//mPZSM->_updateHomeZone(n,true);			
		//}
		//if(mCRender && mCLight) {
		//	PCZSceneNode* n = (PCZSceneNode*)mCRender->mNode;
		//	n->setHomeZone(mPZSM->getZoneByName(mCRender->mParentZoneName));
		//}
	}
}

//Initialize Ogre API
bool SoundManager::initialize() {
	//mSoundManager = new OgreOggSoundManager(); 
	mSoundManager = OgreOggSoundManager::getSingletonPtr();

	bool r = mSoundManager->init();

	//OgreRender::getSingleton().getCamera()->getParentSceneNode()->attachObject(SoundManager::getSingleton().getManager()->getListener());
	//mSoundManager->setDistanceModel(AL_LINEAR_DISTANCE);

	//newSound = 0;
	//newSound = mSoundManager->createSound("Sound1", "one.ogg", true, false, false);
	
	EAXREVERBPROPERTIES props = REVERB_PRESET_AUDITORIUM;
	if ( mSoundManager->hasEFXSupport() )
	{
		mSoundManager->createEFXSlot();
		mSoundManager->createEFXEffect("Auditorium", AL_EFFECT_EAXREVERB, &props);
		
	}

	

	return r;
}
/*
void SoundManager::test() {
	// Create a streamed sound, no looping, no prebuffering
	
	if (newSound)
	{
		newSound->play();
	}
}
*/
OgreOggSoundManager* SoundManager::getManager() {
	return mSoundManager;
}

void SoundManager::update(Ogre::Real time) {
	mSoundManager->update(time);
}