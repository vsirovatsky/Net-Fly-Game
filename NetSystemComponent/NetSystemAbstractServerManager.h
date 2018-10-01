#pragma once

#include "NetMessage.h"
#include "netSystemTypeDefs.h"

namespace netsystem {

class NetSystemAbstractServerManager
{
public:
	NetSystemAbstractServerManager(void){}
	virtual ~NetSystemAbstractServerManager(void){}

	virtual void startUp( NS_INT port, NS_INT numberOfConnections, NS_INT numberOfAllowedConnections ) = 0;
	virtual void shutDown() = 0;

	virtual void sendReliable( NetServerMessage & message ) = 0;
	virtual void sendFast( NetServerMessage & message ) = 0;

	virtual void obtain() = 0;

	virtual void setNSSerializablePrototypesContainer( NSSerializablePrototypesContainer * prototypesContainer ) = 0;
	virtual void setNSServerMessagesDispatcher( NSAbstractServerMessagesDispatcher * dispatcher ) = 0;
};

}