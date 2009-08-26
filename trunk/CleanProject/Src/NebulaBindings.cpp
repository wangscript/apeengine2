#ifndef NEBULA_BINDINGS
#define NEBULA_BINDINGS

//#include "stdafx.h" // Ogre, Lua and luabind headers from here too.
//#include "Application.h"
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "luabind/luabind.hpp"


#include "Ogre.h"
#include <iostream>
#include <tchar.h>

using namespace std;

// Prototype this before operator.hpp so it can be found for tostring() operator.
std::ostream& operator<<( std::ostream& stream, const Ogre::Entity ent );

#include "luabind/operator.hpp"

using namespace luabind;
using namespace Ogre;

// Some helpful macros for defining constants (sort of) in Lua.  Similar to this code:
// object g = globals(L);
// object table = g["class"];
// table["constant"] = class::constant;

#define LUA_CONST_START( class ) { object g = globals(L); object table = g[#class];
#define LUA_CONST( class, name ) table[#name] = class::name
#define LUA_CONST_END }

namespace Nebula {

	void bindVector3( lua_State* L )
	{
		module(L)
			[
				class_<Vector3>( "Vector3" )
				//.def(tostring(self))
				.def_readwrite( "x", &Vector3::x )
				.def_readwrite( "y", &Vector3::y )
				.def_readwrite( "z", &Vector3::z )
				.def(constructor<>())
				.def(constructor<Vector3&>())
				.def(constructor<Real, Real, Real>())
				.def("absDotProduct", &Vector3::absDotProduct)
				.def("crossProduct", &Vector3::crossProduct )
				.def("directionEquals", &Vector3::directionEquals )
				.def("distance", &Vector3::distance )
				.def("dotProduct", &Vector3::dotProduct )
				.def("getRotationTo", &Vector3::getRotationTo )
				.def("isZeroLength", &Vector3::isZeroLength )
				.def("length", &Vector3::length )
				.def("makeCeil", &Vector3::makeCeil )
				.def("makeFloor", &Vector3::makeFloor )
				.def("midPoint", &Vector3::midPoint )
				.def("normalise", &Vector3::normalise )
				.def("nornaliseCopy", &Vector3::normalisedCopy )
				.def("perpendicular", &Vector3::perpendicular )
				.def("positionCloses", &Vector3::positionCloses )
				.def("positionEquals", &Vector3::positionEquals )
				//.def("ptr", &Vector3::ptr )
				.def("randomDeviant", &Vector3::randomDeviant )
				.def("reflect", &Vector3::reflect )
				.def("squaredDistance", &Vector3::squaredDistance )
				.def("squaredLength", &Vector3::squaredLength )

				// Operators

				.def( self + other<Vector3>() )
				.def( self - other<Vector3>() )
				.def( self * other<Vector3>() )
				.def( self * Real() )
			];

		//LUA_CONST_START( Vector3 )
		//	LUA_CONST( Vector3, ZERO);
		//LUA_CONST( Vector3, UNIT_X );
		//LUA_CONST( Vector3, UNIT_X);
		//LUA_CONST( Vector3, UNIT_Y);
		//LUA_CONST( Vector3, UNIT_Z);
		//LUA_CONST( Vector3, NEGATIVE_UNIT_X);
		//LUA_CONST( Vector3, NEGATIVE_UNIT_Y);
		//LUA_CONST( Vector3, NEGATIVE_UNIT_Z);
		//LUA_CONST( Vector3, UNIT_SCALE);
		//LUA_CONST_END;
	}

} //end namespace

#endif
