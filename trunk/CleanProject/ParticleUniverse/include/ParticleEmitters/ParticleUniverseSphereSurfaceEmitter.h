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

#ifndef __PU_SPHERE_SURFACE_EMITTER_H__
#define __PU_SPHERE_SURFACE_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The SphereSurfaceEmitter emits particles from the surface of a sphere (instead within the sphere´s
		volume). The particles are emitted in a direction perpendicular to the tangentvector where 
		the particle emits. Using the angle attribute, the direction can be influenced.
    */
	class _ParticleUniverseExport SphereSurfaceEmitter : public ParticleEmitter
	{
		protected:
			Ogre::Real mRadius;
			Ogre::Vector3 mRandomVector;

		public:
			SphereSurfaceEmitter(void) : 
				ParticleEmitter(),
				mRadius(10),
				mRandomVector(Ogre::Vector3::ZERO)
			{
				mEmitterType = "SphereSurface";
			};
	        virtual ~SphereSurfaceEmitter(void) {};

			/** 
	        */
			const Ogre::Real getRadius(void) const;
			void setRadius(const Ogre::Real radius);

			/** 
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** 
	        */
			virtual void _initParticleDirection(Particle* particle);
			
			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
