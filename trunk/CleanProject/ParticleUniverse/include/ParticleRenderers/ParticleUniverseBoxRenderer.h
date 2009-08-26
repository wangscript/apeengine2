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

#ifndef __PU_BOX_RENDERER_H__
#define __PU_BOX_RENDERER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleRenderers/ParticleUniverseBoxSet.h"

namespace ParticleUniverse
{
	/** The BoxRenderer class is responsible to render particles as a box.
    */
	class _ParticleUniverseExport BoxRenderer : public ParticleRenderer
	{
		protected:
			/** The Box set that's doing the rendering */
			BoxSet* mBoxSet;

		public:
			BoxRenderer(void);
	        virtual ~BoxRenderer(void);

			/** @copydoc ParticleRenderer::_prepare */
			virtual void _prepare(ParticleTechnique* technique);

			/** @copydoc ParticleRenderer::_updateRenderQueue */
			virtual void _updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool);

			/** @copydoc ParticleRenderer::_notifyAttached */
			virtual void _notifyAttached(Ogre::Node* parent, bool isTagPoint = false);

			/** @copydoc ParticleRenderer::_setMaterialName */
			void _setMaterialName(const Ogre::String& materialName);

			/** @copydoc ParticleRenderer::_notifyCurrentCamera */
			virtual void _notifyCurrentCamera(Ogre::Camera* cam);
	
			/** @copydoc ParticleRenderer::_notifyParticleQuota */
			virtual void _notifyParticleQuota(size_t quota);

			/** @copydoc ParticleRenderer::_notifyDefaultDimensions */
			virtual void _notifyDefaultDimensions(Ogre::Real width, Ogre::Real height, Ogre::Real depth);

			/** @copydoc ParticleRenderer::_notifyParticleResized */
			virtual void _notifyParticleResized(void);

			/** @copydoc ParticleRenderer::_notifyParticleZRotated */
			virtual void _notifyParticleZRotated(void);

			/** @copydoc ParticleRenderer::setRenderQueueGroup */
			virtual void setRenderQueueGroup(Ogre::uint8 queueId);

			/** @copydoc ParticleRenderer::_getSortMode */
			virtual Ogre::SortMode _getSortMode(void) const {return Ogre::SM_DISTANCE;};

			/** @copydoc ParticleRenderer::copyAttributesTo */
			virtual void copyAttributesTo (ParticleRenderer* renderer);

			/** Access BoxSet in use */
			BoxSet* getBoxSet(void) const { return mBoxSet; }

			/** @copydoc ParticleRenderer::setVisible */
			virtual void setVisible(bool visible);
	};

}
#endif
