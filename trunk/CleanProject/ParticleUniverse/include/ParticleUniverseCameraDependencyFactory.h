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

#ifndef __PU_CAMERA_DEPENDECY_FACTORY_H__
#define __PU_CAMERA_DEPENDECY_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseCameraDependency.h"

namespace ParticleUniverse
{
	/** This is the factory class with which a CameraDependency is created.
    */
	class _ParticleUniverseExport CameraDependencyFactory
	{
	    public:

			CameraDependencyFactory(void) {};
	        virtual ~CameraDependencyFactory(void) {};

			/** 
	        */
			CameraDependency* create(void)
			{
				return new CameraDependency();
			};

			/** 
	        */
			CameraDependency* create(Ogre::Real threshold, bool inc)
			{
				return new CameraDependency(threshold, inc);
			};

			/** 
	        */
			CameraDependency* clone(CameraDependency* cameraDependency)
			{
				if (cameraDependency)
				{
					CameraDependency* newCameraDependency = create();
					cameraDependency->copyAttributesTo(newCameraDependency);
					return newCameraDependency;
				}

				return 0;
			}
			
			/** Delete a CameraDependency
	        */
			void destroy (CameraDependency* cameraDependency){delete cameraDependency;};
	};

}
#endif
