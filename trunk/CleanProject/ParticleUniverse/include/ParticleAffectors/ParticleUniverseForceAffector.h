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

#ifndef __PU_FORCE_AFFECTOR_H__
#define __PU_FORCE_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This is a baseclass for other Force Affector classes.
    */
	class _ParticleUniverseExport ForceAffector : public ParticleAffector
	{
		public:
			enum ForceApplication
			{
				/// Take the average of the force vector and the particle momentum
				FA_AVERAGE,
				/// Add the force vector to the particle momentum
				FA_ADD
			};

			ForceAffector(void) : 
				ParticleAffector(),
				mForceVector(Ogre::Vector3::ZERO),
				mScaledVector(Ogre::Vector3::ZERO),
				mForceApplication(ForceAffector::FA_ADD)
			{
			};
	        virtual ~ForceAffector(void) {};

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

			/** 
	        */
			const Ogre::Vector3& getForceVector(void) const;
			void setForceVector(const Ogre::Vector3& forceVector);

			/** 
	        */
			ForceApplication getForceApplication(void) const;
			void setForceApplication(ForceApplication forceApplication);

		protected:
			Ogre::Vector3 mForceVector;
			Ogre::Vector3 mScaledVector;
			ForceApplication mForceApplication;
	};

}
#endif
