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

#ifndef __PU_CAMERA_DEPENDENCY_H__
#define __PU_CAMERA_DEPENDENCY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIDependency.h"

namespace ParticleUniverse
{
	/** The CameraDependency class is used to define a relation between an attribute (for example the emission
		rate of a ParticleEmitter) and the camera. The camera distance influences the value of the attribute.
	@remarks
		In case of the emission rate for example, it can be defined that that number of emitted particles 
		decreases if the camera gets further away.
    */
	class _ParticleUniverseExport CameraDependency : public IDependency
	{
		protected:
			Ogre::Real mThreshold;
			bool mIncrease;

		public:
			CameraDependency(void) :
				IDependency(),
				mThreshold(1000),
				mIncrease(false){};

			CameraDependency(Ogre::Real threshold, bool inc) :
				IDependency(),
				mThreshold(threshold),
				mIncrease(inc){};

			virtual ~CameraDependency(void){};

			/** 
	        */
			virtual bool affect(Ogre::Real& baseValue, Ogre::Real dependencyValue);

			/** 
	        */
			const Ogre::Real getThreshold(void) const {return mThreshold;};
			void setThreshold(const Ogre::Real threshold) {mThreshold = threshold;};

			/** 
	        */
			bool isIncrease(void) const {return mIncrease;};
			void setIncrease(bool increase) {mIncrease = increase;};

			/** Copy attributes to another camera dependency.
	        */
			virtual void copyAttributesTo (CameraDependency* cameraDependency);

	};
}
#endif
