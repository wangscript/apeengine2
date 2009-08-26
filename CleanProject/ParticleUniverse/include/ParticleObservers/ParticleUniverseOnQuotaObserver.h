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

#ifndef __PU_ONQUOTA_OBSERVER_H__
#define __PU_ONQUOTA_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether all particles or all particles of a specific type are emitted.
    */
	class _ParticleUniverseExport OnQuotaObserver : public ParticleObserver
	{
		protected:
			bool mResult;

		public:
			OnQuotaObserver(void) : ParticleObserver(),
				mResult(false)
			{
				mObserverType = "OnQuota";
			};
	        virtual ~OnQuotaObserver(void) {};

			/** @copydoc ParticleObserver::_notifyStart */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleObserver::_notifyStart */
			virtual void _postProcessParticles(ParticleTechnique* particleTechnique, Ogre::Real timeElapsed);
	};

}
#endif
