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

#ifndef __PU_PARTICLE_SCRIPT_TOKENISER_H__
#define __PU_PARTICLE_SCRIPT_TOKENISER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseScriptParser.h"
#include "ParticleUniverseGrammar.h"

namespace ParticleUniverse
{
	/*	The ParticleScriptTokeniser actually is the tokeniser and parser in one, but for convenience reasons, some 
		functions are divided between a ParticleScriptTokeniser and ParticleScriptParser class.
	@remarks
		Compiling a script consists of several steps, such as register tokens/functions, perform tokenising and
		parsing scripts. Instead of having one 'God' class that does it all (as in the material and compositor 
		compilers),a distributed approach has been choosen. Registering parse-functions and parsing of the script 
		itself is distributed across multiple components. This is the responsibility of both ParticleScriptTokeniser 
		and ParticleScriptParser. Classes such as ITokenInitialiser and IToken are used to organise the parse-functions
		by type (i.e. ParticleEmitterTokens, ParticleTechniqueTokens, ...). Grammar of the script is also defined in 
		a separate class (IGrammar). By distributing the responsibilities into several classes, it is easier to 
		parse additions by means of addon plugins.
	*/
	class _ParticleUniverseExport ParticleScriptTokeniser:
		public ParticleScriptParser, ITokenRegister
    {
		public:
			// Constructor
			ParticleScriptTokeniser (void);

			// Destructor
			~ParticleScriptTokeniser (void);

			/** gets BNF Grammer for Particle Universe script.
			*/
			virtual const Ogre::String& getClientBNFGrammer(void) const;

			/** get the name of the Particle Universe script BNF grammer.
			*/
			virtual const Ogre::String& getClientGrammerName(void) const { static const Ogre::String grammerName("Particle Universe Script"); return grammerName; }

			/** Register a pointer to a Grammar object, which is placed under the control of the Tokeniser.
			*/
			void addGrammar (IGrammar* grammar);

			/** Compile a particle universe script from a data stream using a specific resource group name.
				@param stream Weak reference to a data stream which is the source of the material script
				@param groupName The name of the resource group that resources which are parsed are to become 
				a member of. If this group is loaded or unloaded, then the resources discovered in this script 
				will be loaded / unloaded with it.
			*/
			void parseScript(Ogre::DataStreamPtr& stream, const Ogre::String& groupName)
			{
				Ogre::Compiler2Pass::compile(stream->getAsString(),  stream->getName());
			}

			/** 
			*/
			virtual void addLexemeTokenAction(const Ogre::String& lexeme, const size_t tokenId, IToken* token = 0);

			/** 
			*/
			virtual size_t addTokenId(const Ogre::String& lexeme, const size_t tokenId, const bool hasAction = false, const bool caseSensitive = false);

		protected:
			// simplified Backus - Naur Form (BNF) grammer for particle universe scripts
			static Ogre::String particleUniverseScriptGrammar;
			std::vector<IGrammar*> mGrammarList;

			// Instance of a TokenActionMap
			static TokenActionMap mTokenActionMap;

			/** Execute an Action associated with a token. Gets called when the compiler finishes tokenizing a
				section of the source that has been parsed.
			**/
			virtual void executeTokenAction(const size_t tokenID);

	        /** Get the start position of auto generated token IDs.
		    */
			virtual size_t getAutoTokenIDStart() const {return ID_AUTOTOKENSTART;}

			/** Associate all the lexemes used in a particle universe script with their corresponding tokens 
				and actions.
			**/
			virtual void setupTokenDefinitions(void);
	};

}
#endif
