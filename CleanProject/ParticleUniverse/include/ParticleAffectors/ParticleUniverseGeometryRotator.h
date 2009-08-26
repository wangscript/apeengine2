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

#ifndef __PU_GEOMETRY_ROTATOR_H__
#define __PU_GEOMETRY_ROTATOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseDynamicAttributeFactory.h"

namespace ParticleUniverse
{
	/** The GeometryRotator rotates particles around its orientation axis. The rotation speed can be 
		adjusted and can be set to a 'global' rotation speed, which affects all particles in the
		Particle Technique the same way. It is also possible to use the rotation speed of the particles
		itself.
    */
	class _ParticleUniverseExport GeometryRotator : public ParticleAffector
	{
		public:
			GeometryRotator(void);
	        virtual ~GeometryRotator(void);

			/** Returns the rotation speed. This is the speed controlled by the affector. Besides
				the default rotation speed, it is also possible to use the particles own rotation speed.
	        */
			DynamicAttribute* getRotationSpeed(void) const;

			/** 
	        */
			void setRotationSpeed(DynamicAttribute* dynRotationSpeed);

			/** Returns an indication whether the rotation speed is the same for all particles in this 
				particle technique, or whether the rotation speed of the particle itself is used.
	        */
			bool useOwnRotationSpeed (void) const;

			/** Set the indication whether rotation speed of the particle itself is used.
	        */
			void setUseOwnRotationSpeed (bool useOwnRotationSpeed);

			/** 
	        */
			const Ogre::Vector3& getRotationAxis(void) const;

			/** 
	        */
			void setRotationAxis(const Ogre::Vector3& rotationAxis);

			/** Returns a rotation speed value, depending on the type of dynamic attribute.
	        */
			Ogre::Real _calculateRotationSpeed (Particle* particle);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** @copydoc ParticleAffector::_initParticleForEmission */
			virtual void _initParticleForEmission(Particle* particle);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

		protected:
			Ogre::Real mScaledRotationSpeed;
			bool mUseOwnRotationSpeed;
			DynamicAttribute* mDynRotationSpeed;
			Ogre::Quaternion mQ;
			Ogre::Vector3 mRotationAxis;
			bool mRotationAxisSet;

			/** Helper factory
			*/
			DynamicAttributeFactory mDynamicAttributeFactory;
			DynamicAttributeHelper mDynamicAttributeHelper;
	};

}
#endif
