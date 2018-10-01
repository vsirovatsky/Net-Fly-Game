#include "StdAfx.h"
#include "Logger.h"
#include "SimpleNetManager.h"
#include "SimpleServerException.h"

using namespace simpleserver;

SimpleNetManager::SimpleNetManager( SimpleNetManagerContext * nContext ) : ioGenerator(), userRegister()
{
	context = nContext;
	sysNet = netsystem::NetSystemServerFacade::INSTANCE();
	serializableContainer = new SerializablePrototypesSimpleContainer();
	sysNet->setNSSerializablePrototypesContainer( serializableContainer );
	sysNet->setNSServerMessagesDispatcher( new SimpleServerMessagesDispatcher( this, &userRegister ) );
}

SimpleNetManager::~SimpleNetManager(void)
{
}

void SimpleNetManager::activate(void)
{
	sysNet->startUp( context->port, context->numberOfConnections, context->numberOfAllowedConnections );
	if ( IsThreadActive() ) {
		throw SimpleServerInitializationException("COMMUNICATIONS already active");
	}
	//start();
}

void SimpleNetManager::run()
{
	/*
	int sleapTime = context->netSleapType;
	PRINTINFO( "SimpleNetManager: ", "started" );
	while ( true ) {
		try {
			Sleep( sleapTime );
			//topMutex.Lock();
			
			runImpl();

			//topMutex.Unlock();
		} catch (...) {
			//topMutex.Unlock();
			throw;
		}
	}
	*/
}

void SimpleNetManager::iterate()
{
	runImpl();
}

void SimpleNetManager::runImpl(){
	sysNet->obtain();
}

void SimpleNetManager::sendReliable( netsystem::NetServerMessage & message )
{
	sysNet->sendReliable( message );
}

void SimpleNetManager::sendFast( netsystem::NetServerMessage & message )
{
	sysNet->sendFast( message );
}
