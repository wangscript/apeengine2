/*
-----------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2006-2008 Henry van Merode

Usage of this program is free for non-commercial use and licensed under the
the terms of the GNU Lesser General Public License.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
-----------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_SYSTEM_MANAGER_H__
#define __PU_PARTICLE_SYSTEM_MANAGER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptTokeniser.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleRenderers/ParticleUniverseBoxSet.h"
#include "ParticleRenderers/ParticleUniverseBox.h"
#include "ParticleRenderers/ParticleUniverseSphereSet.h"
#include "ParticleRenderers/ParticleUniverseSphere.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseAffectorFactory.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseEventHandlerFactory.h"
#include "ParticleUniverseExternFactory.h"
#include "ParticleUniverseBehaviourFactory.h"
#include "ParticleUniverseITokenInitialiser.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseCameraDependency.h"
#include "ParticleUniverseSystemTokens.h"
#include "ParticleUniverseTechniqueTokens.h"
#include "ParticleUniverseRendererTokens.h"
#include "ParticleUniverseEmitterTokens.h"
#include "ParticleUniverseAffectorTokens.h"
#include "ParticleUniverseObserverTokens.h"
#include "ParticleUniverseAttachableTokens.h"
#include "ParticleUniverseDynamicAttributeTokens.h"
#include "ParticleUniverseSystemManagerTokens.h"
#include "ParticleUniverseCameraDependencyTokens.h"
#include "ParticleUniverseAttachable.h"

namespace ParticleUniverse
{
    /** The ParticleSystemManager manages particle systems, particle system scripts (templates), etc. It is also 
		responsible for actually creating techniques, emitters, observers, etc.
	*/
	class ParticleSystemFactory;

	class _ParticleUniverseExport ParticleSystemManager:
		public Ogre::Singleton<ParticleSystemManager>, public Ogre::ScriptLoader, ITokenInitialiser
    {
		friend class ParticleSystemFactory;

		public:
			// Constructor
			ParticleSystemManager (void);

			// Destructor
			~ParticleSystemManager (void);

			/** Remove all registered templates 
			*/ 
			void removeAllParticleSystemTemplates(); 

			/** Create a BoxSet. This is similar to a BillboardSet, instead it uses boxes.
			*/
			BoxSet* createBoxSet(const Ogre::String& name, Ogre::SceneManager* sceneManager, const Ogre::uint poolSize = 20);
			
			/** Destroy the BoxSet.
			*/
			void destroyBoxSet(BoxSet* boxSet, Ogre::SceneManager* sceneManager);

			/** Create a SphereSet. This is similar to a BillboardSet, instead it uses spheres.
			*/
			SphereSet* createSphereSet(const Ogre::String& name, Ogre::SceneManager* sceneManager, const Ogre::uint poolSize = 20);
			
			/** Destroy the SphereSet.
			*/
			void destroySphereSet(SphereSet* sphereSet, Ogre::SceneManager* sceneManager);

			/** Registers a previously created Attachable. This is needed, because the scenemanager has to 
				know.
			*/
			void registerAttachable(Attachable* attachable, Ogre::SceneManager* sceneManager);

			/** Unregisters a created Attachable.
			*/
			void unregisterAttachable(Attachable* attachable, Ogre::SceneManager* sceneManager);

			/** Adds a new 'factory' object for emitters to the list of available emitter types.
			@remarks
				This method allows plugins etc to add new particle emitter types. Particle emitters
				are sources of particles, and generate new particles with their start positions, colours and
				momentums appropriately. 
			@par
				All particle emitter factories have an assigned name which is used to identify the emitter
				type. This must be unique.
			@param
				factory Pointer to a ParticleEmitterFactory subclass created by the plugin or application code.
			*/
			void addEmitterFactory(ParticleEmitterFactory* factory);

			/** Delete an ParticleEmitterFactory. Search the factory by its type.
			*/
			void destroyEmitterFactory(const Ogre::String& emitterType);

			/** Method for creating a new emitter from a factory.
			@param
				emitterType String name of the emitter type to be created. A factory of this type must have been registered.
			*/
			ParticleEmitter* createEmitter(const Ogre::String& emitterType);

			/** Clone a ParticleEmitter.
	        */
			ParticleEmitter* cloneEmitter(ParticleEmitter* emitter);

			/** Delete a ParticleEmitter.
	        */
			void destroyEmitter(ParticleEmitter* emitter);

			/** Add a ParticleAffectorFactory to this ParticleSystemManager.
			@remarks
				ParticleAffectorFactories, ParticleEmitterFactories, ... can be registered by the 
				ParticleSystemManager. This is done by means of their type. If a certain ParticleAffector,
				ParticleEmitter, ... must be created, the appropriate factory is searched (by means of
				its type), which created the object needed.
			@param
				factory Pointer to a ParticleAffectorFactory subclass created by the plugin or application code.
	        */
			void addAffectorFactory(ParticleAffectorFactory* factory);

			/** Delete a ParticleAffectorFactory. Search by its type.
			*/
			void destroyAffectorFactory(const Ogre::String& affectorType);

			/** Create a ParticleAffector given a type.
	        */
			ParticleAffector* createAffector(const Ogre::String& affectorType);

			/** Clone a ParticleAffector.
	        */
			ParticleAffector* cloneAffector(ParticleAffector* affector);

			/** Delete a ParticleAffector.
	        */
			void destroyAffector(ParticleAffector* affector);

			/** Create a ParticleTechnique.
	        */
			ParticleTechnique* createTechnique(void);

			/** Clone a ParticleTechnique.
	        */
			ParticleTechnique* cloneTechnique(ParticleTechnique* technique);

			/** Delete a ParticleTechnique.
	        */
			void destroyTechnique(ParticleTechnique* technique);

			/** Add a ParticleObserverFactory to this ParticleSystemManager.
			@param
				factory Pointer to a ParticleObserverFactory subclass created by the plugin or application code.
	        */
			void addObserverFactory(ParticleObserverFactory* factory);

			/** Delete a ParticleObserverFactory given its type.
	        */
			void destroyObserverFactory(const Ogre::String& observerType) {/* No implementation */};

			/** Create a ParticleObserver given a certain type.
	        */
			ParticleObserver* createObserver(const Ogre::String& observerType);

			/** Clone a ParticleObserver.
	        */
			ParticleObserver* cloneObserver(ParticleObserver* observer);

			/** Destroye a ParticleObserver.
	        */
			void destroyObserver(ParticleObserver* observer);

			/** Add a ParticleEventHandlerFactory to this ParticleSystemManager.
			@param
				factory Pointer to a ParticleEventHandlerFactory subclass created by the plugin or application code.
	        */
			void addEventHandlerFactory(ParticleEventHandlerFactory* factory);

			/** Delete a ParticleEventHandlerFactory given a certain type.
	        */
			void destroyEventHandlerFactory(const Ogre::String& eventHandlerType) {/* No implementation */};

			/** Create a ParticleEventHandler given a certain type.
	        */
			ParticleEventHandler* createEventHandler(const Ogre::String& eventHandlerType);

			/** Clone a ParticleEventHandler.
	        */
			ParticleEventHandler* cloneEventHandler(ParticleEventHandler* eventHandler);

			/** Delete a ParticleEventHandler.
	        */
			void destroyEventHandler(ParticleEventHandler* eventHandler);

			/** Add a ParticleRendererFactory to this ParticleSystemManager.
	        */
			void addRendererFactory(ParticleRendererFactory* factory);

			/** Delete a ParticleRendererFactory given a certain type.
			*/
			void destroyRendererFactory(const Ogre::String& rendererType);

			/** Create a ParticleRenderer.
	        */
			ParticleRenderer* createRenderer(const Ogre::String& rendererType);

			/** Clone a ParticleRenderer.
	        */
			ParticleRenderer* cloneRenderer(ParticleRenderer* renderer);

			/** Delete a ParticleRenderer.
	        */
			void destroyRenderer(ParticleRenderer* renderer);

			/** Add a ExternFactory to this ParticleSystemManager.
	        */
			void addExternFactory(ExternFactory* factory);

			/** Delete a ExternFactory given a certain type.
			*/
			void destroyExternFactory(const Ogre::String& externType);

			/** Create an Extern object.
	        */
			Extern* createExtern(const Ogre::String& externType);

			/** Clone an Extern object.
	        */
			Extern* cloneExtern(Extern* externObject);

			/** Delete an Extern object.
	        */
			void destroyExtern(Extern* externObject);

			/** Add a BehaviourFactory to this ParticleSystemManager.
	        */
			void addBehaviourFactory(ParticleBehaviourFactory* factory);

			/** Delete a BehaviourFactory given a certain type.
			*/
			void destroyBehaviourFactory(const Ogre::String& behaviourType);

			/** Create a Behaviour object.
	        */
			ParticleBehaviour* createBehaviour(const Ogre::String& behaviourType);

			/** Clone a Behaviour object.
	        */
			ParticleBehaviour* cloneBehaviour(ParticleBehaviour* behaviour);

			/** Delete a Behaviour object.
	        */
			void destroyBehaviour(ParticleBehaviour* behaviour);

			/** Create a ParticleSystemTemplate.
			@remarks
				ParticleSystemTemplates contain a ParticleSystem and form a blueprint for other ParticleSystems.
				Given the name of the template, a copy is made of the ParticleSystem. This copy can be used
				in your application. The ParticleSystem templates however are restricted to the 
				ParticleSystemManager.
	        */
			ParticleSystem* createParticleSystemTemplate(const Ogre::String& name, const Ogre::String& resourceGroupName);

			/** Add a ParticleSystem template to this ParticleSystemManager.
	        */
			void addParticleSystemTemplate(const Ogre::String& name, ParticleSystem* systemTemplate);

			/** Retrieves a particle system template.
			*/
			ParticleSystem* getParticleSystemTemplate(const Ogre::String& templateName);

			/** Fill a list of template names in the vector.
			*/
			void particleSystemTemplateNames(std::vector<Ogre::String>& v);

			/** Creates a ParticleSystem, using a template as a blueprint.
			@remarks
				This is the function that must be used by the client application that wants to create a
				ParticleSystem.
	        */
			ParticleSystem* createParticleSystem(const Ogre::String& name, 
				const Ogre::String& templateName, 
				Ogre::SceneManager* sceneManager);

			/** Creates a default ParticleSystem.
			@remarks
				This is the function that must be used by the client application that wants to create a
				ParticleSystem.
	        */
			ParticleSystem* createParticleSystem(const Ogre::String& name, 
				Ogre::SceneManager* sceneManager);

			/** Delete a ParticleSystem.
			@remarks
				This is the function that must be used by the client application that wants to delete a
				ParticleSystem.
	        */
			void destroyParticleSystem(ParticleSystem* particleSystem, Ogre::SceneManager* sceneManager);

			/** Delete a ParticleSystem.
			@remarks
				This implementation deletes a ParticleSystem identified by its name. The function always
				validates whether the name still exists.
	        */
			void destroyParticleSystem(const Ogre::String& particleSystemName, Ogre::SceneManager* sceneManager);

			/** Add an alias to this ParticleSystemManager.
			@remarks
				An alias is a ParticleTechnique, ParticleEmitter, ParticleAffector, etc. and forms the
				blueprint to create copies. These copies can be used again in ParticleSystems (templates).
				An alias is similar to a template, but where templates are restricted to ParticleSystems, 
				aliasses can be any type of object that inherits from IAlias.
	        */
			void addAlias (IAlias* alias);

			/** Returns an alias.
	        */
			IAlias* getAlias (const Ogre::String& aliasName);

			/** Delete an alias from the ParticleSystemManager.
	        */
			void destroyAlias(IAlias* alias);

			/** Delete all aliasses.
	        */
			void destroyAllAliasses(void);

			/** Override standard Singleton retrieval.
	        */
			static ParticleSystemManager& getSingleton (void);
			
			/** Override standard Singleton retrieval.
			*/
			static ParticleSystemManager* getSingletonPtr (void);

			// @copydoc ScriptLoader::getScriptPatterns
			const Ogre::StringVector& getScriptPatterns (void) const;

			// @copydoc ScriptLoader::parseScript
			void parseScript (Ogre::DataStreamPtr& stream, const Ogre::String& groupName);

			// @copydoc ScriptLoader::getLoadingOrder
			Ogre::Real getLoadingOrder (void) const;

			/** Returns the ParticleScriptTokeniser.
			@remarks
				The ParticleScriptTokeniser is the main class responsible for parsing scripts.
			*/
			ParticleScriptTokeniser* getParticleScriptTokeniser(void) const;

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

			/** Returns Camera Dependency.
			@remarks
				CameraDependency is used as a container that stores data parsed from a particle script.
			*/
			CameraDependency* createCameraDependency(void);

		protected:
			/** Implementation of creating a particle system used by the MovableObject factory.
			@remarks
				This function must not be used directly.
	        */
			ParticleSystem* _createSystemImpl(const Ogre::String& name);

			/** Implementation of creating a particle system used by the MovableObject factory.
			@remarks
				This function must not be used directly.
	        */
			ParticleSystem* _createSystemImpl(const Ogre::String& name, const Ogre::String& templateName);

			/** Delete a particle system.
			@remarks
				This is a protected function used by the ParticleSystemManager itself.
	        */
			void _destroySystemImpl(ParticleSystem* particleSystem);

			ParticleScriptTokeniser* mParticleScriptTokeniser;
			Ogre::StringVector _scriptPatterns;
			ParticleSystemTokens mParticleSystemTokens;
			ParticleTechniqueTokens mParticleTechniqueTokens;
			ParticleRendererTokens mParticleRendererTokens;
			ParticleEmitterTokens mParticleEmitterTokens;
			ParticleAffectorTokens mParticleAffectorTokens;
			ParticleObserverTokens mParticleObserverTokens;
			AttachableTokens mAttachableTokens;
			DynamicAttributeTokens mDynamicAttributeTokens;
			CameraDependencyTokens mCameraDependencyTokens;

			// Emitter Factories
			typedef std::map<Ogre::String, ParticleEmitterFactory*> EmitterFactoryMap;
			EmitterFactoryMap mEmitterFactories;

			// Affector Factories
			typedef std::map<Ogre::String, ParticleAffectorFactory*> AffectorFactoryMap;
			AffectorFactoryMap mAffectorFactories;

			// Observer Factories
			typedef std::map<Ogre::String, ParticleObserverFactory*> ObserverFactoryMap;
			ObserverFactoryMap mObserverFactories;

			// EventHandler Factories
			typedef std::map<Ogre::String, ParticleEventHandlerFactory*> EventHandlerFactoryMap;
			EventHandlerFactoryMap mEventHandlerFactories;

			// Renderer Factories
			typedef std::map<Ogre::String, ParticleRendererFactory*> RendererFactoryMap;
			RendererFactoryMap mRendererFactories;

			// Extern Factories
			typedef std::map<Ogre::String, ExternFactory*> ExternFactoryMap;
			ExternFactoryMap mExternFactories;

			// Behaviour Factories
			typedef std::map<Ogre::String, ParticleBehaviourFactory*> BehaviourFactoryMap;
			BehaviourFactoryMap mBehaviourFactories;

			/*	The alias map contains a list with all alias objects that are created during parsing of the 
				scripts. The alias map contains objects that are used in the templated particle systems.
			*/
			typedef std::map<Ogre::String, IAlias*> AliasMap;
			AliasMap mAliasMap;

			/*	The template map contains a list with all particle systems that act as a template.
				These templates cannot be used themselves, but form the blueprint for creation of other 
				particle systems.
			*/
			typedef std::map<Ogre::String, ParticleSystem*> ParticleSystemTemplateMap;
			ParticleSystemTemplateMap mParticleSystemTemplates;

			// Factory used to create ParticleSystems
			ParticleSystemFactory* mParticleSystemFactory;

			// Factory used to create BoxSets
			BoxSetFactory* mBoxSetFactory;

			// Factory used to create SphereSets
			SphereSetFactory* mSphereSetFactory;

			// Parse functions on ParticleSystemManager level
			ParticleSystemManagerTokens mParticleSystemManagerTokens;

			// CameraDependency object is used as a container to store data from a particle script.
			CameraDependency mCameraDependency;
	};

	/** Factory object for creating ParticleSystem instances */
	class _ParticleUniverseExport ParticleSystemFactory : public Ogre::MovableObjectFactory
	{
		protected:
			Ogre::MovableObject* createInstanceImpl(const Ogre::String& name, const Ogre::NameValuePairList* params);
		
		public:
			ParticleSystemFactory() {}
			~ParticleSystemFactory() {}
		
			static Ogre::String PU_FACTORY_TYPE_NAME;

			const Ogre::String& getType(void) const;

			void destroyInstance(Ogre::MovableObject* obj);

	};

}
#endif
