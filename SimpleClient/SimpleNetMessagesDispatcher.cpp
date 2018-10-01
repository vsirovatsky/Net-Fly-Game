#include "StdAfx.h"
#include "SimpleNetMessagesDispatcher.h"

#include "NetConnectedProcessor.h"
#include "NetDisonnectedProcessor.h"
#include "NetCannotConnectProcessor.h"

#include "NetObjectMovingProcessor.h"
#include "NetUserStateChangedProcessor.h"
#include "NetUserStatusReceiveProcessor.h"

using namespace simpleclient;

SimpleNetMessagesDispatcher::SimpleNetMessagesDispatcher( IMessagesSenderProvider * messagesSenderProvider, ISimpleNetState * netState ) 
{
	registerSystemProcessor( new NetConnectedProcessor(messagesSenderProvider, netState) );
	registerSystemProcessor( new NetDisonnectedProcessor(messagesSenderProvider, netState) );
	registerSystemProcessor( new NetCannotConnectProcessor(messagesSenderProvider) );

	registerCustomProcessor( new NetObjectMovingProcessor(messagesSenderProvider) );
	registerCustomProcessor( new NetUserStateChangedProcessor(messagesSenderProvider) );
	registerCustomProcessor( new NetUserStatusReceiveProcessor(messagesSenderProvider, netState) );
}


SimpleNetMessagesDispatcher::~SimpleNetMessagesDispatcher(void)
{
}
