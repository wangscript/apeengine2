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

#ifndef __PU_PATH_FOLLOWER_FACTORY_H__
#define __PU_PATH_FOLLOWER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniversePathFollowerTokens.h"
#include "ParticleUniversePathFollower.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the PathFollower.
    */
	class _ParticleUniverseExport PathFollowerFactory : public ParticleAffectorFactory
	{
		public:
			PathFollowerFactory(void) {};
	        virtual ~PathFollowerFactory(void) {};

			/** See ParticleAffectorFactory */
			Ogre::String getAffectorType() const
			{
				return "PathFollower";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<PathFollower>();
			}

			/** See ParticleAffectorFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister)
			{
				// Delegate to mPathFollowerTokens
				mPathFollowerTokens.setupTokenDefinitions(tokenRegister);
			}

		protected:
			PathFollowerTokens mPathFollowerTokens;
	};

}
#endif
