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

#ifndef __PU_SYSTEM_TOKENS_H__
#define __PU_SYSTEM_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed on a ParticleSystem level.
    */
	class _ParticleUniverseExport ParticleSystemTokens : public ITokenInitialiser
	{
		public:
			ParticleSystemTokens(void) {};
			virtual ~ParticleSystemTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

		protected:
			// Tokens which get called during parsing.
			class LodDistancesToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mLodDistancesToken;
			class SmoothLodToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSmoothLodToken;
			class IterationIntervalToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mIterationIntervalToken;
			class FixedTimeoutToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mFixedTimeoutToken;
			class NonVisibleUpdateTimeoutToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mNonVisibleUpdateTimeoutToken;
			class FastForwardToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mFastForwardToken;
			class MainCameraNameToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mMainCameraNameToken;
			class ScaleToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mScaleToken;
			class ScaleVelocityToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mScaleVelocityToken;
			class ScaleTimeToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mScaleTimeToken;
			class TightBoundingBoxToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mTightBoundingBoxToken;
	};

}
#endif
