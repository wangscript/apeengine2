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

#ifndef __PU_BILLBOARD_RENDERER_H__
#define __PU_BILLBOARD_RENDERER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleUniverseTechnique.h"

namespace ParticleUniverse
{
	/** The BillboardRenderer class is responsible to render particles as a billboard.
    */
	class _ParticleUniverseExport BillboardRenderer : public ParticleRenderer
	{
		public:

			/** Alternative billboard type. 
			@remarks
				This is an extended version of Ogre's billboard type. It has BBT_ORIENTED_SHAPE added
				which basicly means that the billboard orientation is derived from the particle 
				orientation.
			*/
			enum BillboardType
			{
				BBT_POINT,
				BBT_ORIENTED_COMMON,
				BBT_ORIENTED_SELF,
				BBT_ORIENTED_SHAPE,
				BBT_PERPENDICULAR_COMMON,
				BBT_PERPENDICULAR_SELF
			};

			BillboardRenderer(void);
	        virtual ~BillboardRenderer(void);

			/** @copydoc ParticleRenderer::_prepare */
			virtual void _prepare(ParticleTechnique* technique);

			/** 
			*/
			void setBillboardType(BillboardType bbt);

			/** 
			*/
			BillboardType getBillboardType(void) const;

			/** 
			*/
			void setUseAccurateFacing(bool acc);

			/** 
			*/
			bool isUseAccurateFacing(void) const;

			/** 
			*/
			void setBillboardOrigin(Ogre::BillboardOrigin origin) { mBillboardSet->setBillboardOrigin(origin); }

			/** 
			*/
			Ogre::BillboardOrigin getBillboardOrigin(void) const { return mBillboardSet->getBillboardOrigin(); }

			/** 
			*/
			void setBillboardRotationType(Ogre::BillboardRotationType rotationType);

			/** 
			*/
			Ogre::BillboardRotationType getBillboardRotationType(void) const;

			/** 
			*/
			void setCommonDirection(const Ogre::Vector3& vec);

			/** 
			*/
			const Ogre::Vector3& getCommonDirection(void) const;

			/** 
			*/
			void setCommonUpVector(const Ogre::Vector3& vec);

			/** 
			*/
			const Ogre::Vector3& getCommonUpVector(void) const;

			/** 
			*/
			void setPointRenderingEnabled(bool enabled);

			/** 
			*/
			bool isPointRenderingEnabled(void) const;

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

			/** 
			*/
			Ogre::BillboardSet* getBillboardSet(void) const { return mBillboardSet; }

			/** @copydoc ParticleRenderer::setVisible */
			virtual void setVisible(bool visible);

		protected:
			/** 
			*/
			Ogre::BillboardSet* mBillboardSet;

			/** 
			*/
			BillboardType mBillboardType;
	};

}
#endif
