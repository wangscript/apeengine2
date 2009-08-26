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

#ifndef __PU_ONEXPIRE_OBSERVER_H__
#define __PU_ONEXPIRE_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether a Particle has been expired.
    */
	class _ParticleUniverseExport OnExpireObserver : public ParticleObserver
	{
		protected:

		public:
			OnExpireObserver(void) : ParticleObserver()
			{
				mObserverType = "OnExpire";
			};
	        virtual ~OnExpireObserver(void) {};

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);
	};

}
#endif
