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

#ifndef __PU_MESH_SURFACE_EMITTER_TOKENS_H__
#define __PU_MESH_SURFACE_EMITTER_TOKENS_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This class contains the tokens that are needed for the MeshSurfaceEmitter.
    */
	class _ParticleUniverseExport MeshSurfaceEmitterTokens : public ITokenInitialiser
	{
		public:
			MeshSurfaceEmitterTokens(void) {};
			virtual ~MeshSurfaceEmitterTokens(void) {};

			/** @see
				ITokenInitialiser::setupTokenDefinitions
			*/
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister);

		protected:
			// Tokens which get called during parsing.
			class MeshNameToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mMeshNameToken;
			class DistributionToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mDistributionToken;
			class ScaleToken : public IToken {virtual void parse(ParticleScriptParser* parser);} mScaleToken;
	};

}
#endif
