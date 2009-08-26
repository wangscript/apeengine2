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

#ifndef __PU_GRAVITY_EXTERN_H__
#define __PU_GRAVITY_EXTERN_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleAffectors/ParticleUniverseGravityAffector.h"
#include "ParticleUniverseAttachable.h"

namespace ParticleUniverse
{
	/** The GravityExtern is a wrapper of the GravityAffector, adding the functionality of a MovableObject.
		The GravityExtern can be attached to another SceneNode than the one where the ParticleSystem at 
		which the GravityExtern is registered, is attached. This makes it possible to affect the particles 
		in the Particle System, while both SceneNodes moves different from each other. This approach makes
		it possible to simulate something like a helicopter (SceneNode to which the GravityExtern is 
		attached) that flies over a certain area and moves the leaves on the ground (Particle System attached
		to another SceneNode).
    */
	class _ParticleUniverseExport GravityExtern : public Attachable, public GravityAffector
	{
		public:
		GravityExtern(void) : 
			Attachable(),
			GravityAffector() {};
	        virtual ~GravityExtern(void) {};

			/** The _preProcessParticles() function sets the position and mDerivedPosition attributes to
				the actual world position of the node to which it is attached.
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** Processes a particle.
	        */
			virtual void _interface(ParticleTechnique* technique, 
				Particle* particle, 
				Ogre::Real timeElapsed);

			/** Copy both the Extern and the derived GravityAffector properties.
	        */
			virtual void copyAttributesTo (Extern* externObject);

		protected:
	};

}
#endif
