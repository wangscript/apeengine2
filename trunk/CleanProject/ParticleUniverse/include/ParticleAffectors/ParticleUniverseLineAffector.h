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

#ifndef __PU_LINE_AFFECTOR_H__
#define __PU_LINE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** Affects a particle depending on a line shape. Particles are getting a new position along the line.
    */
	class _ParticleUniverseExport LineAffector : public ParticleAffector
	{
		protected:
			Ogre::Real mMaxDeviation;
			Ogre::Real _mScaledMaxDeviation;
			Ogre::Vector3 mEnd;
			Ogre::Real mTimeSinceLastUpdate;
			Ogre::Real mTimeStep;
			Ogre::Real mDrift;
			Ogre::Real mOneMinusDrift;
			bool mUpdate;
			bool mFirst;

		public:
		LineAffector(void) : 
			ParticleAffector(),
			mMaxDeviation(1.0f),
			_mScaledMaxDeviation(1.0f),
			mEnd(Ogre::Vector3::ZERO),
			mTimeSinceLastUpdate(0.0f),
			mTimeStep(0.1f),
			mUpdate(true),
			mFirst(true),
			mDrift(0.0f),
			mOneMinusDrift(1.0f)
			{
				mAffectorType = "Line";
			};
	        virtual ~LineAffector(void) {};

			/** 
	        */
			Ogre::Real getMaxDeviation(void) const;
			void setMaxDeviation(Ogre::Real maxDeviation);

			/** 
	        */
			const Ogre::Vector3& getEnd(void) const;
			void setEnd(const Ogre::Vector3& end);

			/** 
	        */
			Ogre::Real getTimeStep(void) const;
			void setTimeStep(Ogre::Real timeStep);

			/** 
	        */
			Ogre::Real getDrift(void) const;
			void setDrift(Ogre::Real drift);

			/**
	        */
			virtual void _notifyRescaled(const Ogre::Vector3& scale);

			/** 
	        */
			virtual void _firstParticle(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);
			/** 
	        */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Ogre::Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** 
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);
	};

}
#endif
