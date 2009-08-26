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

#ifndef __PU_RENDERER_H__
#define __PU_RENDERER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseParticlePool.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** ParticleRenderer is a virtual class and must be subclassed. A subclass of ParticleRenderer is
		responsible for rendering the visual particles. 
	@remarks
		Several types of renderers are possible. A billboard- and a mesh- renderer are examples.
    */
	class _ParticleUniverseExport ParticleRenderer : public IAlias, public IElement
	{
		protected:
			ParticleTechnique* mParentTechnique;

			// The billboard set that's doing the rendering
			Ogre::BillboardSet* mBillboardSet;

			// Type of the renderer
			Ogre::String mRendererType;

			/* 
			*/
			bool mCullIndividual;

			/* 
			*/
			Ogre::Real mHeight;

			/* 
			*/
			Ogre::Real mWidth;

			/* 
			*/
			Ogre::Real mDepth;

			/** Determines whether the visual particles must be sorted.
	        */
			bool mSorted;

			/** Defines the renderqueue.
	        */
			Ogre::uint8 mQueueId;

			/** Determines whether renderer is initialised.
	        */
			bool mRendererInitialised;

			/** Although the scale is on a Particle System level, it is stored here also, because this value is often 
				used. It is a derived value, so it has not get a get and set function.
			*/
			Ogre::Vector3 _mParticleSystemScale;

		public:
			ParticleRenderer(void);
			virtual ~ParticleRenderer(void);

			/** 
	        */
			const Ogre::String& getRendererType(void) const;
			void setRendererType(Ogre::String rendererType);

			/** Get / set the parent.
	        */
			const ParticleTechnique* getParentTechnique(void) const;
			void setParentTechnique(ParticleTechnique* parentTechnique);

			/** Get / set whether the renderer is initialised.
	        */
			bool isRendererInitialised(void) const;
			void setRendererInitialised(bool rendererInitialised);

			/** Perform activities when a Renderer is started.
			*/
			virtual void _notifyStart(void){/* Do nothing */};

			/** Perform activities when a Renderer is stopped.
			*/
			virtual void _notifyStop(void){/* Do nothing */};

			/** Notify that the Particle System is rescaled.
	        */
			virtual void _notifyRescaled(const Ogre::Vector3& scale);

			/** To make currently displayed objects visible or not.
			*/
			virtual void setVisible(bool visible = true) = 0;

			/** Prepare the renderer before it can be used.
			*/
			virtual void _prepare(ParticleTechnique* technique) = 0;

			/** Updates the renderqueue
			@remarks
				The subclass must update the render queue using whichever Renderable instance(s) it wishes.
			*/
			virtual void _updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool) = 0;

			/** Sets the material this renderer must use; called by ParticleTechnique. */
			virtual void _setMaterialName(const Ogre::String& materialName) = 0;

			/** Delegated to by ParticleTechnique::_notifyCurrentCamera */
			virtual void _notifyCurrentCamera(Ogre::Camera* cam) = 0;
	
			/** Delegated to by ParticleTechnique::_notifyAttached */
			virtual void _notifyAttached(Ogre::Node* parent, bool isTagPoint = false) = 0;

			/** The particle quota has changed */
			virtual void _notifyParticleQuota(size_t quota) = 0;

			/** The particle default size has changed */
			virtual void _notifyDefaultDimensions(Ogre::Real width, Ogre::Real height, Ogre::Real depth) = 0;

			/** Callback when particles are resized */
			virtual void _notifyParticleResized(void) = 0;

			/** Callback when particles are rotated */
			virtual void _notifyParticleZRotated(void) {}

			/** Sets renderqueue group */
			virtual void setRenderQueueGroup(Ogre::uint8 queueId);

			/** Get renderqueue group */
			virtual Ogre::uint8 getRenderQueueGroup(void) const;
			
			/** Gets the particles sort mode */
			virtual Ogre::SortMode _getSortMode(void) const = 0;

			/** Returns whether the particles are sorted */
			bool isSorted(void) const;

			/** Determines whether the particles are sorted */
			void setSorted(bool sorted);

			/** Copy attributes to another renderer.
	        */
			virtual void copyAttributesTo (ParticleRenderer* renderer);
	};

}
#endif
