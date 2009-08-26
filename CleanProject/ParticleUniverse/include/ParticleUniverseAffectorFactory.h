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

#ifndef __PU_AFFECTOR_FACTORY_H__
#define __PU_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This is the base factory of all ParticleAffector implementations.
    */
	class _ParticleUniverseExport ParticleAffectorFactory : public ITokenInitialiser
	{
	    protected:

			/** 
	        */
			template <class T>
			ParticleAffector* _createAffector(void)
			{
				ParticleAffector* particleAffector = new T();
				particleAffector->setAffectorType(getAffectorType());
				return particleAffector;
			};

	public:
			ParticleAffectorFactory(void) {};
	        virtual ~ParticleAffectorFactory(void) {};

		    /** Returns the type of the factory, which identifies the particle affector type this factory creates. */
			virtual Ogre::String getAffectorType() const = 0;

	        /** Creates a new affector instance.
		    @remarks
	        */
		    virtual ParticleAffector* createAffector(void) = 0;

			/** Delete an affector
	        */
			void destroyAffector (ParticleAffector* affector){delete affector;};
	};

}
#endif
