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

#ifndef __PU_EMITTER_TOKENS_H__
#define __PU_EMITTER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed on an Emitter level.
    */
	class _ParticleUniverseExport ParticleEmitterTokens : public ITokenInitialiser
	{
		public:
			ParticleEmitterTokens(void) {};
			virtual ~ParticleEmitterTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

		protected:
			// Tokens which get called during parsing.
			class DirectionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mDirectionToken;
			class EmitsToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mEmitsToken;
			class AngleToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAngleToken;

			class EmissionRateToken : public IToken
			{
				virtual void parse(ParticleScriptParser* parser);
				virtual void postParse(ParticleScriptParser* parser);
			} mEmissionRateToken;

			class TimeToLiveToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mTimeToLiveToken;
			class MassToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mMassToken;
			class VelocityToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mVelocityToken;
			class DurationToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mDurationToken;
			class RepeatDelayToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mRepeatDelayToken;
			class ParticleAllDimensionsToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mParticleAllDimensionsToken;
			class ParticleWidthToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mParticleWidthToken;
			class ParticleHeightToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mParticleHeightToken;
			class ParticleDepthToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mParticleDepthToken;
			class AutoDirectionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAutoDirectionToken;
			class ForceEmissionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mForceEmissionToken;
			class ColourToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mColourToken;
			class ColourRangeStartToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mColourRangeStartToken;
			class ColourRangeEndToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mColourRangeEndToken;
	};

}
#endif
