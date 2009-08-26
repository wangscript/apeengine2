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

#ifndef __PU_ONEVENTFLAG_OBSERVER_H__
#define __PU_ONEVENTFLAG_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** The OnEventFlagObserver looks at each particle is one or more eventflags are set.
    */
	class _ParticleUniverseExport OnEventFlagObserver : public ParticleObserver
	{
		protected:
			Ogre::uint32 mEventFlag;

		public:
			OnEventFlagObserver(void) : ParticleObserver(),
				mEventFlag(0.0f)
			{
				mObserverType = "OnEventFlag";
			};
	        virtual ~OnEventFlagObserver(void) {};

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** 
	        */
			Ogre::uint32 getEventFlag(){return mEventFlag;};
			void setEventFlag(Ogre::uint32 eventFlag){mEventFlag = eventFlag;};

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
