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

#ifndef __PU_ONRANDOM_OBSERVER_FACTORY_H__
#define __PU_ONRANDOM_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnRandomObserverTokens.h"
#include "ParticleUniverseOnRandomObserver.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnRandomObserver.
    */
	class _ParticleUniverseExport OnRandomObserverFactory : public ParticleObserverFactory
	{
		public:
			OnRandomObserverFactory(void) {};
	        virtual ~OnRandomObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual Ogre::String getObserverType(void) const
			{
				return "OnRandom";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnRandomObserver>();
			}

			/** See ParticleObserverFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister)
			{
				// Delegate to mOnRandomObserverTokens
				mOnRandomObserverTokens.setupTokenDefinitions(tokenRegister);
			}

		protected:
			OnRandomObserverTokens mOnRandomObserverTokens;
	};

}
#endif
