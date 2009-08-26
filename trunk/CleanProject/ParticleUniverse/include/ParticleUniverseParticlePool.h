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

#ifndef __PU_PARTICLE_POOL_H__
#define __PU_PARTICLE_POOL_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniversePool.h"
#include "ParticleUniversePoolMap.h"
#include "ParticleUniverseVisualParticle.h"

namespace ParticleUniverse
{
	/** The ParticlePool is a container class that includes other pools. The ParticlePool acts as one pool
		with different types of particles.
    */
	class _ParticleUniverseExport ParticlePool
	{
		protected:
			ParticleTechnique* mParentTechnique;

			/** The Pools
		    */
			Pool<VisualParticle> mVisualParticlesPool;
			PoolMap<ParticleEmitter> mParticleEmitterPool;
			PoolMap<ParticleAffector> mParticleAffectorPool;
			PoolMap<ParticleSystem> mParticleSystemPool;
			PoolMap<ParticleTechnique> mParticleTechniquePool;

			/** Vectors used for deletion of created objects
		    */
			std::vector<VisualParticle*> mVisualParticles;
			std::vector<ParticleEmitter*> mEmitters;
			std::vector<ParticleAffector*> mAffectors;
			std::vector<ParticleTechnique*> mTechniques;
			std::vector<Ogre::String> mSystems; // Use names instead of pointers to avoid problems during cleanup.

			/** Protected methods to increase the pools
		    */
			void _increaseVisualParticlePool(size_t size, std::vector<ParticleBehaviour*>& behaviours);
			void _increaseParticleEmitterPool(size_t size, std::vector<ParticleBehaviour*>& behaviours, ParticleTechnique* technique);
			void _increaseParticleAffectorPool(size_t size, std::vector<ParticleBehaviour*>& behaviours, ParticleTechnique* technique);
			void _increaseParticleTechniquePool(size_t size, std::vector<ParticleBehaviour*>& behaviours, ParticleSystem* system);
			void _increaseParticleSystemPool(size_t size, std::vector<ParticleBehaviour*>& behaviours, ParticleTechnique* technique);

			Particle* mLatestParticle;

		public:

			ParticlePool(void) : mLatestParticle(0){};
			virtual ~ParticlePool (void);

			/** 
			*/
			void setParentTechnique(ParticleTechnique* parentTechnique);

			/** 
			*/
			bool isEmpty(void);

			/** 
			*/
			bool isEmpty(const Particle::ParticleType particleType);

			/** 
			*/
			size_t getSize(void);

			/** 
			*/
			size_t getSize(const Particle::ParticleType particleType);

			/** 
		    */
			void initialisePool(void);

			/** 
		    */
			void increasePool (const Particle::ParticleType particleType, 
				size_t size,
				std::vector<ParticleBehaviour*>& behaviours,
				ParticleTechnique* technique);

			/** Releases a particle from the pool
		    */
			Particle* releaseParticle (const Particle::ParticleType particleType, const Ogre::String& name);

			/** Releases all particles from the pool
		    */
			void releaseAllParticles (void);

			/** 
		    */
			void lockLatestParticle (void);

			/** Lock all particles in the pool
		    */
			void lockAllParticles (void);

			/** 
		    */
			void resetIterator(void);

			/** 
		    */
			Particle* getFirst(void);

			/** 
		    */
			Particle* getNext(void);

			/** 
		    */
			Particle* getFirst(const Particle::ParticleType particleType);

			/** 
		    */
			Particle* getNext(const Particle::ParticleType particleType);

			/** 
		    */
			bool end(void);

			/** 
		    */
			bool end(const Particle::ParticleType particleType);

			/** 
		    */
			std::list<VisualParticle*>& getVisualParticlesList(void)
			{
				return mVisualParticlesPool.getActiveElementsList();
			};
	};

}
#endif
