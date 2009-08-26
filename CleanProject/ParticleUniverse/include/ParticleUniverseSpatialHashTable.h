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

#ifndef __PU_SPATIAL_HASHTABLE_H__
#define __PU_SPATIAL_HASHTABLE_H__

#include "ParticleUniversePrerequisites.h"

namespace ParticleUniverse
{
	/**	Todo.
	*/
	template <typename T>
	class _ParticleUniverseExport SpatialHashTable
	{
		public:
			typedef std::vector<T> HashTableCell;
			typedef std::vector<HashTableCell> HashTableContent;

			/**	Todo.
			*/
			SpatialHashTable(void) :
				mTableSize(50),
				mCellDimension(15),
				mCellOverlap(5),
			{
				_initialise();
			};

			/**	Todo.
			*/
			SpatialHashTable(unsigned int tableSize, unsigned short cellDimension, unsigned short cellOverlap = 0.0f) :
				mTableSize(tableSize),
				mCellDimension(cellDimension),
				mCellOverlap(cellOverlap)
			{
				_initialise();
			};

			/**	Destructor.
			*/
			virtual ~SpatialHashTable(void) {};

			/**	Clearing the hashtable means that every cell must be cleared, but not mHashTable itself. It still needs
				mTableSize vectors. Clearing mHashTable would implicate that all cells are removed, so you have to
				initialise again.
			*/
			void clear(void)
			{
				for (unsigned int i = 0; i < mTableSize; i++)
				{
					mHashTable[i].clear();
				}
			};

			/**	Todo.
			*/
			unsigned int size(void) const
			{
				return mTableSize;
			};

			/**	Todo.
			*/
			unsigned int put(const Ogre::Vector3& position, T object)
			{
				// Put the object in the table, based on the position
				unsigned int cellIndexPosition = _calculateIndex(position);
				put(cellIndexPosition, object);

				/** If cell overlap is defined, take that into account. This means that the same object can be put 
					into multiple cells.
				*/
				if (mCellOverlap > 0.0f)
				{
					Ogre::Vector3 corner;
					corner.x = position.x + mCellOverlap;
					corner.y = position.y + mCellOverlap;
					corner.z = position.z + mCellOverlap;
					unsigned int cellIndexCorner = _calculateIndex(corner);
					if (cellIndexPosition != cellIndexCorner)
					{
						put(cellIndexCorner, object);
					}

					corner.x = position.x + mCellOverlap;
					corner.y = position.y + mCellOverlap;
					corner.z = position.z - mCellOverlap;
					cellIndexCorner = _calculateIndex(corner);
					if (cellIndexPosition != cellIndexCorner)
					{
						put(cellIndexCorner, object);
					}

					corner.x = position.x + mCellOverlap;
					corner.y = position.y - mCellOverlap;
					corner.z = position.z + mCellOverlap;
					cellIndexCorner = _calculateIndex(corner);
					if (cellIndexPosition != cellIndexCorner)
					{
						put(cellIndexCorner, object);
					}

					corner.x = position.x - mCellOverlap;
					corner.y = position.y + mCellOverlap;
					corner.z = position.z + mCellOverlap;
					cellIndexCorner = _calculateIndex(corner);
					if (cellIndexPosition != cellIndexCorner)
					{
						put(cellIndexCorner, object);
					}

					corner.x = position.x + mCellOverlap;
					corner.y = position.y - mCellOverlap;
					corner.z = position.z - mCellOverlap;
					cellIndexCorner = _calculateIndex(corner);
					if (cellIndexPosition != cellIndexCorner)
					{
						put(cellIndexCorner, object);
					}

					corner.x = position.x - mCellOverlap;
					corner.y = position.y - mCellOverlap;
					corner.z = position.z + mCellOverlap;
					cellIndexCorner = _calculateIndex(corner);
					if (cellIndexPosition != cellIndexCorner)
					{
						put(cellIndexCorner, object);
					}

					corner.x = position.x - mCellOverlap;
					corner.y = position.y + mCellOverlap;
					corner.z = position.z - mCellOverlap;
					cellIndexCorner = _calculateIndex(corner);
					if (cellIndexPosition != cellIndexCorner)
					{
						put(cellIndexCorner, object);
					}

					corner.x = position.x - mCellOverlap;
					corner.y = position.y - mCellOverlap;
					corner.z = position.z - mCellOverlap;
					cellIndexCorner = _calculateIndex(corner);
					if (cellIndexPosition != cellIndexCorner)
					{
						put(cellIndexCorner, object);
					}
				}
				return cellIndexPosition;
			};

			/**	If you have multiple objects for which you already know the cellIndex, you can use this convenience 
				function to save time.
			*/
			unsigned int put(const unsigned int cellIndex, T object)
			{
				HashTableCell* cell = &(mHashTable[cellIndex]);
				cell->push_back(object);
				return cellIndex;
			};

			/**	Todo.
			*/
			HashTableCell& getCell(const Ogre::Vector3& position)
			{
				return (mHashTable[_calculateIndex(position)]);
			};

			/**	Todo.
			*/
			unsigned int getCellIndex(const Ogre::Vector3& position)
			{
				return _calculateIndex(position);
			};

		protected:
			HashTableContent mHashTable;
			unsigned short mCellDimension; // Size of the cell
			unsigned short mCellOverlap; // Used to put nearby objects in a cel.
			unsigned int mTableSize;

			/**	Todo.
			*/
			unsigned int _calculateIndex(const Ogre::Vector3& position)
			{
				long x = (floor (position.x / mCellDimension)) * 73856093;
				long y = (floor (position.y / mCellDimension)) * 19349663;
				long z = (floor (position.z / mCellDimension)) * 83492791;
				long i = (x ^ y ^ z) % mTableSize;
				i = i < 0 ? mTableSize - 1 : i; // If negative, point to the last cell.
				return static_cast<unsigned int>(i);
			};

			/**	Todo.
			*/
			void _initialise(void)
			{
				mHashTable.clear();
				for (unsigned int i = 0; i < mTableSize; i++)
				{
					HashTableCell cell;
					mHashTable.push_back(cell);
				}
			}
	};

}
#endif
