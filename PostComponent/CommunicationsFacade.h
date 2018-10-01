#pragma once

#include "communicationsTypeDefs.h"
#include "CommunicationsAbstractManager.h"
#include "CommunicationsMessage.h"
#include "PostOffice.h"

namespace communications {

class CommunicationsFacade {
public:
	static CommunicationsFacade * INSTANCE();
	CommunicationsFacade(void);
	~CommunicationsFacade(void);

	void activate( int nThreadSleepTime );

	AbstractPostOffice * registerPostOffice( COMPONENT_IDS officeId );
private:
	static CommunicationsFacade * pInstance;
	CommunicationsAbstractManager * manager;
};

}