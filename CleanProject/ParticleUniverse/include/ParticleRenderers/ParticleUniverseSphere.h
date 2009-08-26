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

#ifndef __PU_SPHERE_H__
#define __PU_SPHERE_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	class SphereSet;

	/** 
    */
	class _ParticleUniverseExport Sphere
	{
		friend class SphereSet;
		friend class SphereRenderer;

		protected:
			bool mOwnRadius;
			Ogre::Real mRadius;
			bool mRadiusChanged;

		public:
			Ogre::Vector3 mPosition;
			Ogre::ColourValue mColour;
			Ogre::Quaternion mOrientation;
			SphereSet* mParentSet;
			
			/** Default constructor.
			*/
			Sphere(void);

			/** Default destructor.
			*/
	        virtual ~Sphere(void);

			/** Constructor as called by SphereSet.
			*/
			Sphere(const Ogre::Vector3& position, SphereSet* owner);

			/** 
			*/
			void setPosition(const Ogre::Vector3& position);

			/** 
			*/
			void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);

			/** 
			*/
			const Ogre::Vector3& getPosition(void) const;

			/** Sets the colour of this sphere.
			*/
			void setColour(const Ogre::ColourValue& colour);

			/** Get the colour of this sphere.
			*/
			const Ogre::ColourValue& getColour(void) const;
		
			/** Resets this sphere to use the parent SphereSet's radius instead of it's own.
			*/
			void resetRadius(void) { mOwnRadius = false; }

			/** Sets the radius for this sphere.
			*/
			void setRadius(Ogre::Real radius);

			/** Returns true if this box deviates from the SphereSet's default radius.
			*/
			bool hasOwnRadius(void) const;

			/** Retrieves the sphere's personal radius, if hasOwnRadius is true.
			*/
			Ogre::Real getOwnRadius(void) const;

			/** Internal method for notifying the box of it's owner.
			*/
			void _notifyOwner(SphereSet* owner);
	};

}
#endif
