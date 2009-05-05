#ifndef _NxOgreConverter_H
#define _NxOgreConverter_H

#include "Ogre.h"

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
#endif

