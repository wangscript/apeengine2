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

#ifndef OgreMax_ApplicationUtilities_INCLUDED
#define OgreMax_ApplicationUtilities_INCLUDED


//Includes---------------------------------------------------------------------
#include <OgreCamera.h>
#include <OgreString.h>
#include <OgrePixelFormat.h>


//Classes----------------------------------------------------------------------
namespace OgreMax
{
    /** 
     * Utility functions implemented in a way that's specific to how the
     * application operates
     */
    class ApplicationUtilities
    {
    public:        
        /** Copies the relevant camera settings from one camera to another */
        static void CopyCameraSettings
            (
            Ogre::Camera* destinationCamera, 
            const Ogre::Camera* sourceCamera
            );

        /**
         * Chooses the best shadow texture pixel format based on the camera setup
         * @return Returns true if a pixel format was selected, false otherwise
         */
        static bool ChooseShadowPixelFormat
            (
            Ogre::PixelFormat& pixelFormat, 
            const Ogre::String& cameraSetup
            );
    };
}

#endif