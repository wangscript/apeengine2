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

#ifndef __PU_PATH_FOLLOWER_H__
#define __PU_PATH_FOLLOWER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This affector let particles move along a line. The line is derived from a number of points in 3D space.
		Using a spline interpolation, the line becomes smooth.
    */
	class _ParticleUniverseExport PathFollower : public ParticleAffector
	{
		protected:
			Ogre::SimpleSpline mSpline;

		public:
			PathFollower(void) : 
				ParticleAffector()
			{
				mAffectorType = "PathFollower";
			};
	        virtual ~PathFollower(void) {};

			/** 
	        */
			void addPoint(const Ogre::Vector3& point);
				
			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);
	};

}
#endif
