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

#ifndef __PU_MESH_SURFACE_EMITTER_FACTORY_H__
#define __PU_MESH_SURFACE_EMITTER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitterFactory.h"
#include "ParticleUniverseMeshSurfaceEmitterTokens.h"
#include "ParticleUniverseMeshSurfaceEmitter.h"

namespace ParticleUniverse
{
	/** This is the factory class that is responsible for creating a MeshSurfaceEmitter.
    */
	class _ParticleUniverseExport MeshSurfaceEmitterFactory : public ParticleEmitterFactory
	{
		protected:
			MeshSurfaceEmitterTokens mMeshSurfaceEmitterTokens;

		public:
			MeshSurfaceEmitterFactory(void) {};
	        virtual ~MeshSurfaceEmitterFactory(void) {};

            /** See ParticleEmitterFactory */
			Ogre::String getEmitterType() const
			{
				return "MeshSurface";
			}

			/** See ParticleEmitterFactory */
			ParticleEmitter* createEmitter(void)
			{
				return _createEmitter<MeshSurfaceEmitter>();
			}

			/** See ParticleEmitterFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister)
			{
				// Delegate to mMeshSurfaceEmitterTokens
				mMeshSurfaceEmitterTokens.setupTokenDefinitions(tokenRegister);
			}
	};

}
#endif
