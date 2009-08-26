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

#ifndef __PU_BOX_COLLIDER_H__
#define __PU_BOX_COLLIDER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCollider.h"

namespace ParticleUniverse
{
	/** The BoxCollider is a box shape that collides with the particles. The BoxCollider can only collide with
		particles that are created within the same ParticleTechnique as where the BoxCollider is registered.
    */
	class _ParticleUniverseExport BoxCollider : public Collider
	{
		public:
			BoxCollider(void) : 
				Collider(),
				mWidth(0.0f),
				mHeight(0.0f),
				mDepth(0.0f),
				mXmin(0.0f),
				mXmax(0.0f),
				mYmin(0.0f),
				mYmax(0.0f),
				mZmin(0.0f),
				mZmax(0.0f),
				mPredictedPosition(Ogre::Vector3::ZERO)
			{
				mAffectorType = "BoxCollider";
			};
	        virtual ~BoxCollider(void){};

			/** Returns the width of the box
			*/
			const Ogre::Real getWidth(void) const;

			/** Sets the width of the box
			*/
			void setWidth(const Ogre::Real width);

			/** Returns the height of the box
			*/
			const Ogre::Real getHeight(void) const;

			/** Sets the height of the box
			*/
			void setHeight(const Ogre::Real height);

			/** Returns the depth of the box
			*/
			const Ogre::Real getDepth(void) const;

			/** Sets the depth of the box
			*/
			void setDepth(const Ogre::Real depth);

			/** 
			*/
			void calculateDirectionAfterCollision(Particle* particle);

			/** @copydoc ParticleAffector::_preProcessParticles */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

		protected:
			Ogre::Real mWidth;
			Ogre::Real mHeight;
			Ogre::Real mDepth;
			Ogre::Real mXmin;
			Ogre::Real mXmax;
			Ogre::Real mYmin;
			Ogre::Real mYmax;
			Ogre::Real mZmin;
			Ogre::Real mZmax;
			Ogre::AxisAlignedBox mBox;
			Ogre::Vector3 mPredictedPosition;

			/** 
			*/
			void _calculateBounds (void);

			/** 
			*/
			bool _isSmallestValue(Ogre::Real value, const Ogre::Vector3& particlePosition);
	};

}
#endif
