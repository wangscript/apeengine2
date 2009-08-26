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

#ifndef __PU_PARTICLE_FOLLOWER_H__
#define __PU_PARTICLE_FOLLOWER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This affector makes particles follow its predecessor.
    */
	class _ParticleUniverseExport ParticleFollower : public ParticleAffector
	{
		public:
		ParticleFollower(void) : 
			ParticleAffector(),
			mMinDistance(10.0f),
			mMaxDistance(Ogre::Math::POS_INFINITY),
			mPositionPreviousParticle(Ogre::Vector3::ZERO),
			mFirst(false)
			{
				mAffectorType = "Follower";
			};
	        virtual ~ParticleFollower(void) {};

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** Validate if first particle.
			*/
			virtual void _firstParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Ogre::Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** 
	        */
			Ogre::Real getMaxDistance(void) const;
			void setMaxDistance(Ogre::Real maxDistance);

			/** 
	        */
			Ogre::Real getMinDistance(void) const;
			void setMinDistance(Ogre::Real minDistance);

		protected:
			Ogre::Real mMinDistance;
			Ogre::Real mMaxDistance;
			Ogre::Vector3 mPositionPreviousParticle;
			bool mFirst;
	};

}
#endif
