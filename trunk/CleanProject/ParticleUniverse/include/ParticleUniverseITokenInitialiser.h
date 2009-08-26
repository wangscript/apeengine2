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

#ifndef __PU_I_TOKEN_INITIALISER_H__
#define __PU_I_TOKEN_INITIALISER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenRegister.h"

namespace ParticleUniverse
{
	/*	The ITokenInitialiser is used to define the relation between a token in a particle script and the funtion
		that is called to interpret that token.
	@remarks
		A ´token´ represents a function that is used for parsing a particular part of a particle script.
		A class that implements the ITokenInitialiser, must have both a function that defines these ´tokens´.
		The ITokenInitialiser establishes the relation between a token (i.e. keyword) in the script and the function that 
		is called by the parser to interpret that part of the script.
	*/
	class _ParticleUniverseExport ITokenInitialiser
    {

		public:
			ITokenInitialiser(void) {};
			virtual ~ITokenInitialiser(void) {};

			/** Child classes must implement this pure virtual function, in which the relation between the 'token'
				in the script and a particular function that is used to parse that part of the script, is defined.
			**/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister) = 0;
	};

}
#endif
