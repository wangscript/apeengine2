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

#ifndef __PU_ALIGN_AFFECTOR_H__
#define __PU_ALIGN_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** Aligns the orientation of a particle towards the previous particle and adjusts the height of
		the particle, which becomes the length between the two particles. And how do we benefit from 
		this? Well, with the right renderer settings you could get a chain of particles, each connected
		to the previous, making use of the particle orientation.
		
		We get good results with a billboard renderer (which - btw - doesn't take the particle 
		orientation into account by default). Use the billboard type 'oriented shape', which is a type
		that isn't a standard billboard type of Ogre. It has been added to allow the billboard renderer
		take advantage of the particles' orientation. Also use for instance 'bottom center' as the 
		billboard origin, which neatly connects the billboards.

		Using the AlignAffector is a step in the direction to generate electric beams.
    */
	class _ParticleUniverseExport AlignAffector : public ParticleAffector
	{
		protected:
			Particle* mPreviousParticle;
			bool mResize;

		public:
			AlignAffector(void) : 
				ParticleAffector(),
				mPreviousParticle(0),
				mResize(false)
			{
				mAffectorType = "Align";
			};
	        virtual ~AlignAffector(void) {};

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** See setResize().
	        */
			bool isResize(void) const;

			/** Set resize. This attribute determines whether the size of the particle must be changed
				according to its alignment with the previous particle.
	        */
			void setResize(bool resize);

			/** @copydoc ParticleAffector::_firstParticle */
			virtual void _firstParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::_affect */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);
	};

}
#endif
