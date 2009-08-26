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

#ifndef __PU_ONPOSITION_OBSERVER_H__
#define __PU_ONPOSITION_OBSERVER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCommon.h"
#include "ParticleUniverseObserver.h"

namespace ParticleUniverse
{
	/** This class is used to observe whether a Particle reaches a certain position.
    */
	class _ParticleUniverseExport OnPositionObserver : public ParticleObserver
	{
		protected:
			Ogre::Real mPositionXThreshold;
			Ogre::Real mPositionYThreshold;
			Ogre::Real mPositionZThreshold;
			bool mPositionXThresholdSet;
			bool mPositionYThresholdSet;
			bool mPositionZThresholdSet;
			ComparisionOperator mComparePositionX;
			ComparisionOperator mComparePositionY;
			ComparisionOperator mComparePositionZ;

		public:
			OnPositionObserver(void) : 
				ParticleObserver(),
				mPositionXThreshold(0),
				mPositionYThreshold(0),
				mPositionZThreshold(0),
				mComparePositionX(CO_LESS_THAN),
				mComparePositionY(CO_LESS_THAN),
				mComparePositionZ(CO_LESS_THAN),
				mPositionXThresholdSet(false),
				mPositionYThresholdSet(false),
				mPositionZThresholdSet(false)
			{
				mObserverType = "OnPosition";
			};
	        virtual ~OnPositionObserver(void) {};

			/** 
	        */
			virtual bool _observe (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** 
			 */
			void setPositionXThreshold(Ogre::Real threshold){mPositionXThreshold = threshold; mPositionXThresholdSet = true;};
			void setPositionYThreshold(Ogre::Real threshold){mPositionYThreshold = threshold; mPositionYThresholdSet = true;};
			void setPositionZThreshold(Ogre::Real threshold){mPositionZThreshold = threshold; mPositionZThresholdSet = true;};

			/** 
			 */
			Ogre::Real getPositionXThreshold(void) const {return mPositionXThreshold;};
			Ogre::Real getPositionYThreshold(void) const {return mPositionYThreshold;};
			Ogre::Real getPositionZThreshold(void) const {return mPositionZThreshold;};

			/** 
			 */
			void setComparePositionX(ComparisionOperator op){mComparePositionX = op;};
			void setComparePositionY(ComparisionOperator op){mComparePositionY = op;};
			void setComparePositionZ(ComparisionOperator op){mComparePositionZ = op;};

			/** 
			 */
			const ComparisionOperator getComparePositionX(void) const {return mComparePositionX;};
			const ComparisionOperator getComparePositionY(void) const {return mComparePositionX;};
			const ComparisionOperator getComparePositionZ(void) const {return mComparePositionX;};

			/** Copy attributes to another observer.
	        */
			virtual void copyAttributesTo (ParticleObserver* observer);
	};

}
#endif
