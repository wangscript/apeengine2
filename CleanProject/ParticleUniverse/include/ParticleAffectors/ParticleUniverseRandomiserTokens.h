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

#ifndef __PU_RANDOMISER_TOKENS_H__
#define __PU_RANDOMISER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed for the Randomiser.
    */
	class _ParticleUniverseExport RandomiserTokens : public ITokenInitialiser
	{
		public:
			RandomiserTokens(void) {};
			virtual ~RandomiserTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

		protected:
			/** Tokens which get called during parsing.
			*/
			class DeviationXToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mDeviationXToken;
			class DeviationYToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mDeviationYToken;
			class DeviationZToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mDeviationZToken;
			class RandomDirectionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mRandomDirectionToken;
			class TimeStepToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mTimeStepToken;
	};

}
#endif
