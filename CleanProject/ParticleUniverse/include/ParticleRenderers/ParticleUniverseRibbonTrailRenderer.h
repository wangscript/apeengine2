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

#ifndef __PU_RIBBONTRAIL_RENDERER_H__
#define __PU_RIBBONTRAIL_RENDERER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"

namespace ParticleUniverse
{
	/** Visual data specific for this type of renderer.
    */
	class _ParticleUniverseExport RibbonTrailRendererVisualData : public IVisualData
	{
		public:
			RibbonTrailRendererVisualData (Ogre::SceneNode* sceneNode, Ogre::RibbonTrail* ribbonTrail) : 
				IVisualData(), 
				node(sceneNode),
				trail(ribbonTrail),
				addedToTrail(false),
				index(0){};

			Ogre::SceneNode* node;
			bool addedToTrail;
			Ogre::RibbonTrail* trail;
			size_t index;
			virtual void setVisible(bool visible)
			{
				if (visible)
				{
					if (!addedToTrail)
					{
						trail->addNode(node);
						addedToTrail = true;
					}
				}
				else
				{
					if (addedToTrail)
					{
						// What?
					}
				}
			};
	};

	/** The RibbonTrailRenderer class is responsible to render particles as a RibbonTrail.
    */
	class _ParticleUniverseExport RibbonTrailRenderer : public ParticleRenderer
	{
		protected:
			std::vector<RibbonTrailRendererVisualData*> mAllVisualData;
			std::vector<RibbonTrailRendererVisualData*> mVisualData;
			size_t mQuota;
			Ogre::RibbonTrail* mTrail;
			Ogre::String mRibbonTrailName;
			bool mUseVertexColours;
			size_t mMaxChainElements;
			Ogre::Real mTrailLength;
			Ogre::Real mTrailWidth;
			bool mRandomInitialColour;
			bool mSetLength;
			bool mSetWidth;
			Ogre::ColourValue mInitialColour;
			Ogre::ColourValue mColourChange;

		public:
			RibbonTrailRenderer(void);
	        virtual ~RibbonTrailRenderer(void);


			/** Getters and Setters
			*/
			bool isUseVertexColours(void) const;
			void setUseVertexColours(bool useVertexColours);

			size_t getMaxChainElements(void) const;
			void setMaxChainElements(size_t maxChainElements);

			Ogre::Real getTrailLength(void) const;
			void setTrailLength(Ogre::Real trailLength);

			Ogre::Real getTrailWidth(void) const;
			void setTrailWidth(Ogre::Real trailWidth);

			bool isRandomInitialColour(void) const;
			void setRandomInitialColour(bool randomInitialColour);

			const Ogre::ColourValue& getInitialColour(void) const;
			void setInitialColour(const Ogre::ColourValue& initialColour);

			const Ogre::ColourValue& getColourChange(void) const;
			void setColourChange(const Ogre::ColourValue& colourChange);

			/** Deletes all ChildSceneNodes en Entities.
			*/
			void _destroyAll(void);
			
			/** Enable the RibbonTrail
			*/
			virtual void _notifyStart(void);

			/** Disable the RibbonTrail
			*/
			virtual void _notifyStop(void);
			
			/** Make all objects visible or invisible.
			*/
			virtual void setVisible(bool visible);

			/** @copydoc ParticleRenderer::_prepare */
			virtual void _prepare(ParticleTechnique* technique);

			/** 
			*/
			virtual void _updateRenderQueue(Ogre::RenderQueue* queue, ParticlePool* pool);

			/** 
			*/
			virtual void _notifyAttached(Ogre::Node* parent, bool isTagPoint = false);

			/** @copydoc ParticleRenderer::_setMaterialName */
			virtual void _setMaterialName(const Ogre::String& materialName);

			/** 
			*/
			virtual void _notifyCurrentCamera(Ogre::Camera* cam);
	
			/** 
			*/
			virtual void _notifyParticleQuota(size_t quota);

			/** 
			*/
			virtual void _notifyDefaultDimensions(Ogre::Real width, Ogre::Real height, Ogre::Real depth);

			/** 
			*/
			virtual void _notifyParticleResized(void);

			/** 
			*/
			virtual void _notifyParticleZRotated(void);

			/** 
			*/
			virtual void setRenderQueueGroup(Ogre::uint8 queueId);

			/** 
			*/
			virtual Ogre::SortMode _getSortMode(void) const;

			/** 
			*/
			virtual void copyAttributesTo (ParticleRenderer* renderer);
	};

}
#endif

