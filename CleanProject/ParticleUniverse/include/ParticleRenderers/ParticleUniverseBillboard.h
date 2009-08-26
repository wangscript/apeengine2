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

#ifndef __PU_BILLBOARD_H__
#define __PU_BILLBOARD_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** This is a child of the Ogre Billboard class, with the exception that it has new friends ;-)
    */
	class _ParticleUniverseExport Billboard : public Ogre::Billboard
	{
        friend class BillboardRenderer;

		public:
			Billboard(void) : Ogre::Billboard(){};
	        virtual ~Billboard(void){};
	};

}
#endif
