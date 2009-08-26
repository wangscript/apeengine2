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

#ifndef __PU_INTERPARTICLE_COLLIDER_H__
#define __PU_INTERPARTICLE_COLLIDER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCollider.h"

namespace ParticleUniverse
{
	/** The InterParticleCollider ....
    */
	class _ParticleUniverseExport InterParticleCollider : public Collider
	{
		public:
			enum InterParticleCollisionResponse
			{
				IPCR_AVERAGE_VELOCITY,
				IPCR_ANGLE_BASED_VELOCITY
			};

			InterParticleCollider(void) : 
				Collider(),
				mAdjustment(1.0f),
				mInterParticleCollisionResponse(IPCR_AVERAGE_VELOCITY)
			{
				mAffectorType = "InterParticleCollider";
			};
	        virtual ~InterParticleCollider(void){};

			/** Todo
			*/
			Ogre::Real getAdjustment(void) const;

			/** Todo
			*/
			void setAdjustment(Ogre::Real adjustment);

			/** Todo
			*/
			InterParticleCollisionResponse getInterParticleCollisionResponse(void) const;

			/** Todo
			*/
			void setInterParticleCollisionResponse(InterParticleCollisionResponse interParticleCollisionResponse);

			/** @copydoc ParticleAffector::_prepare */
			virtual void _prepare(ParticleTechnique* particleTechnique);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);
		
		protected:
			Ogre::Real mAdjustment;
			InterParticleCollisionResponse mInterParticleCollisionResponse;

			/** Todo
			*/
			bool _validateAndExecuteSphereCollision (Particle* particle1, Particle* particle2, Ogre::Real timeElapsed);
	};

}
#endif
