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

#ifndef __PU_ONQUOTA_OBSERVER_FACTORY_H__
#define __PU_ONQUOTA_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnQuotaObserver.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnQuotaObserver.
    */
	class _ParticleUniverseExport OnQuotaObserverFactory : public ParticleObserverFactory
	{
		public:
			OnQuotaObserverFactory(void) {};
	        virtual ~OnQuotaObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual Ogre::String getObserverType(void) const
			{
				return "OnQuota";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnQuotaObserver>();
			}

			/** See ParticleObserverFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister){};
	};

}
#endif
