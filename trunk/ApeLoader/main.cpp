#include <Ogre.h>
#include <ApeLoaderApp.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char *argv[])
#endif
{
	char* cmdLine;

	#ifdef WIN32
		cmdLine = strCmdLine;
	#else
		cmdLine = "";
	#endif

    // Create application object
    ApeLoaderApp app(cmdLine);

    try {
        app.go();
    } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox( NULL, (e.getFullDescription().c_str()), "Ogre exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occured: " <<
            e.getFullDescription().c_str() << std::endl;
#endif
    } 

    return 0;
}


