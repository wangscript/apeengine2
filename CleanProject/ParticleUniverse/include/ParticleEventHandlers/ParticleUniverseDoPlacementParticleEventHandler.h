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

#ifndef __PU_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_H__
#define __PU_DO_PLACEMENT_PARTICLE_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseParticle.h"
#include "ParticleUniverseTechniqueListener.h"

namespace ParticleUniverse
{
	/** This class 'sticks' one or more particles to the position of a particle that is passed through the 
		DoPlacementParticleEventHandler.
	@remarks
		The position of each particle that is passed through the DoPlacementParticleEventHandler is used to emit
		one or more particles on that same position. The ParticleEmitter that is used for emitting the particle(s)
		is searched (once) by means of its name.
	@par
		This class uses a 'TechniqueListener' to pass the newly created particle from the ParticleTechnique to the 
		DoPlacementParticleEventHandler, where it is initialised.
    */
	class _ParticleUniverseExport DoPlacementParticleEventHandler : public ParticleEventHandler, public TechniqueListener
	{
		protected:
			// Identifies the name of emitter
			Ogre::String mForceEmitterName;

			// The number of particles to emit
			Ogre::Real mNumberOfParticles;

			// The position of the particle to be processed
			Ogre::Vector3 mPosition;

			/** Store the technique value to keep up to speed.
			@remarks
				If the ParticleTechnique has been destroyed, the DoPlacementParticleEventHandler isn´t automatically
				notified. Using the pointer causes an exception.
	        */
			ParticleTechnique* mTechnique;

			/** Store the emitter value to keep up to speed.
			@remarks
				If the ParticleEmitter has been destroyed, the DoPlacementParticleEventHandler isn´t automatically
				notified. Using the pointer causes an exception.
	        */
			ParticleEmitter* mEmitter;

			/** Used to determine whether the emitter used by the DoPlacementParticleEventHandler, is already found.
	        */
			bool mFound;

		public:
			DoPlacementParticleEventHandler(void);
	        virtual ~DoPlacementParticleEventHandler(void);

			/** Get the name of the emitter that is used to emit its particles.
	        */
			const Ogre::String& getForceEmitterName(void) const {return mForceEmitterName;};

			/** Set the name of the emitter that is used to emit its particles.
	        */
			void setForceEmitterName(const Ogre::String& forceEmitterName){mForceEmitterName = forceEmitterName;};

			/** Get the number of particles to emit.
	        */
			Ogre::Real getNumberOfParticles(void) const {return mNumberOfParticles;};

			/** Set the number of particles to emit.
	        */
			void setNumberOfParticles(Ogre::Real numberOfParticles){mNumberOfParticles = numberOfParticles;};

			/** If the _handle() function of this class is invoked (by an Observer), it searches the 
				ParticleEmitter defined by the mForceEmitterName. This ParticleEmitter is either part of 
				the ParticleTechnique in which the DoPlacementParticleEventHandler is defined, and if the ParticleEmitter
				is not found, other ParticleTechniques are searched. The ParticleEmitter is 'forced' to emit the
				requested number of particles.
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** Initialise the emitted particle. This means that its position is set.
	        */
			virtual void particleEmitted(ParticleTechnique* particleTechnique, Particle* particle);

			/** No implementation.
	        */
			virtual void particleExpired(ParticleTechnique* particleTechnique, Particle* particle){};

			/** Copy attributes to another event handler.
	        */
			virtual void copyAttributesTo (ParticleEventHandler* eventHandler);
	};

}
#endif
