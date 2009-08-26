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

#ifndef __PU_ENTITY_RENDERER_H__
#define __PU_ENTITY_RENDERER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleUniverseIVisualData.h"

namespace ParticleUniverse
{
	/** Visual data specific for this type of renderer.
    */
	class _ParticleUniverseExport EntityRendererVisualData : public IVisualData
	{
		public:
			EntityRendererVisualData (Ogre::SceneNode* sceneNode) : IVisualData(), node(sceneNode){};
			Ogre::SceneNode* node;
			virtual void setVisible(bool visible)
			{
				if (node)
				{
					node->setVisible(visible);
				}
			};
	};

	/** The EntityRenderer class is responsible to render particles as an Entity.
    */
	class _ParticleUniverseExport EntityRenderer : public ParticleRenderer
	{
		public:
			enum EntityOrientationType
			{
				ENT_ORIENTED_SELF,
				ENT_ORIENTED_SELF_MIRRORED,
				ENT_ORIENTED_SHAPE
			};

			EntityRenderer(void);
	        virtual ~EntityRenderer(void);

			/** Get the mesh name.
			*/
			const Ogre::String& getMeshName(void) const;

			/** Set the mesh name.
			*/
			void setMeshName(const Ogre::String& meshName);

			/** Deletes all ChildSceneNodes en Entities.
			*/
			void _destroyAll(void);
			
			/** Disable all ChildSceneNodes.
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

			/** Rotate the textures of eacht entity.
			*/
			void _rotateTexture(VisualParticle* particle, Ogre::Entity* entity);

			/** 
			*/
			virtual void setRenderQueueGroup(Ogre::uint8 queueId);

			/** 
			*/
			virtual Ogre::SortMode _getSortMode(void) const;

			/** 
			*/
			const EntityOrientationType& getEntityOrientationType(void) const;

			/** 
			*/
			void setEntityOrientationType(const EntityOrientationType& entityOrientationType);

			/** 
			*/
			virtual void copyAttributesTo (ParticleRenderer* renderer);

		protected:
			std::vector<EntityRendererVisualData*> mAllVisualData;
			std::vector<EntityRendererVisualData*> mVisualData;
			std::vector<Ogre::Entity*> mEntities;
			size_t mQuota;
			Ogre::String mMeshName;
			Ogre::String mEntityName; // Used for random entity name prefix
			Ogre::Real mBoxWidth;
			Ogre::Real mBoxHeight;
			Ogre::Real mBoxDepth;
			bool mZRotated;
			EntityOrientationType mEntityOrientationType;
	};

}
#endif

