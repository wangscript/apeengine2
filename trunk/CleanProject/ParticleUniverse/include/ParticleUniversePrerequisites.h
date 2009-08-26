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

#ifndef __PU_PREREQUISITES_H__
#define __PU_PREREQUISITES_H__

#include "Ogre.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#	if defined( PARTICLE_UNIVERSE_EXPORTS )
#		define _ParticleUniverseExport __declspec( dllexport )
#	else
#		define _ParticleUniverseExport __declspec( dllimport )
#	endif
#else
#	define _ParticleUniverseExport
#endif 

// 4800 - 'Ogre::uint32' : forcing value to bool 'true' or 'false' (performance warning)
// 4217 - reference to an imported symbol that has been defined locally
#pragma warning (disable : 4800 4217)

namespace ParticleUniverse
{
	class ParticleSystem;
	class ParticleTechnique;
	class ParticleEmitter;
	class ParticleAffector;
	class ParticleObserver;
	class Particle;
	class VisualParticle;
	class Extern;
	class IDependency;
	class IToken;
	class BoxColliderExternFactory;
}
#endif
