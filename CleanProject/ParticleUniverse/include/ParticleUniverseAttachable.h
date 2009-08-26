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

#ifndef __PU_ATTACHABLE_H__
#define __PU_ATTACHABLE_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseExtern.h"

namespace ParticleUniverse
{
	/** The Attachable is a MovableObject that can be registered at a ParticleSystem as an Extern. By means
		of this construction it is possible to make a dependency between the 2 MovableObjects.
		This can be convenient if the Attachable is a Particle Affector wrapper, that affects a particle
		based on their mutual distance.
	@remarks
		This MovableObject will not be registered at the SceneManager; its purpose is to take advantage of the
		fact that it can be attached to a SceneNode. If an inherited class of Attachable uses visual (rendering)
		elements, it should use the registerAttachable() and unregisterAttachable() functions of the 
		ParticleSystemManager. This implies some additional coding, because this is not supported by the
		scripting capabilities.
    */
	class _ParticleUniverseExport Attachable : public Extern, public Ogre::MovableObject
	{
		public:
			Attachable(void) :
				Extern(),
				MovableObject(),
				mAABB(),
				mDistanceThreshold(std::numeric_limits<float>::max()),
				mDistanceThresholdSet(false)
			{
				// The Movableobject name is auto generated to prevent a clash in Ogre
				mBoundingRadius = 1;
				std::stringstream ss; 
				ss << this;
				MovableObject::mName = "PUExtern" + ss.str();
			};
	        virtual ~Attachable(void){};

			static Ogre::String PU_ATTACHABLE;

			/** Get the Distance Threshold
			*/
			const Ogre::Real getDistanceThreshold(void) const;

			/** Set the Distance Threshold. This threshold defines at which distance the Attachable doesn't influence 
				the particle anymore.
			*/
			void setDistanceThreshold(const Ogre::Real distanceThreshold);

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			void _notifyAttached(Ogre::Node* parent, bool isTagPoint = false);

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			virtual void _notifyCurrentCamera(Ogre::Camera* cam);

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			const Ogre::String& getMovableType(void) const;

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			const Ogre::AxisAlignedBox& getBoundingBox(void) const;

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			virtual Ogre::Real getBoundingRadius(void) const;
			
			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			virtual void _updateRenderQueue(Ogre::RenderQueue* queue);

			/** @see MovableObject
		    */
			virtual void visitRenderables(Ogre::Renderable::Visitor* visitor,
				bool debugRenderables = false) {/* No implementation */};

			/** Copy attributes to another Extern object.
	        */
			virtual void copyAttributesTo (Extern* externObject);

			/** Perform initialisation actions.
	        */
			virtual void _prepare(ParticleTechnique* technique);

			/** Actually processes a particle.
	        */
			virtual void _interface(ParticleTechnique* technique, 
				Particle* particle, 
				Ogre::Real timeElapsed);

		protected:
			Ogre::AxisAlignedBox mAABB;
			Ogre::Real mBoundingRadius;
			Ogre::Real mDistanceThreshold;
			bool mDistanceThresholdSet;
	};

}
#endif
