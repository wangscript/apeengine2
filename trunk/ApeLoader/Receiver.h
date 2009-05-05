#ifndef _Receiver_H_
#define _Receiver_H_

#include "sigslot.h"
//#include "MessageManager.h"


using namespace sigslot;

class MessageManager;

class Receiver : public has_slots<>
{
public:
	
	enum ApplicationState { 
		UNINITIALIZED,
		INITIALIZED, 
		RUNNING,
	};

	Receiver() {

	};
	~Receiver() {};

	virtual void makeConnections() {};

private:

};

#endif
