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

#ifndef __PU_LINEAR_FORCE_AFFECTOR_H__
#define __PU_LINEAR_FORCE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseForceAffector.h"

namespace ParticleUniverse
{
	/** Adds a force to particles.
    */
	class _ParticleUniverseExport LinearForceAffector : public ForceAffector
	{
		public:
			LinearForceAffector(void) : 
				ForceAffector()
			{
				mAffectorType = "LinearForce";
			};
	        virtual ~LinearForceAffector(void) {};

			/** 
	        */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			virtual void _preProcessParticles(ParticleTechnique* particleTechnique, Ogre::Real timeElapsed);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

		protected:
	};

}
#endif
