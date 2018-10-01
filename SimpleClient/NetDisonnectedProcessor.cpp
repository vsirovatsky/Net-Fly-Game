#include "StdAfx.h"
#include "NetDisonnectedProcessor.h"
#include "Logger.h"

using namespace simpleclient;

NetDisonnectedProcessor::NetDisonnectedProcessor( IMessagesSenderProvider * _messagesSenderProvider, ISimpleNetState * _netState ) : messagesSenderProvider(_messagesSenderProvider), netState(_netState)
{
}


NetDisonnectedProcessor::~NetDisonnectedProcessor(void)
{
}

void NetDisonnectedProcessor::process( NS_Serializable * data )
{
	netState->setDisconnected();
}

NS_MESSAGE_TYPE NetDisonnectedProcessor::getType()
{
	return NS_SYSTEM_CLIENT_MESSAGE_DISCONNECTED;
}