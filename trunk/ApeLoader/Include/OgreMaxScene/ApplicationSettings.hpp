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

#ifndef OgreMax_ApplicationSettings_INCLUDED
#define OgreMax_ApplicationSettings_INCLUDED


//Includes---------------------------------------------------------------------
#include "CommandLineArgs.hpp"
#include "OgreMaxTypes.hpp"


//Classes----------------------------------------------------------------------
namespace OgreMax
{
    class ApplicationSettings
    {
    public:
        ApplicationSettings();
        ApplicationSettings(const Ogre::String& commandLine);
        ApplicationSettings(int argc, char* argv[]);

        void Initialize(const Ogre::String& commandLine);
        void Initialize(int argc, char* argv[]);

        Ogre::RenderSystem* GetConfiguredRenderSystem() const;
        Ogre::RenderSystem* ConfigureRenderSystem(Ogre::RenderSystem* renderSystem = 0);

        enum RenderingSubsystem
        {
            DIRECT3D,
            OPENGL
        };
        
        /** Sets the currently configured rendering subsystem*/
        void SetRenderingSubsystem(RenderingSubsystem subsystem);

    protected:
        /** Called when the command line has been parsed and the settings should be initialized */
        virtual void Initialize(const CommandLineArgs& commandLine);

        /**
         * Determines if te specified rendering subsystem, given by name,
         * matches the currently configured subsystem. This method takes into
         * account the current platform
         */
        bool IsConfiguredRenderingSubsystem(const Ogre::String& name) const;

        RenderingSubsystem GetAllowedRenderingSubsystem() const;

    protected:
        /** The selected rendering subsystem */
        RenderingSubsystem renderingSubsystem;

    public:
        bool fullScreen;
        bool vsync;
        bool enableNvidiaPerformanceHUD;
        int screenWidth;
        int screenHeight;
        int fullScreenRefreshRate;
                
        /** Empty if none specified. If not empty, will always have a trailing path separator */
        Ogre::String pluginsDirectory;
        
        /** Base file name for screenshots. Will be empty if none are specified */
        Ogre::String screenshotBaseName;

        /** Screenshot file name extension. Includes the leading '.' */
        Ogre::String screenshotExtension;

        Ogre::String fileName;
        Ogre::String resourcesConfigurationFileName;
        Ogre::String pluginsConfigurationFileName;

        struct ResourceLocation
        {
            ResourceLocation()
            {
                this->recursive = false;
            }

            Ogre::String type;
            Ogre::String name;
            bool recursive;
        };
        typedef std::list<ResourceLocation> ResourceLocations;
        ResourceLocations resourceLocations;

        bool lockViewCameraToSceneCamera;
        bool writeUserControlsFile;
        bool keepLogFile;

        Ogre::Real cameraMoveSpeed;

        /** Scene up axis. Used only if a mesh is being viewed */
        Types::UpAxis upAxis;

        /** 
         * Indicates whether scene information should be displayed
         * Used by the OgreMax WinViewer
         */
        bool showInfo;
    };

}

#endif