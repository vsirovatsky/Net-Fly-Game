#pragma once;
#include "PostOffice.h"

namespace communications {

class CommunicationsAbstractManager {
public:
	CommunicationsAbstractManager(){};
	virtual ~CommunicationsAbstractManager(){};
	virtual void activate( int nThreadSleepTime ) = 0;
	virtual AbstractPostOffice * registerPostOffice( COMPONENT_IDS officeId ) = 0;
};

class CommunicationsFactory 
{
public:
	static CommunicationsAbstractManager * createCommunicationsManager();
};

}