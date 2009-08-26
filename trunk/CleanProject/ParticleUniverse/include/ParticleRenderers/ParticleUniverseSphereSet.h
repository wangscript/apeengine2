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

#ifndef __PU_SPHERE_SET_H__
#define __PU_SPHERE_SET_H__

#include "ParticleUniversePrerequisites.h"
#include "ParticleRenderers/ParticleUniversePrimitiveShapeSet.h"

namespace ParticleUniverse
{
	class Sphere;

	/** The SphereSet and Sphere classes are comparable with the BillboardSet and Billboard classes in Ogre, instead
		Spheres are rendered.
    */
	class _ParticleUniverseExport SphereSet : public PrimitiveShapeSet
	{
		protected:
			/** Default radius of each sphere
			*/
			Ogre::Real mDefaultRadius;

			/** Flag indicating whether to autoextend pool
			*/
			bool mAutoExtendPool;

			typedef std::list<Sphere*> ActiveSphereList;
			typedef std::list<Sphere*> FreeSphereList;
			typedef std::vector<Sphere*> SpherePool;

			/** Active sphere list.
			@remarks
				This is a linked list of pointers to spheres in the sphere pool.
			*/
			ActiveSphereList mActiveSpheres;

			/** Free sphere queue.
			*/
			FreeSphereList mFreeSpheres;

			/** Pool of sphere instances for use and reuse in the active sphere list.
			*/
			SpherePool mSpherePool;

			/** The vertex position data for all spheres in this set.
			*/
			Ogre::VertexData* mVertexData;

			/** The number of vertices per sphere.
			*/
			size_t mVertexCountPerSphere;

			/** Shortcut to main buffer
			*/
			Ogre::HardwareVertexBufferSharedPtr mMainBuf;

			/** Locked pointer to buffer
			*/
			float* mLockPtr;

			/** Locked pointer to index buffer
			*/
			Ogre::ushort* pIdx;

			/** The vertex index data for all spheres in this set (1 set only)
			*/
			Ogre::IndexData* mIndexData;

			/** The number of indeces per sphere.
			*/
			size_t mIndexCountPerSphere;

			typedef std::vector<Ogre::FloatRect> TextureCoordSets;
			TextureCoordSets mTextureCoords;

			/** Internal method for culling individual sphere
			*/
			inline bool sphereVisible(Ogre::Camera* cam, const Sphere& sphere);

			/** Number of visible sphere
			*/
			unsigned short mNumVisibleSpheres;

			/** Internal method for increasing pool size
			*/
			virtual void increasePool(size_t size);

			/** Internal method for generating vertex data
			*/
			void _genVertices(Sphere& sphere);

			/** Number of rings of which the sphere consists
			*/
			int mNumberOfRings;

			/** Number of segments of which the sphere consists
			*/
			int mNumberOfSegments;

			/** Internal vertex counter
			*/
			unsigned short mVertexIndex;

			/** Helper function to calculate number of number of vertices and indices per sphere
			*/
			void _calculateVertexAndIndexPerSphere(void);


		private:
			/** Flag indicating whether the HW buffers have been created.
			*/
			bool mBuffersCreated;

			/** The number of spheres in the pool.
			*/
			size_t mPoolSize;
        
			/** Is external sphere data in use?
			*/
			bool mExternalData;

			/** Internal method creates vertex and index buffers.
			*/
			void _createBuffers(void);
        
			/** Internal method destroys vertex and index buffers.
			*/
			void _destroyBuffers(void);

		public:
			/** Default constructor.
			*/
			SphereSet(const Ogre::String& name, unsigned int poolSize = 20, bool externalData = false);

			/** Default constructor.
			*/
			SphereSet(void);

			/** Default destructor.
			*/
	        virtual ~SphereSet(void);

			/** Creates a new sphere and adds it to this set.
			*/
			Sphere* createSphere(const Ogre::Vector3& position);

			/** Creates a new sphere and adds it to this set.
			*/
			Sphere* createSphere(Ogre::Real x, Ogre::Real y, Ogre::Real z);

			/** Returns the number of active spheres which currently make up this set.
			*/
			virtual int getNumSpheres(void) const;
			
			/** Tells the set whether to allow automatic extension of the pool of spheres.
			*/
			virtual void setAutoextend(bool autoextend);
			
			/** Returns true if the sphere pool automatically extends.
			*/
			virtual bool isAutoextend(void) const;

			/** Adjusts the size of the pool of spheres available in this set.
			*/
			virtual void setPoolSize(size_t size);

			/** Returns the current size of the sphere pool.
			*/
			virtual unsigned int getPoolSize(void) const;

			/** Empties this set of all spheres.
			*/
			virtual void clear();

			/** Returns a pointer to the sphere at the supplied index.
			*/
			virtual Sphere* getSphere(unsigned int index) const;

			/** Removes the sphere at the supplied index.
			*/
			virtual void removeSphere(unsigned int index);

			/** Removes a sphere from the set.
			*/
			virtual void removeSphere(Sphere* sphere);

			/** Sets the default radius of the spheres in this set.
			*/
			virtual void setDefaultRadius(Ogre::Real radius);

			/** See setDefaultRadius
			*/
			virtual Ogre::Real getDefaultRadius(void) const;

			/** Set the number of rings of which this sphere consists.
			*/
			virtual void setNumberOfRings(int numberOfRings);

			/** Get the number of rings of which this sphere consists.
			*/
			virtual int getNumberOfRings(void) const;

			/** Set the number of segments of which this sphere consists.
			*/
			virtual void setNumberOfSegments(int numberOfSegments);

			/** Get the number of segments of which this sphere consists.
			*/
			virtual int getNumberOfSegments(void) const;

			/** Begin injection of sphere data; applicable when constructing the SphereSet for external data use.
			*/
			void beginSpheres(size_t numSpheres = 0);

			/** Define a sphere.
			*/
			void injectSphere(Sphere& sphere);
        
			/** Finish defining spheres. */
			void endSpheres(void);

			/** Set the bounds of the SphereSet.
			*/
			void setBounds(const Ogre::AxisAlignedBox& box, Ogre::Real radius);

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			virtual void _updateRenderQueue(Ogre::RenderQueue* queue);

			/** Overridden from MovableObject
			@see
				MovableObject
			*/
			virtual void getRenderOperation(Ogre::RenderOperation& op);

			/** Overridden from MovableObject 
			*/
			virtual const Ogre::String& getMovableType(void) const;

			/** Update the bounds of the sphere set
			*/
			virtual void _updateBounds(void);

			/** Sets whether spheres should be treated as being in world space. 
			*/
			virtual void setSpheresInWorldSpace(bool ws) { mWorldSpace = ws; }
	};

	/** Factory object for creating SphereSet instances */
	class _ParticleUniverseExport SphereSetFactory : public Ogre::MovableObjectFactory
	{
	
		protected:
			Ogre::MovableObject* createInstanceImpl( const Ogre::String& name, const Ogre::NameValuePairList* params);

		public:
			SphereSetFactory() {}
			~SphereSetFactory() {}

			static Ogre::String PU_FACTORY_TYPE_NAME;

			const Ogre::String& getType(void) const;
			void destroyInstance( Ogre::MovableObject* obj);  
	};

}

#endif
