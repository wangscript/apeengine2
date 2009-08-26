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

#ifndef __PU_VERTEX_EMITTER_H__
#define __PU_VERTEX_EMITTER_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseEmitter.h"

namespace ParticleUniverse
{
	/** The VertexEmitter gradually generates spawn points, based on the edges of a mesh. 
		This means that in every ParticleTechnique-update, a few points are generated, 
		until all vertices of the mesh have been processed.
	@remarks
		Beware, there is no intermediate validation whether the mesh still exist (performance reasons), 
		so destroying the mesh before all vertices are processed will result in an exception.

		Todo:
		- Add normals to the mSpawnPositionList
    */
	class _ParticleUniverseExport VertexEmitter : public ParticleEmitter
	{
		protected:
			std::list<Ogre::Vector3> mSpawnPositionList;
			const Ogre::VertexElement* mPositionElement;
			Ogre::VertexData* mVertexData;
			Ogre::HardwareVertexBufferSharedPtr mBuffer;
			unsigned char* mVertexBuffer;
			Ogre::Mesh* mMesh;
			Ogre::SubMesh* mSubMesh;
			bool mMeshProcessed;
			size_t mVertexSize;
			size_t mMaxVertexCount;
			size_t mVertexCount;
			unsigned short mSubMeshNumber;
			bool mAllVerticesProcessed;

			/** Determines the size of the steps that are used to traverse through the vertices.
	        */
			unsigned short mStep;
			
			/** Determines in how many segments an edge is divided. This results in spawn points.
	        */
			unsigned short mSegments;

			/** Defines the speed of generating spawnpoints. In each Particle Technique update
				'mIterations' vertices are traversed.
			@remarks
				Setting this attribute to a higher value is needed if the emssion rate of the emitter
				is high. On slower computers, emitting the particles may exceed generating the 
				spawnpoints (because this is not done at once, but per Particle Tehcnique update).
	        */
			unsigned short mIterations;

			/** Determines the name of the mesh of which the vertices are used.
	        */
			Ogre::String mMeshName;

			/** The _preProcessParticles() function is used to generate some spawn points in every update.
	        */
			virtual void _preProcessParticles(ParticleTechnique* technique, Ogre::Real timeElapsed);

			/** 
	        */
			void _setDefaults(void);

			/** 
	        */
			void _loadMesh (void);

			/** Generate spawn points from a mesh. The points will not be generated all at once, but
				gradually. In each call, the points on an edge are generated, until all vertices
				have been processed. In that case, mAllVerticesProcessed is set to true and this 
				function stops further processing.
	        */
			void _generatePoints (void);
				
			/** 
	        */
			void _generatePointsFromMesh (void);

			/** 
	        */
			void _generatePointsFromSubMesh (void);

			/** 
	        */
			void _fillVertexBuffer(void);

			/** 
	        */
			void _generatePointsFromVertexBuffer(void);

			/** 
	        */
			void _generatePoints (const Ogre::Vector3& startVector, 
				const Ogre::Vector3& endVector,
				Ogre::Real lengthIncrement = 0.0f);

		public:
			VertexEmitter(void) : ParticleEmitter(),
				mPositionElement(0),
				mVertexData(0),
				mVertexBuffer(0),
				mMesh(0),
				mSubMesh(0),
				mVertexSize(12),
				mMaxVertexCount(0),
				mVertexCount(0),
				mStep(1),
				mSegments(1),
				mMeshProcessed(false),
				mAllVerticesProcessed(false),
				mSubMeshNumber(0),
				mIterations(1),
				mMeshName(Ogre::StringUtil::BLANK)
			{
				mEmitterType = "Vertex";
				mBuffer.setNull();
			};
	        virtual ~VertexEmitter(void) {};

			/** 
	        */
			unsigned short getIterations(void) const;

			/** 
	        */
			void setIterations(unsigned short iterations);
			
			/** 
	        */
			unsigned short getSegments(void) const;

			/** 
	        */
			void setSegments(unsigned short segments);

			/** 
	        */
			unsigned short getStep(void) const;

			/** 
	        */
			void setStep(unsigned short step);

			/** 
	        */
			const Ogre::String& getMeshName(void) const;

			/** 
	        */
			virtual void _notifyStart (void);
			
			/** 
	        */
			void setMeshName(const Ogre::String& meshName);

			/** 
	        */
			virtual void _initParticlePosition(Particle* particle);

			/** 
	        */
			unsigned short _calculateRequestedParticles(Ogre::Real timeElapsed);

			/** 
	        */
			virtual void copyAttributesTo (ParticleEmitter* emitter);
	};

}
#endif
