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

#ifndef __PU_AFFECTOR_H__
#define __PU_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseParticle.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** Abstract class defining the interface to be implemented by particle affectors.
	@remarks
		Particle affectors modify particles in a particle system over their lifetime. This class defines 
		the interface, and provides a few implementations of some basic functions.
    */
	class _ParticleUniverseExport ParticleAffector : public Particle, public IAlias, public IElement
	{
		public:
			/**
				The AffectSpecialisation enumeration is used to specialise the affector even more. This enumeration 
				isn't used by all affectors; in some cases it isn't even applicable.
			*/
			enum AffectSpecialisation
			{
				AFSP_DEFAULT,
				AFSP_TTL_INCREASE,
				AFSP_TTL_DECREASE
			};

			ParticleAffector(void);
			virtual ~ParticleAffector(void) {};

			/** 
	        */
			const AffectSpecialisation& getAffectSpecialisation(void) const {return mAffectSpecialisation;};
			void setAffectSpecialisation(const AffectSpecialisation& affectSpecialisation) {mAffectSpecialisation = affectSpecialisation;};

			/** 
	        */
			const Ogre::String& getAffectorType(void) const {return mAffectorType;};
			void setAffectorType(const Ogre::String& affectorType) {mAffectorType = affectorType;};

			/** 
	        */
			const Ogre::String& getName(void) const {return mName;};
			void setName(const Ogre::String& name) {mName = name;};

			/** 
	        */
			ParticleTechnique* getParentTechnique(void) const {return mParentTechnique;};
			void setParentTechnique(ParticleTechnique* parentTechnique);

			/** Perform initialisation actions.
			@remarks
				The _prepare() function is automatically called during initialisation (prepare) activities of a 
				ParticleTechnique. A subclass could implement this function to perform initialisation 
				actions.
	        */
			virtual void _prepare(ParticleTechnique* particleTechnique){/* Do nothing */};

			/** Perform activities when a ParticleAffector is started.
			*/
			virtual void _notifyStart (void);

			/** Perform activities when a ParticleAffector is stopped.
			*/
			virtual void _notifyStop (void){/* Do nothing */};

			/** Perform activities when a ParticleAffector is paused.
			*/
			virtual void _notifyPause (void){/* Do nothing */};

			/** Perform activities when a ParticleAffector is resumed.
			*/
			virtual void _notifyResume (void){/* Do nothing */};

			/** Notify that the Particle System is rescaled.
	        */
			virtual void _notifyRescaled(const Ogre::Vector3& scale);

			/** Perform activities before the individual particles are processed.
			@remarks
				This function is called before the ParticleTechnique update-loop where all particles are traversed.
				the preProcess is typically used to perform calculations where the result must be used in 
				processing each individual particle.
	        */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Ogre::Real timeElapsed){/* Do nothing */};

			/** Perform precalculations if the first Particle in the update-loop is processed.
			*/
			virtual void _firstParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Ogre::Real timeElapsed) { /* by default do nothing */ }

			/** Initialise the ParticleAffector before it is emitted itself.
	        */
			virtual void _initForEmission(void);

			/** Initialise the ParticleAffector before it is expired itself.
	        */
			virtual void _initForExpiration(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** Initialise a newly emitted particle.
			@param
				particle Pointer to a Particle to initialise.
			*/
			virtual void _initParticleForEmission(Particle* particle) { /* by default do nothing */ }

			/** Entry point for affecting a Particle.
			@remarks
				Before the actual _affect() function is called, validations have to take place whether
				affecting the Particle is really needed. Particles which are emitted by a ParticleEmitter
				that has been excluded, will not be affected. This _affect() function is internally called.
			@param
				particle Pointer to a ParticleTechnique to which the particle belongs.
			@param
				particle Pointer to a Particle.
			@param
				timeElapsed The number of seconds which have elapsed since the last call.
			@param
				firstParticle Determines whether the ParticleAffector encounters the first particle of all active particles.
			*/
			void _processParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Ogre::Real timeElapsed, 
				bool firstParticle);

			/** Perform activities after the individual particles are processed.
			@remarks
				This function is called after the ParticleTechnique update-loop where all particles are traversed.
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed){/* Do nothing */};

			/** Affect a particle.
			@param
				particle Pointer to a ParticleTechnique to which the particle belongs.
			@param
				particle Pointer to a Particle.
			@param
				timeElapsed The number of seconds which have elapsed since the last call.
			*/
			virtual void _affect(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Ogre::Real timeElapsed) = 0;

			/** Add a ParticleEmitter name that excludes Particles emitted by this ParticleEmitter from being
				affected.
	        */
			void addEmitterToExclude(const Ogre::String& emitterName);

			/** Remove a ParticleEmitter name that excludes Particles emitted by this ParticleEmitter.
	        */
			void removeEmitterToExclude(const Ogre::String& emitterName);

			/** Remove all ParticleEmitter names that excludes Particles emitted by this ParticleEmitter.
	        */
			void removeAllEmittersToExclude(void);

			/** Copy attributes to another affector.
	        */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** Calculate the derived position of the affector.
			@remarks
				Note, that in script, the position is set as localspace, while if the affector is
				emitted, its position is automatically transformed. This function always returns 
				the derived position.
	        */
			const Ogre::Vector3& getDerivedPosition(void);

			/** If the mAffectSpecialisation is used to specialise the affector, a factor can be calculated and used
				in a child class. This factor depends on the value of mAffectSpecialisation.
			@remarks
				This helper method assumes that the particle pointer is valid.
			*/
			Ogre::Real _calculateAffectSpecialisationFactor (const Particle* particle);

		protected:
			ParticleTechnique* mParentTechnique;

			// Type of the affector
			Ogre::String mAffectorType;

			// Name of the affector (optional)
			Ogre::String mName;

			/** The mAffectSpecialisation is used to specialise the affector. This attribute is comparable with the 
				mAutoDirection of the ParticleEmitter, it is an optional attribute and used in some of the Particle
				Affectors.
			*/
			AffectSpecialisation mAffectSpecialisation;

			/** List of ParticleEmitter names that excludes particles emitted by ParticleEmitters with that name.
			@remarks
				Particles emitted by an ParticleEmitter with a name that is included in this list are not 
				affected by this ParticleAffector.
	        */
			std::list<Ogre::String> mExcludedEmitters;

			/** Although the scale is on a Particle System level, it is stored here also, because this value is often 
				used. It is a derived value, so it has not get a get and set function.
			*/
			Ogre::Vector3 _mParticleSystemScale;
	};

}
#endif
