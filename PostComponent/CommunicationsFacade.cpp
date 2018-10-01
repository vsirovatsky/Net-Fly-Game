#include "stdafx.h"
#include "CommunicationsFacade.h"
#include "CommunicationsAbstractManager.h"
#include "CommunicationsManager.h"

using namespace communications;

CommunicationsAbstractManager * CommunicationsFactory::createCommunicationsManager()
{
	return new CommunicationsManager();
}


CommunicationsFacade * CommunicationsFacade::pInstance = 0;

CommunicationsFacade * CommunicationsFacade::INSTANCE(){
	if ( pInstance == 0 ) {
		pInstance = new CommunicationsFacade();
	}
	return pInstance;
}

CommunicationsFacade::CommunicationsFacade(void)
{
	manager = CommunicationsFactory::createCommunicationsManager();
}

CommunicationsFacade::~CommunicationsFacade(void)
{
	if ( manager != 0 ) {
		delete manager;
	}
}

void CommunicationsFacade::activate( int nThreadSleepTime )
{
	manager->activate( nThreadSleepTime );
}

AbstractPostOffice * CommunicationsFacade::registerPostOffice( COMPONENT_IDS officeId )
{
	return manager->registerPostOffice( officeId );
}
