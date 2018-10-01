#include "StdAfx.h"
#include "SimpleNetManager.h"
#include "SimpleClientException.h"
#include "Logger.h"
#include "SimpleClientMessage.h"
#include "SimpleNetMessagesDispatcher.h"

#include "PostNetDefaultProcessor.h"
#include "PostNetObjectMovingProcessor.h"

using namespace simpleclient;
using namespace communications;

SimpleNetManager::SimpleNetManager( SimpleNetManagerContext * nContext )
{
	context = nContext;
	netState = new SimpleNetState();
	postOffice = communications::CommunicationsFacade::INSTANCE()->registerPostOffice( communications::NET_COMPONENT_ID );
	sysNet = netsystem::NetSystemClientFacade::INSTANCE();
	serializableContainer = new SerializablePrototypesSimpleContainer();
	sysNet->setNSSerializablePrototypesContainer( serializableContainer );
	sysNet->setNSClientMessagesDispatcher( new SimpleNetMessagesDispatcher(this, netState) );

	postOffice->refisterDefaultFilter( this );
	postOffice->registerDefaultProcessor( new PostNetDefaultProcessor() );
	postOffice->registerProcessor( new PostNetObjectMovingProcessor( this, netState ) );
}

SimpleNetManager::~SimpleNetManager(void)
{
	delete netState;
	delete context;
}

void SimpleNetManager::activate(void)
{
	sysNet->connect(context->ip, context->port);
	if ( IsThreadActive() ) {
		throw SimpleClientInitializationException("Net component already active");
	}
	start();
}

void SimpleNetManager::sendReliable( netsystem::NetMessage & message )
{
	sysNet->sendReliable( message );
}

void SimpleNetManager::sendFast( netsystem::NetMessage & message )
{
	sysNet->sendFast( message );
}

void SimpleNetManager::sendLocal( IMessage * mess, COMPONENT_IDS receiverId )
{
	postOffice->send( mess, receiverId );
}

void SimpleNetManager::sendLocal( PC_MESSAGES_LIST * messagesList, COMPONENT_IDS receiverId )
{
	postOffice->send( messagesList, receiverId );
}

void SimpleNetManager::run()
{
	PRINTINFO("SimpleNetManager: ","started");
	int sleapTime = context->netSleapType;
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
}

void SimpleNetManager::runImpl(){
	postOffice->obtain();
	sysNet->obtain();
	postOffice->flush();
}

bool SimpleNetManager::pass( Envelope * en )
{
	if ( netState->isConnected() ) 
		return true;
	else
		return false;
}