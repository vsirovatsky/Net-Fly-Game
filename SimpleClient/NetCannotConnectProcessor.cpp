#include "StdAfx.h"
#include "NetCannotConnectProcessor.h"
#include "Logger.h"

using namespace simpleclient;

NetCannotConnectProcessor::NetCannotConnectProcessor( IMessagesSenderProvider * _messagesSenderProvider ) : messagesSenderProvider(_messagesSenderProvider)
{
}


NetCannotConnectProcessor::~NetCannotConnectProcessor(void)
{
}

void NetCannotConnectProcessor::process( NS_Serializable * data )
{
	PRINT("connection failed");
}

NS_MESSAGE_TYPE NetCannotConnectProcessor::getType()
{
	return NS_SYSTEM_CLIENT_MESSAGE_CONNECTION_FAILED;
}