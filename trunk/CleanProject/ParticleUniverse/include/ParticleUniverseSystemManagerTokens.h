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

#ifndef __PU_SYSTEM_MANAGER_TOKENS_H__
#define __PU_SYSTEM_MANAGER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed on a ParticleSystemManager level.
    */
	class _ParticleUniverseExport ParticleSystemManagerTokens : public ITokenInitialiser
	{
		protected:

		public:
			ParticleSystemManagerTokens(void) {};
			virtual ~ParticleSystemManagerTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

			// Tokens which get called during parsing.
			class OpenBraceToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mOpenBraceToken;
			class CloseBraceToken : public IToken {	virtual void parse(ParticleScriptParser* parser);} mCloseBraceToken;
			class AliasToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAliasToken;
			class UseAliasToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mUseAliasToken;
			class SystemToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mSystemToken;
			class TechniqueToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mTechniqueToken;
			class RendererToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mRendererToken;
			class EmitterToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mEmitterToken;
			class AffectorToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mAffectorToken;
			class ObserverToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mObserverToken;
			class EventHandlerToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mEventHandlerToken;
			class BehaviourToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mBehaviourToken;
			class ExternToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mExternToken;
			class EnabledToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mEnabledToken;
			class PositionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mPositionToken;
			class KeepLocalToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mKeepLocalToken;
			class CameraDependencyToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mCameraDependencyToken;
	};

}
#endif
