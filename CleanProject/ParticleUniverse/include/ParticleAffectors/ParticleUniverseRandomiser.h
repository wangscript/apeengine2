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

#ifndef __PU_RANDOMISER_H__
#define __PU_RANDOMISER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** Randomises the position or the direction of a particle.
    */
	class _ParticleUniverseExport Randomiser : public ParticleAffector
	{
		protected:
			Ogre::Real mMaxDeviationX;
			Ogre::Real mMaxDeviationY;
			Ogre::Real mMaxDeviationZ;
			Ogre::Real mTimeSinceLastUpdate;
			Ogre::Real mTimeStep;
			bool mRandomDirection;
			bool mUpdate;

		public:
			Randomiser(void) : 
				ParticleAffector(),
				mMaxDeviationX(1.0f),
				mMaxDeviationY(1.0f),
				mMaxDeviationZ(1.0f),
				mTimeSinceLastUpdate(0.0f),
				mTimeStep(0.0f),
				mUpdate(true),
				mRandomDirection(true)
			{
				mAffectorType = "Randomiser";
			};
	        virtual ~Randomiser(void) {};

			/** 
	        */
			Ogre::Real getMaxDeviationX(void) const;
			void setMaxDeviationX(const Ogre::Real maxDeviationX);

			/** 
	        */
			Ogre::Real getMaxDeviationY(void) const;
			void setMaxDeviationY(const Ogre::Real maxDeviationZ);

			/** 
	        */
			Ogre::Real getMaxDeviationZ(void) const;
			void setMaxDeviationZ(const Ogre::Real maxDeviationZ);

			/** 
	        */
			Ogre::Real getTimeStep(void) const;
			void setTimeStep(const Ogre::Real timeStep);

			/** 
	        */
			bool isRandomDirection(void) const;
			void setRandomDirection(bool randomDirection);

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
