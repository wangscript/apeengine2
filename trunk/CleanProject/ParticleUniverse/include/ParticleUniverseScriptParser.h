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

#ifndef __PU_PARTICLE_SCRIPT_PARSER_H__
#define __PU_PARTICLE_SCRIPT_PARSER_H__

#include "OgreCompiler2Pass.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseTechnique.h"
#include "ParticleUniverseRenderer.h"
#include "ParticleUniverseEmitter.h"
#include "ParticleUniverseAffector.h"
#include "ParticleUniverseObserver.h"
#include "ParticleUniverseEventHandler.h"
#include "ParticleUniverseExtern.h"
#include "ParticleUniverseBehaviour.h"
#include "ParticleUniverseDynamicAttribute.h"
#include "ParticleUniverseContext.h"

namespace ParticleUniverse
{
	// String representation of the Particle Universe contexts. Numeric values are used to keep the string small.
	const static Ogre::String ALIAS					= "1";
	const static Ogre::String SYSTEM				= "2";
	const static Ogre::String TECHNIQUE				= "3";
	const static Ogre::String RENDERER				= "4";
	const static Ogre::String EMITTER				= "5";
	const static Ogre::String AFFECTOR				= "6";
	const static Ogre::String OBSERVER				= "7";
	const static Ogre::String HANDLER				= "8";
	const static Ogre::String BEHAVIOUR				= "9";
	const static Ogre::String EXTERN				= "10";
	const static Ogre::String DYNAMIC_ATTRIBUTE		= "11";
	const static Ogre::String DEPENDENCY			= "12";

	/*	The ParticleScriptParser forms a layer between Ogre's Compiler2Pass and the ParticleScriptTokeniser.
	@remarks
		It's purpose is to make protected parsing functions of the Compiler2Pass available to other 
		components that are involved in parsing the script.
	*/
	class _ParticleUniverseExport ParticleScriptParser : public Ogre::Compiler2Pass
    {
		public:
			Context context;

			ParticleScriptParser()
			{
			};

			virtual ~ParticleScriptParser() {};

			/** 
			*/
			void logParseError(const Ogre::String& error){};

			/** 
			*/
			const Ogre::String& getNextTokenLabel(void) const
			{
				return Ogre::Compiler2Pass::getNextTokenLabel();
			}

			/** 
			*/
			size_t getRemainingTokensForAction(void) const
			{
				return Ogre::Compiler2Pass::getRemainingTokensForAction();
			}

			/** 
			*/
			const Ogre::String& getCurrentTokenLexeme(void) const
			{
				return Ogre::Compiler2Pass::getCurrentTokenLexeme();
			}

			/** 
			*/
			size_t getNextTokenID(void) const
			{
				return Ogre::Compiler2Pass::getNextTokenID();
			}

			/** 
			*/
			const Ogre::String& getNextTokenLexeme(void) const
			{
				return Ogre::Compiler2Pass::getNextTokenLexeme();
			}

			/** 
			*/
			void skipToken(void) const
			{
				Ogre::Compiler2Pass::skipToken();
			}
			
			/** 
			*/
			float getNextTokenValue(void) const
			{
				return Ogre::Compiler2Pass::getNextTokenValue();
			}
			
			/** 
			*/
			bool testNextTokenID(const size_t expectedTokenID) const
			{
				return Ogre::Compiler2Pass::testNextTokenID(expectedTokenID);
			}

			/** 
			*/
			const Ogre::String& getGroupName(void) const
			{
				return mSourceName;
			}

			/** This function returns the value, because DynamicAttribute can differ in type
			*/
			DynamicAttribute* parseDynamicAttribute(void);

			/** 
			*/
			void parseVector2(Ogre::Vector2& vector);

			/** 
			*/
			void parseVector3(Ogre::Vector3& vector);

			/** 
			*/
			void parseVector4(Ogre::Vector4& vector);

			/** 
			*/
			void parseColourValue(Ogre::ColourValue& colourValue);

			/** 
			*/
			void parseRadian(Ogre::Radian& rad);

			/** 
			*/
			void parseReal(Ogre::Real& real);

			/** 
			*/
			void parseBool(bool& b);

			/** 
			*/
			void parseUshort(unsigned short& shortValue);

			/** 
			*/
			void parseUint(Ogre::uint& uint);

			/** 
			*/
			void parseUint8(Ogre::uint8& uint8);

			/** 
			*/
			void parseUint16(Ogre::uint16& uint16);

			/** 
			*/
			void parseUint32(Ogre::uint32& uint32);
	};

}
#endif
