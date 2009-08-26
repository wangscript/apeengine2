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

#ifndef __PU_ONTIME_OBSERVER_H__
#define __PU_ONTIME_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** The OnTimeObserver observers how much time has been elapsed. This can be both the particles own time
		and the time since the ParticleSystem was started.
    */
	class _ParticleUniverseExport OnTimeObserver : public ParticleObserver
	{
		protected:
			Ogre::Real mThreshold;
			ComparisionOperator mCompare;
			bool mSinceStartSystem;

		public:
			OnTimeObserver(void) : ParticleObserver(),
				mThreshold(0.0f),
				mCompare(CO_GREATER_THAN),
				mSinceStartSystem(false)
			{
				mObserverType = "OnTime";
			};
	        virtual ~OnTimeObserver(void) {};

			/** In case there are no particles, but the observation returns true, the event handlers must still be
				called.
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** 
	        */
			Ogre::Real getThreshold(){return mThreshold;};
			void setThreshold(Ogre::Real threshold){mThreshold = threshold;};

			/** 
	        */
			const ComparisionOperator getCompare(void) const {return mCompare;};
			void setCompare(ComparisionOperator op){mCompare = op;};

			/** 
	        */
			bool isSinceStartSystem(){return mSinceStartSystem;};
			void setSinceStartSystem(bool sinceStartSystem){mSinceStartSystem = sinceStartSystem;};

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
