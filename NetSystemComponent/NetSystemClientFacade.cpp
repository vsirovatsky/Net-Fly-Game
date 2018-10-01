#include "NetSystemClientFacade.h"

namespace netsystem {

NetSystemClientFacade * NetSystemClientFacade::pInstance = 0;

NetSystemClientFacade * NetSystemClientFacade::INSTANCE(){
	if ( pInstance == 0 ) {
		pInstance = new NetSystemClientFacade();
	}
	return pInstance;
}

NetSystemClientFacade::NetSystemClientFacade(void)
{
	manager = NetSystemFactory::createNetSystemClientManager();
}


NetSystemClientFacade::~NetSystemClientFacade(void)
{
	if ( manager != 0 ) {
		delete manager;
	}
}

void NetSystemClientFacade::connect(NS_STRING ip, NS_INT port)
{
	manager->connect( ip, port );
}

void NetSystemClientFacade::disconnect()
{
	manager->disconnect();
}

bool NetSystemClientFacade::isConnected()
{
	return manager->isConnected();
}

void NetSystemClientFacade::sendReliable( NetMessage & message )
{
	manager->sendReliable( message );
}

void NetSystemClientFacade::sendFast( NetMessage & message )
{
	manager->sendFast( message );
}

void NetSystemClientFacade::obtain()
{
	manager->obtain();
}

void NetSystemClientFacade::setNSSerializablePrototypesContainer( NSSerializablePrototypesContainer * prototypesContainer )
{
	manager->setNSSerializablePrototypesContainer( prototypesContainer );
}

void NetSystemClientFacade::setNSClientMessagesDispatcher( NSAbstractClientMessagesDispatcher * dispatcher )
{
	manager->setNSClientMessagesDispatcher( dispatcher );
}

}