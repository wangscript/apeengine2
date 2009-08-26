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

#ifndef __PU_BEHAVIOUR_FACTORY_H__
#define __PU_BEHAVIOUR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenInitialiser.h"

namespace ParticleUniverse
{
	/** This is the base factory of all ParticleBehaviour implementations.
    */
	class _ParticleUniverseExport ParticleBehaviourFactory : public ITokenInitialiser
	{
	    protected:
			/** 
	        */
			template <class T>
			ParticleBehaviour* _createBehaviour(void)
			{
				ParticleBehaviour* particleBehaviour = new T();
				particleBehaviour->setBehaviourType(getBehaviourType());
				return particleBehaviour;
			};

	public:
			ParticleBehaviourFactory(void) {};
			virtual ~ParticleBehaviourFactory(void){};

		    /** Returns the type of the factory, which identifies the particle behaviour type this factory creates. */
			virtual Ogre::String getBehaviourType() const = 0;

	        /** Creates a new behaviour instance.
		    @remarks
	        */
		    virtual ParticleBehaviour* createBehaviour(void) = 0;

			/** Delete a behaviour
	        */
			void destroyBehaviour (ParticleBehaviour* behaviour){delete behaviour;};
	};

}
#endif
