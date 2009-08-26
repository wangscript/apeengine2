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

#ifndef __PU_LIGHT_RENDERER_TOKENS_H__
#define __PU_LIGHT_RENDERER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed for a LightRenderer.
    */
	class _ParticleUniverseExport LightRendererTokens : public ITokenInitialiser
	{
		protected:

		public:
			LightRendererTokens(void) {};
			virtual ~LightRendererTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

		protected:
			// Tokens which get called during parsing.
			class LightTypeToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mLightTypeToken;
			class QueueIdToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mQueueIdToken;
			class DiffuseColourToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mDiffuseColourToken;
			class SpecularColourToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSpecularColourToken;
			class AttenuationRangeToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAttenuationRangeToken;
			class AttenuationConstantToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAttenuationConstantToken;
			class AttenuationLinearToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAttenuationLinearToken;
			class AttenuationQuadraticToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAttenuationQuadraticToken;
			class SpotlightInnerAngleToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSpotlightInnerAngleToken;
			class SpotlightOuterAngleToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSpotlightOuterAngleToken;
			class SpotlightFalloffToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSpotlightFalloffToken;
			class PowerScaleToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mPowerScaleToken;
	};

}
#endif
