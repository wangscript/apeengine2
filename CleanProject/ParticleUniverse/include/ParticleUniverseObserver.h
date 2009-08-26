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

#ifndef __PU_OBSERVER_H__
#define __PU_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseParticle.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** ParticleObservers are used to observe whether a certain condition occurs. This condition is often related to 
		the state of a Particle, but also certain situations regarding a ParticleTechnique, ParticleEmitter or even
		the ParticleSystem can be validated.
	@remarks
		ParticleEventHandlers can be added to a ParticleObserve to handle the condition that is registered by the
		ParticleObserver. This mechanism provides a extendable framework for determination of events and processing
		these events.
	@par
		ParticleObservers are defined on the same level as a ParticleEmitter and not as part of a ParticleEmitter. 
		This is because the ParticleObserver observes ALL particles in the ParticleTechniques´ Particle pool.
	@par
		A ParticleObserver can contain one or more ParticleEventHandlers.
	*/
	class _ParticleUniverseExport ParticleObserver : public IAlias, public IElement
	{
		public:
			typedef std::vector<ParticleEventHandler*>::iterator ParticleEventHandlerIterator;
			typedef std::vector<ParticleEventHandler*>::const_iterator ParticleEventHandlerConstIterator;
			typedef std::vector<ParticleEventHandler*> ParticleEventHandlerList;

			ParticleObserver(void);
			virtual ~ParticleObserver(void);

			/** 
	        */
			const Ogre::String& getObserverType(void) const {return mObserverType;};
			void setObserverType(const Ogre::String& observerType) {mObserverType = observerType;};

			/** 
	        */
			virtual bool isEnabled(void) const;

			/** 
	        */
			virtual void setEnabled(bool enabled);

			/** 
	        */
			ParticleTechnique* getParentTechnique(void) const {return mParentTechnique;};
			void setParentTechnique(ParticleTechnique* parentTechnique){mParentTechnique = parentTechnique;};

			/** 
	        */
			const Ogre::String& getName(void) const {return mName;};
			void setName(const Ogre::String& name) {mName = name;};

			/** 
	        */
			const Particle::ParticleType& getParticleTypeToObserve(void) const {return mParticleTypeToObserve;};
			void setParticleTypeToObserve(const Particle::ParticleType particleTypeToObserve);

			/** Perform activities when a ParticleTechnique is started.
			*/
			virtual void _notifyStart (void);

			/** Perform activities when a ParticleTechnique is stopped.
			*/
			virtual void _notifyStop (void){/* Do nothing */};

			/** Notify that the Particle System is rescaled.
	        */
			virtual void _notifyRescaled(const Ogre::Vector3& scale);

			/** Perform activities before the individual particles are processed.
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** Executes the ParticleObserver.
			@remarks
				This function calls the _observe() function to determine whether the event must be handled or not.
	        */
			virtual void _processParticle(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed, bool firstParticle);

			/** Perform precalculations if the first Particle in the update-loop is processed.
			*/
			virtual void _firstParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Ogre::Real timeElapsed) { /* by default do nothing */ }

			/** Perform activities after the individual particles are processed.
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed){/* Do nothing */};

			/** This function determines whether a condition (the event) is true or false.
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed) = 0;

			/** 
	        */
			ParticleEventHandler* createEventHandler(const Ogre::String& eventHandlerType);

			/** 
	        */
			void addEventHandler(ParticleEventHandler* eventHandler);

			/** 
	        */
			ParticleEventHandler* getEventHandler (size_t index) const;

			/** 
	        */
			ParticleEventHandler* getEventHandler (const Ogre::String& eventHandlerName) const;

			/** 
	        */
			size_t getNumEventHandlers (void) const;

			/** 
	        */
			void destroyEventHandler(ParticleEventHandler* eventHandler);

			/** 
	        */
			void destroyEventHandler (size_t index);

			/** 
	        */
			void destroyAllEventHandlers (void);

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);

			/** Return the interval value, which defines at what interval the observer is called.
	        */
			Ogre::Real getObserverInterval(void) const;

			/** Set the interval value, which defines at what interval the observer is called.
	        */
			void setObserverInterval(Ogre::Real observerInterval);

			/** Return the value of mObserveUntilEvent.
	        */
			bool getObserveUntilEvent(void) const;

			/** Sets the value of mObserveUntilEvent. This value determines whether observation must be continued
				after an event ocurred and the event handlers are called.
	        */
			void setObserveUntilEvent(bool observeUntilEvent);

		protected:
			ParticleTechnique* mParentTechnique;

			// Type of observer
			Ogre::String mObserverType;

			// Name of the observer (optional)
			Ogre::String mName;

			/** Determines whether an observer is activated.
	        */
			bool mEnabled;
			bool mOriginalEnabled;
			bool mOriginalEnabledSet;

			/** Determines whether the _observe() function must be executed.
			@remarks
				This is independent of mEnabled, which means that an observer can be enabled, but if mObserve has
				been set to false, it still doesn't observe. It is used to enable/disable execution of the _observe() 
				function in combination with the update interval.
	        */
			bool mObserve;

			/** Observes until an event takes place. If the event occurs, the event handlers are called and after that
				the observer doesn't observe anymore.
	        */
			bool mObserveUntilEvent;

			/** Flag that is set if the event handler(s) are called at least once.
	        */
			bool mEventHandlersExecuted;

			/** Although the scale is on a Particle System level, it is stored here also, because this value is often 
				used. It is a derived value, so it has not get a get and set function.
			*/
			Ogre::Vector3 _mParticleSystemScale;

			// Particle type to be observed. Default is that all particles are observed.
			Particle::ParticleType mParticleTypeToObserve;

			/** Determines whether mParticleTypeToObserve is set. If ´true´, only that particles of the specified type
				are observed. If ´false´ (= default), all particles are obeserved.
			*/
			bool mParticleTypeToObserveSet;

			// List with EventHandlers, which will be triggered if the condition that this observer validates occurs.
			ParticleEventHandlerList mEventHandlers;

			/** Values that determine that the observer is called after every interval.
	        */
			Ogre::Real mObserverInterval;
			Ogre::Real mObserverIntervalRemainder;
			bool mObserverIntervalSet;

			/** Handle the observer implementation.
	        */
			virtual void _handleObserve (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** Handle the event.
			@remarks
				This function iterates over all at the observer registered handlers and executes them.				
	        */
			virtual void _handleEvent (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);
	};

}
#endif
