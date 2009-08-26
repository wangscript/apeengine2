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

#ifndef __PU_I_GRAMMAR_H__
#define __PU_I_GRAMMAR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseITokenRegister.h"

namespace ParticleUniverse
{
	/*	Abstract Grammar class
	@remarks
		Each plugin containing emitters, affectors, etc. should have its own Backus - Naur grammar and has
		to implement some virtual functions.
		The plugin must provide the rules list, which looks like "| {<r1>} | {<r2>} | {<r3>} | {<r4>}", and also
		the details (properties) of each emitter, affector, etc. Both the rules list and the details are combined
		with the overall BNF grammar.
	*/
	class _ParticleUniverseExport IGrammar
    {
		public:
			IGrammar(void) {};
			virtual ~IGrammar(void) {};
			virtual const Ogre::String& getParticleRendererPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleRendererDetailedPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleEmitterPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleEmitterDetailedPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleAffectorPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleAffectorDetailedPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleObserverPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleObserverDetailedPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleEventHandlerPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleEventHandlerDetailedPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleBehaviourPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getParticleBehaviourDetailedPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getExternPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
			virtual const Ogre::String& getExternDetailedPropertiesGrammar(void){return Ogre::StringUtil::BLANK;};
	};

}
#endif
