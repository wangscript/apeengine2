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

#ifndef __PU_EXTERN_H__
#define __PU_EXTERN_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** The Extern class is the abstract class for all extern components. Each subclass of Extern wraps a
		particular external component and forms a bridge between the external component and the
		ParticleUniverse (or to be more specific, the ParticleTechnique).
	@remarks
		External components can be used to add functionality to the ParticleUniverse plugin. An example is
		the addition of a physics library. Settings up the library is typically done within a dedicated
		subclass of Extern.
    */
	class _ParticleUniverseExport Extern : public IAlias, public IElement
	{
		protected:
			// Type of extern
			Ogre::String mExternType;

			// Name of the extern (optional)
			Ogre::String mName;

			// Parent
			ParticleTechnique* mParentTechnique;

			/** Although the scale is on a Particle System level, it is stored here also, because this value is often 
				used. It is a derived value, so it has not get a get and set function.
			*/
			Ogre::Vector3 _mParticleSystemScale;

		public:
			Extern(void) :
				IElement(),
				mExternType(Ogre::StringUtil::BLANK),
				mParentTechnique(0),
				_mParticleSystemScale(Ogre::Vector3::UNIT_SCALE){};
			virtual ~Extern(void){};

			/** 
	        */
			const Ogre::String& getName(void) const {return mName;};
			void setName(const Ogre::String& name) {mName = name;};

			/** 
	        */
			const Ogre::String& getExternType(void) const {return mExternType;};
			void setExternType(const Ogre::String& externType) {mExternType = externType;};

			/** 
	        */
			ParticleTechnique* getParentTechnique(void) const {return mParentTechnique;};
			void setParentTechnique(ParticleTechnique* parentTechnique) {mParentTechnique = parentTechnique;};

			/** Notify that the Particle System is rescaled.
	        */
			virtual void _notifyRescaled(const Ogre::Vector3& scale);

			/** Copy attributes to another extern object.
	        */
			virtual void copyAttributesTo (Extern* externObject);

			/** Perform initialisation actions.
			@remarks
				The _prepare() function is automatically called during initialisation activities of a ParticleTechnique.
				Each subclass should implement this function to perform initialisation actions needed for the external
				component.
			@par
				This is a pure virtual function, to be sure that developers of an extern component don't forget to
				override this functions and perform setup/initialisation of the component. This is to prevent that 
				unexplainable errors occur because initialisation tasks where forgotten.
	        */
			virtual void _prepare(ParticleTechnique* technique) = 0;

			/** Perform activities when a ParticleTechnique is started.
			*/
			virtual void _notifyStart (void){/* Do nothing */};

			/** Perform activities when a ParticleTechnique is stopped.
			*/
			virtual void _notifyStop (void){/* Do nothing */};

			/** Perform activities before the individual particles are processed.
			@remarks
				This function is called before the ParticleTechnique update-loop where all particles are traversed.
				the preProcess is typically used to perform calculations where the result must be used in 
				processing each individual particle.
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed){/* Do nothing */};

			/** Perform precalculations if the first Particle in the update-loop is processed.
			*/
			virtual void _firstParticle(ParticleTechnique* particleTechnique, 
				Particle* particle, 
				Ogre::Real timeElapsed) { /* by default do nothing */ }

			/** Processes a particle.
			@remarks
				Some processing on a particle can be performed. This function is automatically called in the 
				ParticleTechnique update-loop where all particles are traversed.
	        */
			virtual void _processParticle(ParticleTechnique* technique, Particle* particle, Ogre::Real timeElapsed, bool firstParticle);

			/** Actually processes a particle.
	        */
			virtual void _interface(ParticleTechnique* technique, 
				Particle* particle, 
				Ogre::Real timeElapsed) = 0;

			/** Perform activities after the individual particles are processed.
			@remarks
				This function is called after the ParticleTechnique update-loop where all particles are traversed.
	        */
			virtual void _postProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed){/* Do nothing */};
	};

}
#endif
