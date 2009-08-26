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

#ifndef __PU_SCALE_AFFECTOR_H__
#define __PU_SCALE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** Scales a particle. This can be a linear scale, but scaling that changes over time is possible.
    */
	class _ParticleUniverseExport ScaleAffector : public ParticleAffector
	{
		public:
			ScaleAffector(void);
	        virtual ~ScaleAffector(void);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** 
	        */
			DynamicAttribute* getDynScaleX(void) const {return mDynScaleX;};
			void setDynScaleX(DynamicAttribute* dynScaleX);

			/** 
	        */
			DynamicAttribute* getDynScaleY(void) const {return mDynScaleY;};
			void setDynScaleY(DynamicAttribute* dynScaleY);

			/** 
	        */
			DynamicAttribute* getDynScaleZ(void) const {return mDynScaleZ;};
			void setDynScaleZ(DynamicAttribute* dynScaleZ);

			/** 
	        */
			DynamicAttribute* getDynScaleXYZ(void) const {return mDynScaleXYZ;};
			void setDynScaleXYZ(DynamicAttribute* dynScaleXYZ);

	protected:
			DynamicAttribute* mDynScaleX;
			DynamicAttribute* mDynScaleY;
			DynamicAttribute* mDynScaleZ;
			DynamicAttribute* mDynScaleXYZ;
			bool mDynScaleXSet;
			bool mDynScaleYSet;
			bool mDynScaleZSet;
			bool mDynScaleXYZSet;
			DynamicAttributeFactory mDynamicAttributeFactory;
			DynamicAttributeHelper mDynamicAttributeHelper;

			/** Returns the scale value for the dynamic Scale.
	        */
			Ogre::Real _calculateScale(DynamicAttribute* dynScale, Particle* particle);

			Ogre::Real mLatestTimeElapsed;
	};

}
#endif
