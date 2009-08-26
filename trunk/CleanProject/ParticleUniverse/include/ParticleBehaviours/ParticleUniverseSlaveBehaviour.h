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

#ifndef __PU_SLAVE_BEHAVIOUR_H__
#define __PU_SLAVE_BEHAVIOUR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseBehaviour.h"
#include "ParticleUniverseTechniqueListener.h"

namespace ParticleUniverse
{
	/** Todo.
    */
	class _ParticleUniverseExport SlaveBehaviour : public ParticleBehaviour
	{
		protected:

		public:
			Particle* masterParticle;

			SlaveBehaviour(void);
	        virtual ~SlaveBehaviour(void){};

			/** See ParticleBehaviour.
	        */
			virtual void _processParticle(ParticleTechnique* technique, Particle* particle, Ogre::Real timeElapsed);

			/** 
	        */
			virtual void copyAttributesTo (ParticleBehaviour* behaviour);
	};

}
#endif
