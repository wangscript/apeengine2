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

#ifndef __PU_GRAVITY_AFFECTOR_H__
#define __PU_GRAVITY_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This affector applies Newton's law of universal gravitation. The distance between a particle
		and the GravityAffector is important in the calculation of the gravity. Therefor, this affector needs
		to have its position set.
    */
	class _ParticleUniverseExport GravityAffector : public ParticleAffector
	{
		public:
		GravityAffector(void) : 
			ParticleAffector(),
			mGravity(1.0f)
			{
				mAffectorType = "Gravity";
			};
	        virtual ~GravityAffector(void) {};

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
			Ogre::Real getGravity(void) const;
			void setGravity(Ogre::Real gravity);

	protected:
			Ogre::Real mGravity;
	};

}
#endif
