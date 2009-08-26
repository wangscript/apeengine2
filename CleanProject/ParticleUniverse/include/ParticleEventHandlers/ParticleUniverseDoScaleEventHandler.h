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

#ifndef __PU_DO_SCALE_EVENT_HANDLER_H__
#define __PU_DO_SCALE_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"

namespace ParticleUniverse
{
	/** The DoScaleEventHandler scales different particle attributes.
    */
	class _ParticleUniverseExport DoScaleEventHandler : public ParticleEventHandler
	{
		public:
			enum ScaleType
			{
				ST_TIME_TO_LIVE,
				ST_VELOCITY
			};

			DoScaleEventHandler(void) : 
				ParticleEventHandler(),
				mScaleFraction(0.2),
				mScaleType(ST_TIME_TO_LIVE)
			{
				mEventHandlerType = "DoScale";
			};
	        virtual ~DoScaleEventHandler(void) {};

			/** Returns the scale type
	        */
			const ScaleType& getScaleType(void) const;

			/** Set the scale type. This scale type identifies to which attribute the scale factor is applied.
	        */
			void setScaleType(const ScaleType& scaleType);

			/** Returns the scale fraction
	        */
			const Ogre::Real getScaleFraction(void) const;

			/** Set the scale fraction. This scale fraction value is used to scale different attributes if the 
				event handler is called.
	        */
			void setScaleFraction(const Ogre::Real scaleFraction);

			/** 
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** Copy attributes to another event handler.
	        */
			virtual void copyAttributesTo (ParticleEventHandler* eventHandler);

		protected:
			Ogre::Real mScaleFraction;
			ScaleType mScaleType;
	};

}
#endif
