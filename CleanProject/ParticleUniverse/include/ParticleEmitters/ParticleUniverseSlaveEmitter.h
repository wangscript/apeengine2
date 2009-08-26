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

#ifndef __PU_SLAVE_EMITTER_H__
#define __PU_SLAVE_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseEmitter.h"
#include "ParticleUniverseTechniqueListener.h"

namespace ParticleUniverse
{
	/** Todo.
    */
	class _ParticleUniverseExport SlaveEmitter : public ParticleEmitter, public TechniqueListener
	{
		protected:
			Particle* mMasterParticle;
			Ogre::String mMasterTechniqueName;
			Ogre::String mMasterEmitterName;
			Ogre::Vector3 mMasterPosition;
			Ogre::Vector3 mMasterDirection;
			bool mMasterEmitterNameSet;

		public:
			SlaveEmitter(void);
	        virtual ~SlaveEmitter(void){};

			/** 
	        */
			const Ogre::String& getMasterTechniqueName(void) const;

			/** 
	        */
			void setMasterTechniqueName(const Ogre::String& masterTechniqueName);

			/** 
	        */
			const Ogre::String& getMasterEmitterName(void) const;

			/** See ParticleEmitter.
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** See ParticleEmitter.
	        */
			virtual void _initParticleDirection(Particle* particle);

			/** See ParticleEmitter.
	        */
			virtual void _prepare(ParticleTechnique* particleTechnique);

			/** Initialise the emitted particle. This means that its position is set.
	        */
			virtual void particleEmitted(ParticleTechnique* particleTechnique, Particle* particle);

			/** No implementation.
	        */
			virtual void particleExpired(ParticleTechnique* particleTechnique, Particle* particle){};

			/** 
	        */
			void setMasterEmitterName(const Ogre::String& masterEmitterName);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
