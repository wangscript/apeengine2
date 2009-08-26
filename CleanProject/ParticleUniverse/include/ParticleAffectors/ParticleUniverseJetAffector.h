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

#ifndef __PU_JET_AFFECTOR_H__
#define __PU_JET_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"

namespace ParticleUniverse
{
	/** Adds a non-linear boost to a particle.
    */
	class _ParticleUniverseExport JetAffector : public ParticleAffector
	{
		protected:
			Ogre::Real mScaled;

			/** Dynamic attribute used to generate the velocity of a particle.
			*/
			DynamicAttribute* mDynAcceleration;

			/** Helper factory
			*/
			DynamicAttributeFactory mDynamicAttributeFactory;

		public:
			JetAffector(void);
	        virtual ~JetAffector(void);

			/** 
	        */
			DynamicAttribute* getDynAcceleration(void) const {return mDynAcceleration;};
			void setDynAcceleration(DynamicAttribute* dynAcceleration);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);
	};

}
#endif
