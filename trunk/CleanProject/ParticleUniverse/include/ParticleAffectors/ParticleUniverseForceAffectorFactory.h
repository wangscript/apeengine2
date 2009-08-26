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

#ifndef __PU_FORCE_AFFECTOR_FACTORY_H__
#define __PU_FORCE_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseForceAffectorTokens.h"
#include "ParticleUniverseForceAffector.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** This factory is just a dummy factory and only used to register generic ForceAffector tokens.
    */
	class _ParticleUniverseExport ForceAffectorFactory : public ParticleAffectorFactory
	{
		protected:
			ForceAffectorTokens mForceAffectorTokens;

		public:
			ForceAffectorFactory(void) {};
	        virtual ~ForceAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			Ogre::String getAffectorType(void) const
			{
				return "Dummy01"; // Dummy Factory, only for setting up token definitions.
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED, "PU: ForceAffectorFactory is a dummy factory.", 
					"ForceAffectorFactory::createAffector");
			}

			/** See ParticleAffectorFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister)
			{
				// Delegate to mForceAffectorTokens
				mForceAffectorTokens.setupTokenDefinitions(tokenRegister);
			}
	};

}
#endif
