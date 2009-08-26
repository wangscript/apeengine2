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

#ifndef __PU_I_DEPENDENCY_H__
#define __PU_I_DEPENDENCY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** Abstract (pure virtual) dependency class
	@remarks
		In some cases, an attribute of a ParticleSystem or its underlying components (ParticleEmitter, ...) may 
		depend on another value that changes over time. The ´changing value´ is wrapped into a IDependency class
		and the attribute is ´continuesly´ changed by the IDependency subclass.
	*/
	class _ParticleUniverseExport IDependency : public IElement
	{
		public:
			IDependency(void) : IElement() {};
			virtual ~IDependency(void){};
	};

}
#endif
