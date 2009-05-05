#ifndef _APEENGINE_LOADER_H
#define _APEENGINE_LOADER_H

#include "InputHandler.h"
#include "OgreRender.h"
//#include "Receiver.h"

class ApeLoaderApp
{
public:
	ApeLoaderApp(const char* cmdLine);
	~ApeLoaderApp();
    
    void go(void);

	const char* mName;
}; 

#endif