#include "StdAfx.h"
#include "NetConnectedProcessor.h"
#include "Logger.h"

using namespace simpleclient;

NetConnectedProcessor::NetConnectedProcessor( IMessagesSenderProvider * _messagesSenderProvider, ISimpleNetState * _netState ) : messagesSenderProvider(_messagesSenderProvider), netState(_netState)
{
}


NetConnectedProcessor::~NetConnectedProcessor(void)
{
}

void NetConnectedProcessor::process( NS_Serializable * data )
{
	netState->setConnected();
}

NS_MESSAGE_TYPE NetConnectedProcessor::getType()
{
	return NS_SYSTEM_CLIENT_MESSAGE_CONNECTED;
}
