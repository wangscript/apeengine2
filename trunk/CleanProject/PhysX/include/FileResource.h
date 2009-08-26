/*!
@file
@author		Pablo Nuñez
@date		13/2009
@module
*//*
This file is part of the Nebula Engine.

Nebula Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Nebula Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Nebula Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __FILE_RESOURCE_H__
#define __FILE_RESOURCE_H__

#include "EnginePrerequisites.h"

namespace Nebula {

	enum MeshType {
		MT_Triangle,
		MT_Convex,
		MT_Unknown
	};

	enum ResourceAccess {
		RA_Read,
		RA_Write,
		RA_ReadWrite,
		RA_Default
	};

	class FileResource : public NxStream { //: public Resource

		public:

			FileResource(const std::string&, ResourceAccess);
			~FileResource();

			std::string  getResourceIdentifier() const;

			/** \brief Re-use the stream.
			*/
			void  reuse(const std::string&, ResourceAccess);

			/** \brief Close the stream.
			*/
			void  close();

			/** \brief The size of the stream.
			*/
			NxU32  size() const;

			/** \brief Set the read pointer to X bytes from the beginning of the stream.
			*/
			void  seek(long);

			/** \brief Skip forward so many bytes from the current position of the read pointer.
			*/
			void  skip(long);

			/** \brief How far is the read pointer from the beginning of the stream.
			*/
			size_t  tell() const;

			/** \brief Reset the readPointer to the beginning.
				\note <strong>Must</strong> be used with MemoryStreams after writing and reading is about to commence.
			*/
			void  rewind();

			/** \brief Write char to the stream.
			*/
			void  writeUChar(unsigned char);

			/** \brief Write short to the stream.
			*/
			void  writeUShort(unsigned short);

			/** \brief Write unsigned int to the stream.
			*/
			void  writeUInt(unsigned int);

			/** \brief Write float to the stream.
			*/
			void  writeFloat(float);

			/** \brief Write double to the stream.
			*/
			void  writeDouble(double);

			/** \brief Write a stl string to the stream.
			*/
			void  writeString(std::string);

			/** \brief Write any data to the stream.
			*/
			void  write(const void*, size_t length);

			/** \brief Get a char from the stream.
			*/
			unsigned char  getUChar() const;

			/** \brief Get a short from the stream.
			*/
			unsigned short  getShort() const;

			/** \brief Get a unsigned int from the stream.
			*/
			unsigned int  getUInt() const;

			/** \brief Get a float from the stream.
			*/
			float  getFloat() const;

			/** \brief Get a double from the stream.
			*/
			double  getDouble() const;

			/** \brief Get a stl string from the stream.
			*/
			std::string  getString() const;

			/** \brief Get any data from the stream.
			*/
			void  get(void* buffer, size_t length) const;

	protected:
		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::getUChar
		\internal
		*/
		NxU8   readByte() const;

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::getUChar
		\internal
		*/
		NxU16   readWord() const;

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::getUChar
		\internal
		*/
		NxU32   readDword() const;

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::getUChar
		\internal
		*/
		NxReal   readFloat() const;

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::getUChar
		\internal
		*/
		double   readDouble() const;

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::getUChar
		\internal
		*/
		void   readBuffer(void* buffer, NxU32 size) const;

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::getUChar
		\internal
		*/
		NxStream&   storeByte(NxU8 b);

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::getUChar
		\internal
		*/
		NxStream&   storeWord(NxU16 w);

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::storeFloat
		\internal
		*/
		NxStream&   storeDword(NxU32 d);

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::storeFloat
		\internal
		*/
		NxStream&   storeFloat(NxReal f);

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::storeDouble
		\internal
		*/
		NxStream&   storeDouble(NxF64 f);

		/** \brief PhysX Interface. Do not override or use.
		\see ResourceStreamPtr::store
		\internal
		*/
		NxStream&   storeBuffer(const void* buffer, NxU32 size);

		FILE*                mFile;
		NxU32                mSize;
		std::string   mResourceIdentifier;
	};

} //end namespace

#endif
