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

#ifndef __PU_VISUAL_PARTICLE_H__
#define __PU_VISUAL_PARTICLE_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseParticle.h"

namespace ParticleUniverse
{
	/** A VisualParticle is the most obvious implementation of a particle. It represents that particles that can be
		visualised on the screen.
    */
	class _ParticleUniverseExport VisualParticle : public Particle
	{
		public:
			VisualParticle(void);
			virtual ~VisualParticle(void) {};

			/** Current and original colour */
			Ogre::ColourValue colour;
			Ogre::ColourValue originalColour;

			/** zRotation is used to rotate the particle in 2D (around the Z-axis)
			@remarks
				There is no relation between zRotation and orientation.
				rotationSpeed in combination with orientation are used for 3D rotation of the particle, while
				zRotation means the rotation around the Z-axis. This type of rotation is typically used for 
				rotating textures. This also means that both types of rotation can be used together.
			*/
			Ogre::Radian zRotation;

			/** The zRotationSpeed is used in combination with zRotation and defines tha actual rotationspeed
				in 2D. */
			Ogre::Radian zRotationSpeed;

			/*  Orientation of the particle.
			@remarks
				The orientation stays Quaternion::IDENTITY. Regular emission doesn´t automatically
				change the orientation of the particle. Only certain affectors, behaviours or extern 
				objects typically change the orientation. The orientation of the particle will also be 
				only visible if the Particle Renderer - such as the Box renderer - supports orientation.
			*/
			Ogre::Quaternion orientation;

			/** The rotation is used in combination with orientation. Because the rotation speed is part
				of the particle itself, it can be changed independently. */
			Ogre::Real rotationSpeed;

			/** Does this particle have it's own dimensions? */
			bool ownDimensions;

			/** Own width
			*/
			Ogre::Real width;
        
			/** Own height
			*/
			Ogre::Real height;

			/** Own depth
			*/
			Ogre::Real depth;

			/** Radius of the particle, to be used for inter-particle collision and such.
			*/
			Ogre::Real radius;

			/** Set own dimensions
			*/
			void setOwnDimensions(Ogre::Real newWidth, Ogre::Real newHeight, Ogre::Real newDepth);

			/** @see Particle::_initForExpiration()
			*/
			virtual void _initForExpiration(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** Calculate the bounding sphere radius
			*/
			void _calculateBoundingSphereRadius(void);

	};

}
#endif
