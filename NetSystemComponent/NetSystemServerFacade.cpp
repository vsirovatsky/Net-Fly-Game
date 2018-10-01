#include "NetSystemServerFacade.h"

namespace netsystem {

NetSystemServerFacade * NetSystemServerFacade::pInstance = 0;

NetSystemServerFacade * NetSystemServerFacade::INSTANCE(){
	if ( pInstance == 0 ) {
		pInstance = new NetSystemServerFacade();
	}
	return pInstance;
}

NetSystemServerFacade::NetSystemServerFacade(void)
{
	manager = NetSystemFactory::createNetSystemServerManager();
}


NetSystemServerFacade::~NetSystemServerFacade(void)
{
	if ( manager ) {
		delete manager;
	}
}

void NetSystemServerFacade::startUp( NS_INT port, NS_INT numberOfConnections, NS_INT numberOfAllowedConnections )
{
	manager->startUp( port, numberOfConnections, numberOfAllowedConnections);
}

void NetSystemServerFacade::shutDown()
{
	manager->shutDown();
}

void NetSystemServerFacade::sendReliable( NetServerMessage & message )
{
	manager->sendReliable( message );
}

void NetSystemServerFacade::sendFast( NetServerMessage & message )
{
	manager->sendFast( message );
}

void NetSystemServerFacade::obtain()
{
	manager->obtain();
}

void NetSystemServerFacade::setNSSerializablePrototypesContainer( NSSerializablePrototypesContainer * prototypesContainer )
{
	manager->setNSSerializablePrototypesContainer( prototypesContainer );
}

void NetSystemServerFacade::setNSServerMessagesDispatcher( NSAbstractServerMessagesDispatcher * dispatcher )
{
	manager->setNSServerMessagesDispatcher( dispatcher );
}

}