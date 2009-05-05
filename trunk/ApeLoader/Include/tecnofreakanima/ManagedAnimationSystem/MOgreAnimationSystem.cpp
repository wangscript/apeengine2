/*
TecnoFreak Animation System
http://sourceforge.net/projects/tecnofreakanima/

Copyright (c) 2008 Pau Novau Lebrato

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"

#include "MOgreAnimationSystem.h"

#include "Ogre/AnimationSystem.h"

#include <Ogre.h>

using namespace ManagedAnimationSystem;

OgreAnimationSystem::OgreAnimationSystem( Mogre::Entity^ entity )
: m_native( NULL )
{
	m_native = new tecnofreak::ogre::AnimationSystem( entity );
}

OgreAnimationSystem::OgreAnimationSystem( Mogre::AnimationStateSet^ animations )
: m_native( NULL )
{
	m_native = new tecnofreak::ogre::AnimationSystem( animations );
}

OgreAnimationSystem::~OgreAnimationSystem()
{
	delete m_native;
}

void OgreAnimationSystem::update( float elapsedSeconds )
{
	m_native->update( elapsedSeconds );
}

void OgreAnimationSystem::load( String^ filename )
{
	std::string s = static_cast< char* >( System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( filename ).ToPointer() );
	m_native->loadAnimationTree( s );
}

bool OgreAnimationSystem::hasParameter( String^ parameterName )
{
	std::string s = static_cast< char* >( System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( parameterName ).ToPointer() );
	return m_native->hasParameter( s );
}

Parameter^ OgreAnimationSystem::getParameter( String^ parameterName )
{
	std::string s = static_cast< char* >( System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi( parameterName ).ToPointer() );
	tecnofreak::IParameter* nativeParameter = m_native->getParameter( s );
	return gcnew Parameter( nativeParameter );
}