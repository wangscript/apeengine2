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

#ifndef __PU_ONEXPIRE_OBSERVER_FACTORY_H__
#define __PU_ONEXPIRE_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserverFactory.h"
#include "ParticleUniverseOnExpireObserver.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the OnExpireObserver.
    */
	class _ParticleUniverseExport OnExpireObserverFactory : public ParticleObserverFactory
	{
		public:
			OnExpireObserverFactory(void) {};
	        virtual ~OnExpireObserverFactory(void) {};

			/** See ParticleObserverFactory */
			virtual Ogre::String getObserverType(void) const
			{
				return "OnExpire";
			}

			/** See ParticleObserverFactory */
			virtual ParticleObserver* createObserver(void)
			{
				return _createObserver<OnExpireObserver>();
			}

			/** See ParticleObserverFactory
			@remarks
				This observer doesn't have attributes */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister){}

		protected:
	};

}
#endif
