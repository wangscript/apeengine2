/*
-----------------------------------------------------------------------------
This source file is part of the Particle Universe product.

Copyright (c) 2006-2007 [company name here]

Usage of this program is free for non-commercial use and licensed under the
the terms of the GNU Lesser General Public License.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.

You may alternatively use this source for commercial use under the terms of a
specific version of the [company name here] Commercial License provided you 
have obtained such a license from [company name here].
-----------------------------------------------------------------------------
*/

#ifndef __PU_PARTICLE_TOKENS_H__
#define __PU_PARTICLE_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed on a Particle level.
    */
	class _ParticleUniverseExport ParticleTokens : public ITokenInitialiser
	{
		protected:

		public:
			ParticleTokens(void) {};
			virtual ~ParticleTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

			// Tokens which get called during parsing.
			class PositionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mPositionToken;
			class DirectionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mDirectionToken;
	};

}
#endif
