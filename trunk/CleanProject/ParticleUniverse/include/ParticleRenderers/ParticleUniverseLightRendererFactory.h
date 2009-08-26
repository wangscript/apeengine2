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

#ifndef __PU_LIGHT_RENDERER_FACTORY_H__
#define __PU_LIGHT_RENDERER_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRendererFactory.h"
#include "ParticleUniverseLightRenderer.h"
#include "ParticleUniverseLightRendererTokens.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating a LightRenderer.
    */
	class _ParticleUniverseExport LightRendererFactory : public ParticleRendererFactory
	{
		public:
			LightRendererFactory(void) {};
	        virtual ~LightRendererFactory(void) {};

			/** See ParticleRendererFactory */
			Ogre::String getRendererType() const
			{
				return "Light";
			}

			/** See ParticleRendererFactory */
			ParticleRenderer* createRenderer(void)
			{
				return _createRenderer<LightRenderer>();
			}

			/** See ParticleRendererFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister)
			{
				// Delegate to mLightRendererTokens
				mLightRendererTokens.setupTokenDefinitions(tokenRegister);
			}

		protected:
			LightRendererTokens mLightRendererTokens;
	};

}
#endif
