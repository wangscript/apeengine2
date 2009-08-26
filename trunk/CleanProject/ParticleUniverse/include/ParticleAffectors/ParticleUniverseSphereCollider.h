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

#ifndef __PU_SPHERE_COLLIDER_H__
#define __PU_SPHERE_COLLIDER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCollider.h"

namespace ParticleUniverse
{
	/** The SphereCollider is a sphere shape that collides with the particles. The SphereCollider can only collide 
		with particles that are created within the same ParticleTechnique as where the SphereCollider is registered.
    */
	class _ParticleUniverseExport SphereCollider : public Collider
	{
		public:
			SphereCollider(void) : 
				Collider(),
				mPredictedPosition(Ogre::Vector3::ZERO),
				mRadius(0.0f)
			{
				mAffectorType = "SphereCollider";
			};
	        virtual ~SphereCollider(void){};

			/** Returns the radius of the sphere
			*/
			const Ogre::Real getRadius(void) const;

			/** Sets the radius of the sphere
			*/
			void setRadius(const Ogre::Real radius);

			/** 
			*/
			void calculateDirectionAfterCollision(Particle* particle, Ogre::Vector3 distance, Ogre::Real distanceLength);

			/** @copydoc ParticleAffector::_preProcessParticles */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

		protected:
			Ogre::Real mRadius;
			Ogre::Sphere mSphere;
			Ogre::Vector3 mPredictedPosition;
	};

}
#endif
