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

#ifndef __PU_COLOUR_AFFECTOR_H__
#define __PU_COLOUR_AFFECTOR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseAffector.h"

namespace ParticleUniverse
{
	/** This affector is typically used to change the colour of a particle during its lifetime.
    */
	class _ParticleUniverseExport ColourAffector : public ParticleAffector
	{
		public:
			typedef std::map<Ogre::Real, Ogre::ColourValue> ColourMap;
			typedef std::map<Ogre::Real, Ogre::ColourValue>::iterator ColourMapIterator;
			enum ColourOperation
			{
				CAO_MULTIPLY,
				CAO_SET
			};

			// Constructor
			ColourAffector(void) : 
				ParticleAffector(),
				mColourOperation(CAO_SET)
			{
				mAffectorType = "Colour";
			};

			// Destructor
	        virtual ~ColourAffector(void) {};

			/** 
	        */
			void addColour(Ogre::Real timeFraction, const Ogre::ColourValue& colour);
				
			/** 
	        */
			ColourMapIterator _findNearestColourMapIterator(Ogre::Real timeFraction);

			/** 
	        */
			const ColourOperation& getColourOperation (void) const;

			/** 
	        */
			void setColourOperation (const ColourOperation& colourOperation);

			/** 
	        */
			virtual void _affect(ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);

			/** @copydoc ParticleAffector::copyAttributesTo */
			virtual void copyAttributesTo (ParticleAffector* affector);

		protected:
			ColourMap mColourMap;
			ColourOperation mColourOperation;
	};

}
#endif
