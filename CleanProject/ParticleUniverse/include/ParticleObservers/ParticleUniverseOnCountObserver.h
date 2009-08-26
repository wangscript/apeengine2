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

#ifndef __PU_ONCOUNT_OBSERVER_H__
#define __PU_ONCOUNT_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe if an x number of Particles have been emitted.
	@remarks
		OnCountObserver supports 2 possible situations. If the comparison operator is set to 
		'less than', the _observe() function returns true until the counter exceeds the threshold.
		If the comparison operator is set to 'greater than', the _observe() function only returns 
		true if the counter exceeds the threshold.
    */
	class _ParticleUniverseExport OnCountObserver : public ParticleObserver
	{
		protected:
			Ogre::uint mCount;
			Ogre::uint mThreshold;
			ComparisionOperator mCompare;

		public:
			OnCountObserver(void) : ParticleObserver(),
				mCount(1),
				mThreshold(0),
				mCompare(CO_LESS_THAN)
			{
				mObserverType = "OnCount";
			};
	        virtual ~OnCountObserver(void) {};

			/** 
	        */
			virtual void _notifyStart (void);

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** 
	        */
			Ogre::uint getThreshold(){return mThreshold;};
			void setThreshold(Ogre::uint threshold){mThreshold = threshold;};

			/** 
	        */
			const ComparisionOperator getCompare(void) const {return mCompare;};
			void setCompare(ComparisionOperator op){mCompare = op;};

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
