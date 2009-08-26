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

#ifndef __PU_POOLMAP_H__
#define __PU_POOLMAP_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/** The PoolMap is an extention of the regular Pool. The PoolMap contains objects that can be found by name.
	*/
	template <typename T>
	class _ParticleUniverseExport PoolMap
	{
		public:
			typedef std::multimap<Ogre::String, T*> PoolMapMap;
			typedef typename PoolMapMap::iterator PoolMapIterator; // The 'typename' MUST be added, since T is not a fixed type
			PoolMapIterator mPoolMapIterator;

			//-----------------------------------------------------------------------
			PoolMap (bool managed = false) : mManaged(managed)
			{
				if (mManaged)
				{
					// Unused.
				}
			};
			//-----------------------------------------------------------------------
			virtual ~PoolMap (void)
			{
				if (mManaged)
				{
					// Unused.
				}
			};
			//-----------------------------------------------------------------------
			/** Returns true if the number of released elements is 0.
			*/
			bool isEmpty(void)
			{
				return mReleased.empty();
			};
			//-----------------------------------------------------------------------
			/** 
			*/
			size_t getSize(void)
			{
				return mReleased.size();
			};
			//-----------------------------------------------------------------------
			void resetIterator (void)
			{
				mPoolMapIterator = mReleased.begin();
			};
			//-----------------------------------------------------------------------
			T* getFirst (void)
			{
				resetIterator();
				if (end())
					return 0;

				T* t = mPoolMapIterator->second;
				return t;
			};
			//-----------------------------------------------------------------------
			T* getNext (void)
			{
				if (end())
					return 0;

				mPoolMapIterator++;
				if (end())
					return 0;
				
				T* t = mPoolMapIterator->second;
				return t;
			};
			//-----------------------------------------------------------------------
			bool end (void)
			{
				return mPoolMapIterator == mReleased.end();
			};
			//-----------------------------------------------------------------------
			/** 
			*/
			void clear (void)
			{
				mLocked.clear();
				mReleased.clear();
			};
			//-----------------------------------------------------------------------
			/** Add an element to the PoolMap.
			@remarks
				Can only be done if the pool doesn't manage the creation and desctruction of the elements.
			*/
			void addElement (const Ogre::String& key, T* element)
			{
				if (mManaged)
					OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED, "It is not allowed to add elements, because the pool manages the creation/destruction.", 
				        "PoolMap::addElement");

				mLocked.insert(make_pair(key, element));
			};

			//-----------------------------------------------------------------------
			/** Get an element from the pool.
			@remarks
				This function does not only retrieve an object, but the object is also marked as ´released´. This means
				that the object is exposed to the outside world. If objects in pool are traversed, only the released objects
				are taken into account.
			*/
			T* releaseElement (const Ogre::String& key)
			{
				// Return with 0 if no elements left
				if (mLocked.empty())
					return 0;

				// Return the first element that is encountered
				T* t = 0;
				PoolMapIterator it;
				it = mLocked.find(key);
				if (it != mLocked.end())
				{
					// Get the element and move it to the released elements list
					t = it->second;
					mReleased.insert(make_pair(key, t));
					mLocked.erase(it);
				}

				return t;
			};
			//-----------------------------------------------------------------------
			/** 
			*/
			void releaseAllElements (void)
			{
				// Move all elements from locked elements to released elements
				PoolMapIterator it;
				for (it = mLocked.begin(); it != mLocked.end(); ++it)
				{
					mReleased.insert(make_pair(it->first, it->second));
				}
				mLocked.clear();
				resetIterator();
			};
			//-----------------------------------------------------------------------
			void lockLatestElement (void)
			{
				// Move element pointed by iterator from released elements to locked elements
				mLocked.insert(make_pair(mPoolMapIterator->first, mPoolMapIterator->second));
				mReleased.erase(mPoolMapIterator++); // Watch the ++ at the end to set mPoolMapIterator to the next element
			};
			//-----------------------------------------------------------------------
			/** Lock all elements in the pool.
			@remarks
				All released objects are locked.
			*/
			void lockAllElements (void)
			{
				// Move all elements from release elements to locked elements
				PoolMapIterator it;
				for (it = mReleased.begin(); it != mReleased.end(); ++it)
				{
					mLocked.insert(make_pair(it->first, it->second));
				}
				mReleased.clear();
				resetIterator();
			};

		protected:
			bool mManaged; // Determine whether the pool is responsible for creation and destruction of the elements
			PoolMapMap mReleased;
			PoolMapMap mLocked;
	};

}
#endif
