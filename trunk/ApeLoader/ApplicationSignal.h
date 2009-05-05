#ifndef _APP_SIGNAL_H_
#define _APP_SIGNAL_H_

#include "sigslot.h"
#include "ApplicationSlot.h"

using namespace sigslot;

class ApplicationSignal
{
public:
	
	ApplicationSignal() { //void* test
		//test->StateChanged.connect(this, &ApeLoaderApp::OnStateChanged);
	};
	~ApplicationSignal() {};

	//virtual 
	signal1<ApplicationSlot::ApplicationState> AppState;

private:
};

#endif
