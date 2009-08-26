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

#ifndef __PU_EXTERN_FACTORY_H__
#define __PU_EXTERN_FACTORY_H__

#include "ParticleUniverseExtern.h"
#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This is the base factory of all Extern implementations.
    */
	class _ParticleUniverseExport ExternFactory : public ITokenInitialiser
	{
	    protected:

			/** 
	        */
			template <class T>
			Extern* _createExtern(void)
			{
				Extern* externObject = new T();
				externObject->setExternType(getExternType());
				return externObject;
			};

	public:
			ExternFactory(void){};
			virtual ~ExternFactory(void){};

		    /** Returns the type of the factory, which identifies the Extern type this factory creates. */
			virtual Ogre::String getExternType() const = 0;

	        /** Creates a new Extern instance.
		    @remarks
	        */
		    virtual Extern* createExtern(void) = 0;

			/** Delete an Extern.
	        */
			void destroyExtern (Extern* externObject){if (externObject) delete externObject;};
	};

}
#endif
