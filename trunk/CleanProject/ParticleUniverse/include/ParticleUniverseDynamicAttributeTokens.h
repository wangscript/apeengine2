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

#ifndef __PU_DYNAMIC_ATTRIBUTE_TOKENS_H__
#define __PU_DYNAMIC_ATTRIBUTE_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed on a DynamicAttribute level.
    */
	class _ParticleUniverseExport DynamicAttributeTokens : public ITokenInitialiser
	{
		public:
			DynamicAttributeTokens(void) {};
			virtual ~DynamicAttributeTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

		protected:
			// Tokens which get called during parsing.
			class ControlPointToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mControlPointToken;
			class MinimumToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mMinimumToken;
			class MaximumToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mMaximumToken;
			class FrequencyToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mFrequencyToken;
			class PhaseToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mPhaseToken;
			class BaseToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mBaseToken;
			class AmplitudeToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAmplitudeToken;
			class TypeToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mTypeToken;
	};

}
#endif
