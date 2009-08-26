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

#ifndef _NCONVERTER_H
#define _NCONVERTER_H

#include "EnginePrerequisites.h"

namespace Nebula {

	class NxTools {

	public:

		static inline Ogre::Vector3 convert(const NxVec3& v) {
			return	Ogre::Vector3(v.x,v.y,v.z);
		}

		static inline NxVec3 convert(const Ogre::Vector3& v) {
			return	NxVec3(v.x,v.y,v.z);
		}

		static inline NxVec3 convert(Ogre::Real x, Ogre::Real y, Ogre::Real z) {
			return	NxVec3(x,y,z);
		}

		static inline Ogre::Quaternion convert(const NxQuat& q) {	
			return Ogre::Quaternion(q.w, q.x, q.y, q.z);
		}

		static inline NxQuat convert(Ogre::Quaternion& q, bool _normalise = true) {

			if (_normalise)
				q.normalise();

			NxQuat a;
			a.x = q.x;
			a.y = q.y;
			a.z = q.z;
			a.w = q.w;
			return a;
		}

	};

} //end namespace

#endif

