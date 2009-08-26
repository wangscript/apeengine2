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

#ifndef __PU_TECHNIQUE_TOKENS_H__
#define __PU_TECHNIQUE_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed on a Technique level.
    */
	class _ParticleUniverseExport ParticleTechniqueTokens : public ITokenInitialiser
	{
		public:
			ParticleTechniqueTokens(void) {};
			virtual ~ParticleTechniqueTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

		protected:
			// Tokens which get called during parsing.
			class VisualParticleQuotaToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mVisualParticleQuotaToken;
			class EmittedEmitterQuotaToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mEmittedEmitterQuotaToken;
			class EmittedTechniqueQuotaToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mEmittedTechniqueQuotaToken;
			class EmittedAffectorQuotaToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mEmittedAffectorQuotaToken;
			class EmittedSystemQuotaToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mEmittedSystemQuotaToken;
			class MaterialToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mMaterialToken;
			class LodIndexToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mLodIndexToken;
			class SpatialHashingCellDimensionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSpatialHashingCellDimensionToken;
			class SpatialHashingCellOverlapToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSpatialHashingCellOverlapToken;
			class SpatialHashTableSizeToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSpatialHashTableSizeToken;
			class SpatialHashingUpdateIntervalToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSpatialHashingUpdateIntervalToken;
			class MaxVelocityToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mMaxVelocityToken;

			class WidthToken : public IToken
			{
				virtual void parse(ParticleScriptParser* parser);
				virtual void postParse(ParticleScriptParser* parser);
			} mWidthToken;

			class HeightToken : public IToken
			{
				virtual void parse(ParticleScriptParser* parser);
				virtual void postParse(ParticleScriptParser* parser);
			} mHeightToken;
			
			class DepthToken : public IToken
			{
				virtual void parse(ParticleScriptParser* parser);
				virtual void postParse(ParticleScriptParser* parser);
			} mDepthToken;
	};

}
#endif
