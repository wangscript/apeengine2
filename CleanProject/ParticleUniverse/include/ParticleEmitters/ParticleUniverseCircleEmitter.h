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

#ifndef __PU_CIRCLE_EMITTER_H__
#define __PU_CIRCLE_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The CircleEmitter is a ParticleEmitter that emits particles on a circle shape. Particle can be emitted
		random on the circle, but it can also follow the circles' contours.
    */
	class _ParticleUniverseExport CircleEmitter : public ParticleEmitter
	{
		protected:
			Ogre::Real mRadius;
			Ogre::Real mCircleAngle;
			Ogre::Real mStep;
			Ogre::Real mX;
			Ogre::Real mZ;
			bool mRandom;
			Ogre::Quaternion mOrientation;

		public:
			CircleEmitter(void);
	        virtual ~CircleEmitter(void) {};

			/** 
	        */
			const Ogre::Real getRadius(void) const;
			void setRadius(const Ogre::Real radius);

			/** 
	        */
			const Ogre::Real getCircleAngle(void) const;
			void setCircleAngle(const Ogre::Real circleAngle);

			/** 
	        */
			const Ogre::Real getStep(void) const;
			void setStep(const Ogre::Real step);

			/** 
	        */
			const bool isRandom(void) const;
			void setRandom(const bool random);

			/* 
			*/ 
			const Ogre::Quaternion& getOrientation(void) const; 
			void setNormal(const Ogre::Vector3 &normal); 

			/** Determine a particle position on the circle.
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** Determine the particle direction.
	        */
			virtual void _initParticleDirection(Particle* particle);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
