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

#ifndef __PU_PLANE_COLLIDER_FACTORY_H__
#define __PU_PLANE_COLLIDER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniversePlaneColliderTokens.h"
#include "ParticleUniversePlaneCollider.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the PlaneCollider.
    */
	class _ParticleUniverseExport PlaneColliderFactory : public ParticleAffectorFactory
	{
		public:
			PlaneColliderFactory(void){};
	        virtual ~PlaneColliderFactory(void){};

			/** See ParticleAffectorFactory */
			Ogre::String getAffectorType() const
			{
				return "PlaneCollider";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<PlaneCollider>();
			}

			/** See ParticleAffectorFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister)
			{
				// Delegate to mPlaneColliderTokens
				mPlaneColliderTokens.setupTokenDefinitions(tokenRegister);
			}

	protected:
		PlaneColliderTokens mPlaneColliderTokens;
	};

}
#endif
