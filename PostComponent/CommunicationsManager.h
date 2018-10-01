#pragma once

#include "CommunicationsAbstractManager.h"
#include "PostOffice.h"
#include "CommunicationsMessage.h"

#include "ThreadWrapper.h"
#include "SimpleMutex.h"

namespace communications {

class CommunicationsManager : public CommunicationsAbstractManager, common::thread
{
public:
	CommunicationsManager(void);
	virtual ~CommunicationsManager(void);

	virtual void activate( int nThreadSleepTime );
	virtual AbstractPostOffice * registerPostOffice( COMPONENT_IDS officeId );

	virtual void run();
private:
	int threadSleepTime;
	void runImpl();
	PostOffice * getOffice( COMPONENT_IDS officeId );
	void lostMessage( Envelope * en );
private:
	common::SimpleMutex topMutex;
	PostOffice * postOffice_COMMUNICATIONS;
	PostOffice * postOffice_MASTER;
	PostOffice * postOffice_INPUT;
	PostOffice * postOffice_NET;
	PostOffice * postOffice_FILE;
	PostOffice * postOffice_SOUND;
	PostOffice * postOffice_VIDEO;
};

}
