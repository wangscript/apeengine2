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

#ifndef __PU_VORTEX_AFFECTOR_H__
#define __PU_VORTEX_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"

namespace ParticleUniverse
{
	/** The VortexAffector rotates particles around a given rotation axis.
    */
	class _ParticleUniverseExport VortexAffector : public ParticleAffector
	{
		public:
			VortexAffector(void);
	        virtual ~VortexAffector(void);

			/** 
	        */
			const Ogre::Vector3& getRotationVector(void) const;

			/** 
	        */
			void setRotationVector(const Ogre::Vector3& rotationVector);

			/** 
	        */
			DynamicAttribute* getRotationSpeed(void) const;

			/** 
	        */
			void setRotationSpeed(DynamicAttribute* dynRotationSpeed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Ogre::Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

		protected:
			Ogre::Vector3 mRotationVector;
			Ogre::Quaternion mRotation;
			DynamicAttribute* mDynRotationSpeed;
			DynamicAttributeHelper mDynamicAttributeHelper;
			DynamicAttributeFactory mDynamicAttributeFactory;

			/** 
	        */
			Ogre::Radian VortexAffector::_calculateRotationSpeed(void);
	};

}
#endif
