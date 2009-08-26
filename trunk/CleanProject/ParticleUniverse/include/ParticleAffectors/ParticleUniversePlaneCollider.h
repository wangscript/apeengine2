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

#ifndef __PU_PLANE_COLLIDER_H__
#define __PU_PLANE_COLLIDER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCollider.h"

namespace ParticleUniverse
{
	/** The PlaneCollider is a plane shape that collides with the particles. The PlaneCollider can only collide 
		with particles that are created within the same ParticleTechnique as where the PlaneCollider is registered.
    */
	class _ParticleUniverseExport PlaneCollider : public Collider
	{
		public:
			PlaneCollider(void) : 
				Collider(),
				mPredictedPosition(Ogre::Vector3::ZERO),
				mNormal(Ogre::Vector3::ZERO)
			{
				mAffectorType = "PlaneCollider";
			};
	        virtual ~PlaneCollider(void){};

			/** Returns the normal of the plane
			*/
			const Ogre::Vector3 getNormal(void) const;

			/** Sets the normal of the plane
			*/
			void setNormal(const Ogre::Vector3& normal);

			/** 
			*/
			void calculateDirectionAfterCollision(Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

		protected:
			Ogre::Vector3 mNormal;
			Ogre::Vector3 mPredictedPosition;
			Ogre::Plane mPlane;
	};

}
#endif
