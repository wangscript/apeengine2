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

#ifndef __PU_BOX_EMITTER_H__
#define __PU_BOX_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The BoxEmitter is a ParticleEmitter that emits particles within a box shape.
    */
	class _ParticleUniverseExport BoxEmitter : public ParticleEmitter
	{
		protected:
			Ogre::Real mHeight;
			Ogre::Real mWidth;
			Ogre::Real mDepth;

			Ogre::Real mXRange;
			Ogre::Real mYRange;
			Ogre::Real mZRange;

		public:
			BoxEmitter(void);
	        virtual ~BoxEmitter(void) {};

			/** 
	        */
			const Ogre::Real getHeight(void) const;
			void setHeight(const Ogre::Real height);

			/** 
	        */
			const Ogre::Real getWidth(void) const;
			void setWidth(const Ogre::Real width);

			/** 
	        */
			const Ogre::Real getDepth(void) const;
			void setDepth(const Ogre::Real depth);

			/** 
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
