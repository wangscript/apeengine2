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

#ifndef __PU_I_VISUALDATA_H__
#define __PU_I_VISUALDATA_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** This abstract class is used for assigning visual data to some other class. Visual data can be anything,
		from SceneNodes to specific renderdata.
	*/
	class _ParticleUniverseExport IVisualData
	{
		public:
			IVisualData(void) {};
			virtual ~IVisualData(void) {};
			virtual void setVisible(bool visible) = 0;
	};

}
#endif
