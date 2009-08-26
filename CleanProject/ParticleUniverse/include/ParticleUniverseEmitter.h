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

#ifndef __PU_EMITTER_H__
#define __PU_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"
#include "ParticleUniverseCameraDependency.h"
#include "ParticleUniverseCameraDependencyFactory.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseParticle.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** Abstract class defining the interface to be implemented by particle emitters.
	@remarks
		Subclasses of ParticleEmitters are responsible of spawning the particles of a particle technique.
		This class defines the interface, and provides a few implementations of some basic functions.
    */
	class _ParticleUniverseExport ParticleEmitter : public Particle, public IAlias, public IElement
	{
		protected:
			ParticleTechnique* mParentTechnique;

			/** Although the scale is on a Particle System level, it is stored here also, because this value is often 
				used. It is a derived value, so it has not get a get and set function.
			*/
			Ogre::Vector3 _mParticleSystemScale;

			// Type of the emitter
			Ogre::String mEmitterType;

			// Name of the emitter (optional)
			Ogre::String mName;

			/** Direction (and speed) of the emitted particle
			@remarks
				Don't confuse the particle direction with the direction of the emitter itself. 
				The particleDirection is the direction of an emitted particle.
			*/
			Ogre::Vector3 mParticleDirection;

			// Angle around direction which particles may be emitted
			DynamicAttribute* mDynAngle;

			// Rate of particle emission.
			DynamicAttribute* mDynEmissionRate;

			// Identifies the type of particle this emitter emits (default is visual particle).
			ParticleType mEmitsType;

			// Identifies the name of particle this emitter emits (default is visual particle, so there is no name)
			Ogre::String mEmitsName;

			/** Dynamic attribute used to generate the total time to live.
			*/
			DynamicAttribute* mDynTotalTimeToLive;

			/** Dynamic attribute used to generate the mass of a particle.
			*/
			DynamicAttribute* mDynParticleMass;

			/** Dynamic attribute used to generate the velocity of a particle.
			*/
			DynamicAttribute* mDynVelocity;

			/** Dynamic attribute used to define the duration of the emitter.
			*/
			DynamicAttribute* mDynDuration;

			/** Dynamic attribute used to define the repeat/delay of the emitter.
			*/
			DynamicAttribute* mDynRepeatDelay;

			/** Dynamic attribute used to define the (own) dimensions of a particle.
			@remarks
				In the Particle Technique it is possible to set the default dimensions for all particles, but it
				is also possible to set the dimensions per particle. Note, that this only applies to visual particles,
				of course. This attribute is used to x, y and z dimensions with the value.
			*/
			DynamicAttribute* mDynParticleAllDimensions;
			bool mDynParticleAllDimensionsSet;

			/** Dynamic attribute used to define the (own) width of a particle.
			@remarks
				In the Particle Technique it is possible to set the default width for all particles, but it
				is also possible to set the width per particle. Note, that this only applies to visual particles,
				of course.
			*/
			DynamicAttribute* mDynParticleWidth;
			bool mDynParticleWidthSet;

			/** Dynamic attribute used to define the (own) height of a particle.
			@remarks
				In the Particle Technique it is possible to set the default height for all particles, but it
				is also possible to set the height per particle. Note, that this only applies to visual particles,
				of course.
			*/
			DynamicAttribute* mDynParticleHeight;
			bool mDynParticleHeightSet;

			/** Dynamic attribute used to define the (own) depth of a particle.
			@remarks
				In the Particle Technique it is possible to set the default depth for all particles, but it
				is also possible to set the depth per particle. Note, that this only applies to visual particles,
				of course.
			*/
			DynamicAttribute* mDynParticleDepth;
			bool mDynParticleDepthSet;

			/** Notional up vector, just used to speed up generation of variant directions.
			*/
			Ogre::Vector3 mUpVector;

			/** Particles that are left to be emitted from the previous time.
			*/
			Ogre::Real mRemainder;

			/** Helper factory
			*/
			DynamicAttributeFactory mDynamicAttributeFactory;

			/** Helper class
			*/
			DynamicAttributeHelper mDynamicAttributeHelper;

			/** Duration remainder.
	        */
			Ogre::Real mDurationRemain;

			/** Indication to determine whether duration is set.
	        */
			bool mDynDurationSet;

			/** Repeat/delay remainder.
	        */
			Ogre::Real mRepeatDelayRemain;

			/** Indication to determine whether repeat/delay is set.
	        */
			bool mDynRepeatDelaySet;

			/** Distance value that causes a decrease (or increase if needed) of the particle emission rate.
			@remarks
				This is used to decrease the emission rate if the camera is further away.
			@par
				Note, that the distance concerns the squared distance between the camera and the ParticleTechnique
				and NOT between the camera and the ParticleEmitter position. This means that it will not be accurate
				if the emitter is emitted itself. The reason is to reduce the number of calculations.
			@par
				This should be typically used for a 1 camera setup, since using 2 camera´s would result in wrong 
				calculations (mixed values).
			*/
			CameraDependency* mEmissionRateCameraDependency;

			/** Factory to create a CameraDependency.
			*/
			CameraDependencyFactory mCameraDependencyFactory;

			/** Auto direction means that the direction of a particle is not determined by the 
				direction vector that has been set, but the direction vector is generated based on
				the shape of the emitter. In most cases this means that the particle direction is
				perpendicular on the shape of the emitter.
			@remarks
				This attribute has only a meaning for certain emitters.
			*/
			bool mAutoDirection;

			/** In normal cases, emission is regulated by time. This prevents that too much particles are
				emitted at once, which causes a drop in the framerate. In some cases you just want to emit
				all particles immediately without any delay. Setting the 'mForceEmission' to true enables this.
				In that case, the emission rate defines the number of particles that are emitted immediately.
				If the emission rate is 100, the emitter emits 100 particles at once and then disables.
			*/
			bool mForceEmission;

			/** Original value, used to set it back.
			*/
			bool mOriginalForceEmission;

			/** If mForceEmission has been set to true and if all particles are emitted, the mForceEmissionExecuted
				is also set to true, preventing any further 'forced emission'.
			*/
			bool mForceEmissionExecuted;

			/** Original value, used to set it back.
			*/
			bool mOriginalForceEmissionExecuted;

			/** Colour that is assigned to an emitted particle.
			*/
			Ogre::ColourValue mParticleColour;

			/** Used to randomize the colour of an emitted particle.
			*/
			Ogre::ColourValue mParticleColourRangeStart;

			/** Used to randomize the colour of an emitted particle.
			*/
			Ogre::ColourValue mParticleColourRangeEnd;

			/** Used to determine whether the colour range has been set.
			*/
			bool mParticleColourRangeSet;

			/** Determines whether particle positions should be kept local in relation to the emitter.
	        */
			bool mKeepLocal;

		public:
			ParticleEmitter(void);
			
			virtual ~ParticleEmitter(void);

			/** 
	        */
			ParticleTechnique* getParentTechnique(void) const {return mParentTechnique;};
			void setParentTechnique(ParticleTechnique* parentTechnique);

			/** 
	        */
			const Ogre::String& getEmitterType(void) const {return mEmitterType;};
			void setEmitterType(const Ogre::String& emitterType) {mEmitterType = emitterType;};

			/** 
	        */
			const Ogre::String& getName(void) const {return mName;};
			void setName(const Ogre::String& name) {mName = name;};

			/** 
	        */
			DynamicAttribute* getDynAngle(void) const {return mDynAngle;};
			void setDynAngle(DynamicAttribute* dynAngle);

			/** 
	        */
			DynamicAttribute* getDynEmissionRate(void) const {return mDynEmissionRate;};
			void setDynEmissionRate(DynamicAttribute* dynEmissionRate);

			/** 
	        */
			DynamicAttribute* getDynTotalTimeToLive(void) const {return mDynTotalTimeToLive;};
			void setDynTotalTimeToLive(DynamicAttribute* dynTotalTimeToLive);

			/** 
	        */
			DynamicAttribute* getDynParticleMass(void) const {return mDynParticleMass;};
			void setDynParticleMass(DynamicAttribute* dynParticleMass);

			/** 
	        */
			DynamicAttribute* getDynVelocity(void) const {return mDynVelocity;};
			void setDynVelocity(DynamicAttribute* dynVelocity);

			/** 
	        */
			DynamicAttribute* getDynDuration(void) const {return mDynDuration;};
			void setDynDuration(DynamicAttribute* dynDuration);

			/** 
	        */
			DynamicAttribute* getDynRepeatDelay(void) const {return mDynRepeatDelay;};
			void setDynRepeatDelay(DynamicAttribute* dynRepeatDelay);

			/** 
	        */
			DynamicAttribute* getDynParticleAllDimensions(void) const {return mDynParticleAllDimensions;};
			void setDynParticleAllDimensions(DynamicAttribute* dynParticleAllDimensions);

			/** 
	        */
			DynamicAttribute* getDynParticleWidth(void) const {return mDynParticleWidth;};
			void setDynParticleWidth(DynamicAttribute* dynParticleWidth);

			/** 
	        */
			DynamicAttribute* getDynParticleHeight(void) const {return mDynParticleHeight;};
			void setDynParticleHeight(DynamicAttribute* dynParticleHeight);

			/** 
	        */
			DynamicAttribute* getDynParticleDepth(void) const {return mDynParticleDepth;};
			void setDynParticleDepth(DynamicAttribute* dynParticleDepth);

			/** 
	        */
			ParticleType getEmitsType(void) const {return mEmitsType;};
			void setEmitsType(ParticleType emitsType) {mEmitsType = emitsType;};

			/** 
	        */
			const Ogre::String& getEmitsName(void) const {return mEmitsName;};
			void setEmitsName(const Ogre::String& emitsName);

			/** Set the distance-value and inc. indication to recalculate the emission rate.
	        */
			void setEmissionRateCameraDependency(CameraDependency* cameraDependency);
			void setEmissionRateCameraDependency(Ogre::Real squareDistance, bool inc = false);

			/** 
	        */
			CameraDependency* getEmissionRateCameraDependency(void);

			/** Returns the base direction of the particle that is going to be emitted. */
			virtual const Ogre::Vector3& getParticleDirection(void) const;

			/** 
	        */
			virtual void setEnabled (bool enabled);
			
			/** Sets the direction of the particle that the emitter is emitting.
			@remarks
				Don't confuse this with the emitters own direction.
			@param dir The base direction of emitted particles.
			*/
			virtual void setParticleDirection(const Ogre::Vector3& direction);

			/** 
	        */
			bool isAutoDirection(void) const;

			/** 
	        */
			void setAutoDirection(bool autoDirection);

			/** 
	        */
			bool isForceEmission(void) const;

			/** 
	        */
			void setForceEmission(bool forceEmission);

			/** Perform initialisation actions.
	        */
			virtual void _prepare(ParticleTechnique* particleTechnique){/* Do nothing */};

			/** Perform activities before the individual particles are processed.
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** Perform activities after the individual particles are processed.
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed){/* Do nothing */};

			/** Perform initialising activities as soon as the emitter is emitted.
	        */
			virtual void _initForEmission(void);

			/** Initialise the ParticleEmitter before it is expired itself.
	        */
			virtual void _initForExpiration(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** 
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** 
	        */
			virtual void _initParticleForEmission(Particle* particle);

			/**  Internal method for generating the particle direction.
			@param direction Reference to direction vector
			*/
			virtual void _initParticleDirection(Particle* particle);

			/**  Internal method for generating the angle.
			*/
			void _generateAngle(Ogre::Radian& angle);

			/**  Internal method for generating the particle velocity.
			@param dVector Reference to vector direction * velocity
			*/
			virtual void _initParticleVelocity(Particle* particle);

			/**  Internal method for generating the mass of a particle.
			*/
			virtual void _initParticleMass(Particle* particle);

			/**  Internal method for generating the colour of a particle.
			*/
			virtual void _initParticleColour(Particle* particle);

			/**  Internal method for generating the time to live of a particle.
			*/
			Ogre::Real _initParticleTimeToLive(void);

			/** Calculate the number of particles that the emitter wants to emit.
			*/
			virtual unsigned short _calculateRequestedParticles(Ogre::Real timeElapsed);

			/**  Internal method for generating particles' own dimensions.
			@remarks
				Particles' own dimensions will only be set if the mDynParticleAllDimensions or the mDynParticleWidth, 
				mDynParticleHeight and/or mDynParticleDepth have been defined in the emitter.
			@param particle Pointer to a particle
			 */
			void _initParticleDimensions(Particle* particle);

			/** Initialise some attributes that are time-based.
	        */
			void _initTimeBased(void);

			/** Calculate the derived position of the emitter.
			@remarks
				Note, that in script, the position is set into localspace, while if the emitter is
				emitted, its position is automatically transformed . This function always returns the 
				transformed (derived) position.
	        */
			const Ogre::Vector3& getDerivedPosition(void);

			/** Perform activities when a ParticleEmitter is started.
			*/
			virtual void _notifyStart (void);

			/** Perform activities when a ParticleEmitter is stopped.
			*/
			virtual void _notifyStop (void){/* Do nothing */};

			/** Perform activities when a ParticleEmitter is paused.
			*/
			virtual void _notifyPause (void){/* Do nothing */};

			/** Perform activities when a ParticleEmitter is resumed.
			*/
			virtual void _notifyResume (void){/* Do nothing */};

			/** Notify that the Particle System is rescaled.
	        */
			virtual void _notifyRescaled(const Ogre::Vector3& scale);

			/** Copy attributes to another emitter.
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);

			/** Get the colour of a particle that will be emitted.
	        */
			const Ogre::ColourValue& getParticleColour(void) const;

			/** Set the colour of an emitted particle.
	        */
			void setParticleColour(const Ogre::ColourValue& particleColour);

			/** Get the colour range start of an emitted particle.
	        */
			const Ogre::ColourValue& getParticleColourRangeStart(void) const;

			/** Set the colour range start of an emitted particle. This is the lower value used to generate a random colour.
	        */
			void setParticleColourRangeStart(const Ogre::ColourValue& particleColourRangeStart);

			/** Get the colour range end of an emitted particle.
	        */
			const Ogre::ColourValue& getParticleColourRangeEnd(void) const;

			/** Set the colour range end of an emitted particle. This is the upper value used to generate a random colour.
	        */
			void setParticleColourRangeEnd(const Ogre::ColourValue& particleColourRangeEnd);

			/** 
			*/
			bool isKeepLocal(void) const;

			/** If this attribute is set to 'true', the particles are emitted relative to the emitter
			*/
			void setKeepLocal(bool keepLocal);

			/** Transforms the particle position in a local position relative to the emitter
			*/
			bool makeParticleLocal(Particle* particle);
	};

}
#endif
