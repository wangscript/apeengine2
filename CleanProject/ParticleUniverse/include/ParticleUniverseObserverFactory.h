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

#ifndef __PU_OBSERVER_FACTORY_H__
#define __PU_OBSERVER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseObserver.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This is the base factory of all ParticleObserver implementations.
    */
	class _ParticleUniverseExport ParticleObserverFactory : public ITokenInitialiser
	{
	    protected:

			/** 
	        */
			template <class T>
			ParticleObserver* _createObserver(void)
			{
				ParticleObserver* particleObserver = new T();
				particleObserver->setObserverType(getObserverType());
				return particleObserver;
			};

	public:
			ParticleObserverFactory(void) {};
	        virtual ~ParticleObserverFactory(void) {};

		    /** Returns the type of the factory, which identifies the particle observer type this factory creates. */
			virtual Ogre::String getObserverType() const = 0;

	        /** Creates a new observer instance.
		    @remarks
	        */
		    virtual ParticleObserver* createObserver(void) = 0;

			/** Delete an observer
	        */
			void destroyObserver (ParticleObserver* observer){delete observer;};
	};

}
#endif
