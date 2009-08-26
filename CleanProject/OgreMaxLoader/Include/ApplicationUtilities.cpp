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

//Includes---------------------------------------------------------------------
#include "ApplicationUtilities.hpp"

using namespace Ogre;
using namespace OgreMax;


//Implementation---------------------------------------------------------------
void ApplicationUtilities::CopyCameraSettings(Camera* destinationCamera, const Camera* sourceCamera)
{
    destinationCamera->setPosition(sourceCamera->getRealPosition());
    destinationCamera->setOrientation(sourceCamera->getRealOrientation());
    destinationCamera->setNearClipDistance(sourceCamera->getNearClipDistance());
    destinationCamera->setFarClipDistance(sourceCamera->getFarClipDistance());
    destinationCamera->setProjectionType(sourceCamera->getProjectionType());
    destinationCamera->setFOVy(sourceCamera->getFOVy());    
}

bool ApplicationUtilities::ChooseShadowPixelFormat(PixelFormat& pixelFormat, const String& cameraSetup)
{
    //Non-depth shadow maps use a non-floating point pixel format
    //In Direct3D this is essential since the default OgreMax shadow texture pixel format is floating point,
    //which causes the texture shadows to appear blue
    String cameraSetupLower = cameraSetup;
    StringUtil::toLowerCase(cameraSetupLower);
    if (cameraSetupLower.empty() ||
        cameraSetupLower == "uniform" || 
        cameraSetupLower == "uniformfocused" || 
        cameraSetupLower == "planeoptimal")
    {
        pixelFormat = PF_L8;
        return true;
    }
    else
        return false;
}