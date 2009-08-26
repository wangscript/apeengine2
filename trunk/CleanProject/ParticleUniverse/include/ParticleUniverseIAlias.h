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

#ifndef __PU_I_ALIAS_H__
#define __PU_I_ALIAS_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** Abstract (pure virtual) alias class
	@remarks
		The IAlias class acts as an interface and is used to represent all other classes that are a child of the
		IAlias class. This typically concerns entities that are used in the Particle Universe scripts and for
		which it is possible to define an alias (i.e. ParticleTechnique, ParticleEmitter and ParticleAffector).
	*/
	class _ParticleUniverseExport IAlias
	{
		public:
			enum AliasType
			{
				AT_UNDEFINED,
				AT_TECHNIQUE,
				AT_RENDERER,
				AT_EMITTER,
				AT_AFFECTOR,
				AT_OBSERVER,
				AT_EXTERN,
				AT_HANDLER,
				AT_BEHAVIOUR
			};

			IAlias(void) : 
				mAliasName(Ogre::StringUtil::BLANK),
				mAliasType(AT_UNDEFINED) {};
			virtual ~IAlias(void) {};

			/** 
			*/
			const Ogre::String& getAliasName(void) const {return mAliasName;};
			void setAliasName(Ogre::String aliasName) {mAliasName = aliasName;};

			/** 
			*/
			const AliasType getAliasType(void) const {return mAliasType;};
			void setAliasType(AliasType aliasType) {mAliasType = aliasType;};

		protected:
			Ogre::String mAliasName;
			AliasType mAliasType;
	};

}
#endif
