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

#ifndef __PU_GRAMMAR_H__
#define __PU_GRAMMAR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIGrammar.h"

namespace ParticleUniverse
{
	/*	This class contains the BNF grammar rules for the ParticleUniverse plugin itself.
	*/
	class _ParticleUniverseExport Grammar : public IGrammar
    {
		public:
			Grammar(void) {};
			virtual ~Grammar(void) {};

			// Main header
			static Ogre::String particleUniverseBeginGrammar;

			// Renderer
			static Ogre::String particleRendererHeaderGrammar;
			static Ogre::String particleRendererPropertiesGrammar;
			static Ogre::String particleRendererDetailedPropertiesGrammar;

			// Emitter
			static Ogre::String particleEmitterHeaderGrammar;
			static Ogre::String particleEmitterPropertiesGrammar;
			static Ogre::String particleEmitterDetailedPropertiesGrammar;

			// Affector
			static Ogre::String particleAffectorHeaderGrammar;
			static Ogre::String particleAffectorPropertiesGrammar;
			static Ogre::String particleAffectorDetailedPropertiesGrammar;

			// Observer
			static Ogre::String particleObserverHeaderGrammar;
			static Ogre::String particleObserverPropertiesGrammar;
			static Ogre::String particleObserverDetailedPropertiesGrammar;

			// EventHandler
			static Ogre::String particleEventHandlerHeaderGrammar;
			static Ogre::String particleEventHandlerPropertiesGrammar;
			static Ogre::String particleEventHandlerDetailedPropertiesGrammar;

			// Behaviour
			static Ogre::String particleBehaviourHeaderGrammar;
			static Ogre::String particleBehaviourPropertiesGrammar;
			static Ogre::String particleBehaviourDetailedPropertiesGrammar;

			// Extern
			static Ogre::String externHeaderGrammar;
			static Ogre::String externPropertiesGrammar;
			static Ogre::String externDetailedPropertiesGrammar;

			// Main footer
			static Ogre::String particleUniverseEndGrammar;

			// Implementation of virtual functions
			virtual const Ogre::String& getParticleEmitterPropertiesGrammar(void);
			virtual const Ogre::String& getParticleEmitterDetailedPropertiesGrammar(void);
			virtual const Ogre::String& getParticleAffectorPropertiesGrammar(void);
			virtual const Ogre::String& getParticleAffectorDetailedPropertiesGrammar(void);
			virtual const Ogre::String& getParticleRendererPropertiesGrammar(void);
			virtual const Ogre::String& getParticleRendererDetailedPropertiesGrammar(void);
			virtual const Ogre::String& getParticleObserverPropertiesGrammar(void);
			virtual const Ogre::String& getParticleObserverDetailedPropertiesGrammar(void);
			virtual const Ogre::String& getParticleEventHandlerPropertiesGrammar(void);
			virtual const Ogre::String& getParticleEventHandlerDetailedPropertiesGrammar(void);
			virtual const Ogre::String& getParticleBehaviourPropertiesGrammar(void);
			virtual const Ogre::String& getParticleBehaviourDetailedPropertiesGrammar(void);
			virtual const Ogre::String& getExternPropertiesGrammar(void);
			virtual const Ogre::String& getExternDetailedPropertiesGrammar(void);
	};

}
#endif
