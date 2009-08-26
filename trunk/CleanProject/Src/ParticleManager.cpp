#include "ParticleManager.h"

template<> Nebula::ParticleManager* Ogre::Singleton<Nebula::ParticleManager>::ms_Singleton = 0;

namespace Nebula {

	ParticleManager::ParticleManager()
	{
		initialize();
	}

	ParticleManager::~ParticleManager()
	{

	}

	void ParticleManager::initialize() {

		mParticleManager =  ParticleUniverse::ParticleSystemManager::getSingletonPtr();
		
		std::vector<Ogre::String> names;
		mParticleManager->particleSystemTemplateNames(names);
		std::vector<Ogre::String>::iterator it;
		std::vector<Ogre::String>::iterator itEnd = names.end();
		//CEGUI::ListboxTextItem* item;
		for (it = names.begin(); it != itEnd; ++it)
		{
			Ogre::String n = (*it);
			//mListBox->addItem(item);
		}

	}

	ParticleManager* ParticleManager::getSingletonPtr(void)
	{
		return ms_Singleton;
	}

	ParticleManager& ParticleManager::getSingleton(void)
	{
		assert( ms_Singleton );  
		return ( *ms_Singleton );
	}
		
	void ParticleManager::createParticle(const std::string name, const std::string scriptName) {
		ParticleUniverse::ParticleSystem* particle = ParticleManager::getSingleton().getParticleManager()->createParticleSystem(name,scriptName,OgreManager::getSingleton().getSceneManager());
		mParticles[name] = particle;

	}

	void ParticleManager::attachParticleToNode(const std::string name, Ogre::SceneNode* node) {
		node->attachObject(mParticles[name]);
	}

	void ParticleManager::detachParticleFromNode(const std::string name, Ogre::SceneNode* node) {
		node->detachObject(mParticles[name]);
	}
	
	ParticleUniverse::ParticleSystem* ParticleManager::getParticle(const std::string name) {
		if(mParticles[name]) {
			return mParticles[name];
			
			//ParticleUniverse::ParticleTechnique* tech = mParticles[name]->getTechnique(0);
			//ParticleUniverse::ParticleEmitter* emiter = tech->getEmitter(0);
			//emiter->setParticleDirection
			//ParticleUniverse::ParticleBehaviour* pb = emiter->getBehaviour();

			//ParticleUniverse::ParticleSystem::getTechnique ParticleUniverse::ParticleSystem::getTechnique(0)

		}
	}

	void ParticleManager::startParticle(const std::string name) {
		if(mParticles[name])
			mParticles[name]->start();
	}

	void ParticleManager::stopParticle(const std::string name) {
		if(mParticles[name]) {
			mParticles[name]->stop();
		}
	}

	void ParticleManager::setBindings() {

	}

	bool ParticleManager::start()
	{

		return true;
	}

	void ParticleManager::onSuspend()
	{

	}

	void ParticleManager::update()
	{
		
	}

	void ParticleManager::onResume()
	{

	}

	void ParticleManager::stop()
	{

	}
	

} //end namespace
