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

#ifndef __PU_POSITION_EMITTER_H__
#define __PU_POSITION_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The PositionEmitter is an emitter that emits particles from one or more given positions.
		The PositionEmitter enables building up a predefined structure out of particles. Imaging building up a
		wall that is made up from stone blocks. The particles are emitted on the positions that are added to this
		emitter. Adding some physical behaviour to the particles and you have your stone wall that collapses if a 
		force is applied to it.
    */
	class _ParticleUniverseExport PositionEmitter : public ParticleEmitter
	{
		protected:
			std::vector<Ogre::Vector3> mPositionList;
			bool mRandomized;
			size_t mIndex;

		public:
			PositionEmitter(void) : 
				ParticleEmitter(),
				mRandomized(true),
				mIndex(0)
			{
				mEmitterType = "Position";
			};
	        virtual ~PositionEmitter(void) {};

			/** 
	        */
			bool isRandomized() const;

			/** 
	        */
			void setRandomized(bool randomized);

			/** Add a new position to this emitter
	        */
			void addPosition(const Ogre::Vector3& position);

			/** Remove all positions from this emitter
	        */
			void removeAllPositions(void);

			/** See ParticleEmitter
			*/
			void _notifyStart(void);

			/** See ParticleEmitter
			*/
			virtual unsigned short _calculateRequestedParticles(Ogre::Real timeElapsed);

			/** Generate a particle position based on the added positions.
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
