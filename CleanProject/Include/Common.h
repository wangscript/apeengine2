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

#ifndef __NEBULA__COMMON__H__
#define __NEBULA__COMMON__H__

#pragma warning( disable : 4251 )

#define NEBULA_PLATFORM_WIN32 1
#define NEBULA_PLATFORM_LINUX 2
#define NEBULA_PLATFORM_APPLE 3

// Determine current platform.
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define NEBULA_PLATFORM NEBULA_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
#   define NEBULA_PLATFORM Nebula_PLATFORM_APPLE
#else
#   define NEBULA_PLATFORM Nebula_PLATFORM_LINUX
#endif

#if NEBULA_PLATFORM == NEBULA_PLATFORM_WIN32
#       define NebulaDllExport __declspec( dllexport )
#       define NebulaDllPrivate __declspec( dllexport )
#       define NebulaThisCall __thiscall
#elif NEBULA_PLATFORM == NEBULA_PLATFORM_APPLE || NEBULA_PLATFORM == NEBULA_PLATFORM_LINUX
#       define NebulaDllExport
#       define NebulaDllPrivate
#       define NebulaThisCall
#endif

#undef min
#undef max

#include <stdexcept>

#endif