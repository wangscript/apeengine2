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

#ifndef __PU_LINE_AFFECTOR_FACTORY_H__
#define __PU_LINE_AFFECTOR_FACTORY_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseLineAffectorTokens.h"
#include "ParticleUniverseLineAffector.h"
#include "ParticleUniverseAffectorFactory.h"

namespace ParticleUniverse
{
	/** Factory class responsible for creating the LineAffector.
    */
	class _ParticleUniverseExport LineAffectorFactory : public ParticleAffectorFactory
	{
		public:
			LineAffectorFactory(void) {};
	        virtual ~LineAffectorFactory(void) {};

			/** See ParticleAffectorFactory */
			Ogre::String getAffectorType() const
			{
				return "Line";
			}

			/** See ParticleAffectorFactory  */
			ParticleAffector* createAffector(void)
			{
				return _createAffector<LineAffector>();
			}

			/** See ParticleAffectorFactory */
			virtual void setupTokenDefinitions(ITokenRegister* tokenRegister)
			{
				// Delegate to mLineAffectorTokens
				mLineAffectorTokens.setupTokenDefinitions(tokenRegister);
			}

		protected:
			LineAffectorTokens mLineAffectorTokens;
	};

}
#endif
