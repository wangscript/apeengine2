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

#ifndef __PU_SPHERE_COLLIDER_FACTORY_H__
#define __PU_SPHERE_COLLIDER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSphereColliderTokens.h"
#include "ParticleUniverseSphereCollider.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the SphereCollider.
    */
	class _ParticleUniverseExport SphereColliderFactory : public ParticleAffectorFactory
	{
		public:
			SphereColliderFactory(void){};
	        virtual ~SphereColliderFactory(void){};

			/** See ParticleAffectorFactory */
			Ogre::String getAffectorType() const
			{
				return "SphereCollider";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<SphereCollider>();
			}

			/** See ParticleAffectorFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister)
			{
				// Delegate to mSphereColliderTokens
				mSphereColliderTokens.setupTokenDefinitions(tokenRegister);
			}

	protected:
		SphereColliderTokens mSphereColliderTokens;
	};

}
#endif
