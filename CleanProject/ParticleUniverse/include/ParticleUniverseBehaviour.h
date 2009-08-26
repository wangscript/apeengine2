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

#ifndef __PU_BEHAVIOUR_H__
#define __PU_BEHAVIOUR_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseIAlias.h"
#include "ParticleUniverseIElement.h"

namespace ParticleUniverse
{
	/** Defines the behaviour of a particle.
	@remarks
		While a ParticleAffector acts as an external 'force' on the particles, the ParticleBehaviour defines 
		the internal behaviour of each particle individually. For example, 'wind' is typically something that is 
		defined as a ParticleAffector, while 'elasticity' is behaviour of the particle itself.
	@par
		A particle can have multiple Behaviours. Each ParticleBehaviour is accompanied with a specific subclass of 
		the ParticleBehaviourFactory. Similar to ParticleEmitters and ParticleAffectors, each factory is 
		identified by means of a type name.
	@par
		The main reason to introduce the ParticleBehaviour class is to be able to expand the attributes and 
		functions of a particle dynamically and to assign behaviour by means of a particle script.
	*/
	class _ParticleUniverseExport ParticleBehaviour : public IAlias, public IElement
	{
		protected:
			// Type of behaviour
			Ogre::String mBehaviourType;

			ParticleTechnique* mParentTechnique;

			/** Although the scale is on a Particle System level, it is stored here also, because this value is often 
				used. It is a derived value, so it has not get a get and set function.
			*/
			Ogre::Vector3 _mParticleSystemScale;

		public:
			ParticleBehaviour(void) : 
				IElement(),
				IAlias(),
				_mParticleSystemScale(Ogre::Vector3::UNIT_SCALE)
			{
				mAliasType = AT_BEHAVIOUR;
			};
			virtual ~ParticleBehaviour(void) {};

			/** 
	        */
			const Ogre::String& getBehaviourType(void) const {return mBehaviourType;};
			void setBehaviourType(const Ogre::String& behaviourType) {mBehaviourType = behaviourType;};

			/** 
	        */
			ParticleTechnique* getParentTechnique(void) const {return mParentTechnique;};
			void setParentTechnique(ParticleTechnique* parentTechnique){mParentTechnique = parentTechnique;};

			/** Notify that the Particle System is rescaled.
	        */
			virtual void _notifyRescaled(const Ogre::Vector3& scale){_mParticleSystemScale = scale;};

			/** Perform initialisation actions.
			@remarks
				The _prepare() function is automatically called during initialisation (prepare) activities of a 
				ParticleTechnique. A subclass could implement this function to perform initialisation 
				actions.
	        */
			virtual void _prepare(ParticleTechnique* technique){/* No implementation */};

			/** Perform initialising activities as soon as the particle with which the ParticleBehaviour is
				associated, is emitted.
	        */
			virtual void _initParticleForEmission(Particle* particle){/* No implementation */};

			/** Process a particle.
	        */
			virtual void _processParticle(ParticleTechnique* technique, Particle* particle, Ogre::Real timeElapsed) = 0;

			/** Perform some action if a particle expires.
	        */
			virtual void _initParticleForExpiration(ParticleTechnique* technique, Particle* particle, Ogre::Real timeElapsed){/* No implementation */};

			/** Copy attributes to another ParticleBehaviour.
	        */
			virtual void copyAttributesTo (ParticleBehaviour* behaviour)
			{
				behaviour->mParentTechnique = mParentTechnique;
				behaviour->_mParticleSystemScale = _mParticleSystemScale;
			};
	};

}
#endif
