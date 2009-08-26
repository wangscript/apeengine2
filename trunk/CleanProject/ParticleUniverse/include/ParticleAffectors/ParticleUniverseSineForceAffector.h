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

#ifndef __PU_SINE_FORCE_AFFECTOR_H__
#define __PU_SINE_FORCE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseForceAffector.h"

namespace ParticleUniverse
{
	/** Applies a sine force to a particle.
    */
	class _ParticleUniverseExport SineForceAffector : public ForceAffector
	{
		public:
			SineForceAffector(void) : 
				ForceAffector(),
				mAngle(361),
				mFrequencyMin(1.0f),
				mFrequencyMax(1.0f),
				mFrequency(1.0f)
			{
				mAffectorType = "SineForce";
			};
	        virtual ~SineForceAffector(void) {};

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Ogre::Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** 
	        */
			const Ogre::Real getFrequencyMin(void) const;
			void setFrequencyMin(const Ogre::Real frequencyMin);

			/** 
	        */
			const Ogre::Real getFrequencyMax(void) const;
			void setFrequencyMax(const Ogre::Real frequencyMax);

		protected:
			Ogre::Real mAngle;
			Ogre::Real mFrequencyMin;
			Ogre::Real mFrequencyMax;
			Ogre::Real mFrequency;
	};

}
#endif
