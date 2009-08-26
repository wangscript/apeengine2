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

#ifndef __PU_ONCLEAR_OBSERVER_H__
#define __PU_ONCLEAR_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether all particles of a technique are no longer emitted.
    */
	class _ParticleUniverseExport OnClearObserver : public ParticleObserver
	{
		protected:
			bool mContinue;

		public:
			OnClearObserver(void) : ParticleObserver(),
				mContinue(false)
			{
				mObserverType = "OnClear";
			};
	        virtual ~OnClearObserver(void) {};

			/** 
	        */
			virtual void _notifyStart (void);

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique,
				Particle* particle, 
				Ogre::Real timeElapsed);

			/** The _processParticle() function is overridden, because we don´t observe an individual particle.
				even if there isn´t a particle left anymore (and that is the situation we want to validate).
	        */
			virtual void _processParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Ogre::Real timeElapsed, 
				bool firstParticle);

			/** Instead of the _processParticle(), the _postProcessParticles() is used because it is called
				even if there isn´t a particle left anymore (and that is the situation we want to validate).
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed);
	};

}
#endif
