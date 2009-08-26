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

#ifndef __PU_DOEXPIRE_EVENT_HANDLER_H__
#define __PU_DOEXPIRE_EVENT_HANDLER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEventHandler.h"

namespace ParticleUniverse
{
	/** The DoExpireEventHandler expires a particle.
    */
	class _ParticleUniverseExport DoExpireEventHandler : public ParticleEventHandler
	{
		protected:

		public:
			DoExpireEventHandler(void) : ParticleEventHandler()
			{
				mEventHandlerType = "DoExpire";
			};
	        virtual ~DoExpireEventHandler(void) {};

			/** Get indication that all particles are expired
	        */
			bool getExpireAll(void);

			/** Set indication that all particles are expired
	        */
			void setExpireAll(bool expireAll);

			/** 
	        */
			virtual void _handle (ParticleTechnique* particleTechnique, Particle* particle, Ogre::Real timeElapsed);
	};

}
#endif
