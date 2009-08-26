/*
 * OgreMaxViewer - An Ogre 3D-based viewer for .scene and .mesh files
 * Copyright 2008 Derek Nedelman
 *
 * This code is available under the OgreMax Free License:
 *   -You may use this code for any purpose, commercial or non-commercial.
 *   -If distributing derived works (that use this source code) in binary or source code form, 
 *    you must give the following credit in your work's end-user documentation: 
 *        "Portions of this work provided by OgreMax (www.ogremax.com)"
 *
 * Derek Nedelman assumes no responsibility for any harm caused by using this code.
 * 
 * OgreMaxViewer was written by Derek Nedelman and released at www.ogremax.com 
 */

#ifndef OgreMax_ApplicationLuaTypes_INCLUDED
#define OgreMax_ApplicationLuaTypes_INCLUDED

#ifndef OGREMAX_VIEWER_NO_LUA


//Includes---------------------------------------------------------------------
#include "LuaScript.hpp"


//Classes----------------------------------------------------------------------
namespace OgreMax
{
    class LuaScript;

    class ApplicationLuaTypes
    {
    public:
        static void Register(LuaScript& script, const Ogre::String& moduleName);
    };

}

#endif

#endif