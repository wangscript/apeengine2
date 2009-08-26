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

#ifndef __PU_I_ELEMENT_H__
#define __PU_I_ELEMENT_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** The IElement is used to identify classes that must be set as part of a section in case a script is
		parsed.
	@remarks
		I.e. If the parses encounters a ´technique´ section in a particle universe script, a ParticleTechnique
		object is created and must be set in the current section of the Context object. the
		ParticleTechnique object must be of type IElement to be stored in the Context object.
	*/
	class _ParticleUniverseExport IElement
	{
		public:
			IElement(void) {};
			virtual ~IElement(void) {};
	};

}
#endif
