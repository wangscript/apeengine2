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

#ifndef __PU_SPHERE_COLLIDER_EXTERN_H__
#define __PU_SPHERE_COLLIDER_EXTERN_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleAffectors/ParticleUniverseSphereCollider.h"
#include "ParticleUniverseAttachable.h"

namespace ParticleUniverse
{
	/** The SphereColliderExtern is a wrapper of the SphereCollider, adding the functionality of a MovableObject.
		This makes it possible to let particles collide with a SphereCollider that is attached to a different 
		SceneNode, than the ParticleSystem with which particles it collides.
    */
	class _ParticleUniverseExport SphereColliderExtern : public Attachable, public SphereCollider
	{
		public:
			SphereColliderExtern(void) : 
				Attachable(),
				SphereCollider() {};
	        virtual ~SphereColliderExtern(void) {};

			/** see Extern::_preProcessParticles */
			virtual void _preProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** see Extern::_interface */
			virtual void _interface(ParticleTechnique* technique, 
				Particle* particle, 
				Ogre::Real timeElapsed);

			/** Copy both the Extern and the derived SphereCollider properties.
	        */
			virtual void copyAttributesTo (Extern* externObject);

		protected:
	};

}
#endif
