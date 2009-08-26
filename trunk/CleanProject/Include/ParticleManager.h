/*!
	@file
	@author		Pablo Nuñez
	@date		13/2009
	@module
*//*
	This file is part of the Nebula Engine.
	
	Nebula Engine is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	Nebula Engine is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.
	
	You should have received a copy of the GNU Lesser General Public License
	along with Nebula Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _PARTICLE_MANAGER_H
#define _PARTICLE_MANAGER_H

#include "EnginePrerequisites.h"

namespace Nebula {

	class ParticleUniverse::ParticleSystem;

	class NebulaDllPrivate ParticleManager : public ITask,
											 public Ogre::Singleton<ParticleManager>
	{
	public:
		ParticleManager();
		~ParticleManager();
		
		static ParticleManager& getSingleton(void);
		static ParticleManager* getSingletonPtr(void);

		bool start();
		void onSuspend();
		void update();
		void onResume();
		void stop();
		
		void createParticle(const std::string name, const std::string scriptName);
		void attachParticleToNode(const std::string name, Ogre::SceneNode*);
		void detachParticleFromNode(const std::string name, Ogre::SceneNode*);
		void startParticle(const std::string name);
		void stopParticle(const std::string name);
		ParticleUniverse::ParticleSystem* getParticle(const std::string name);

		//mParticle = ParticleManager::getSingleton().getParticleManager()->createParticleSystem(mDesc.name,mDesc.particleScriptName,OgreManager::getSingleton().getSceneManager());

		void initialize();

		ParticleUniverse::ParticleSystemManager* getParticleManager() {
			return mParticleManager;
		}

	private:
		ParticleUniverse::ParticleSystemManager* mParticleManager;

		std::map<const std::string, ParticleUniverse::ParticleSystem* > mParticles;

		//Set Lua bindings
		void setBindings();

	};


} //end namespace

#endif