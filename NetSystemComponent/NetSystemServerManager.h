#pragma once

#include "netSystemTypeDefs.h"
#include "NetSystemException.h"
#include "RakPeerInterface.h"
#include "NetSystemAbstractServerManager.h"
#include "MessageIdentifiers.h"
#include "NetMessage.h"
#include "BitStream.h"

namespace netsystem {

class NetSystemServerManager :
	public NetSystemAbstractServerManager
{
public:
	NetSystemServerManager(void);
	virtual ~NetSystemServerManager(void);

	virtual void startUp( NS_INT port, NS_INT numberOfConnections, NS_INT numberOfAllowedConnections );
	virtual void shutDown();

	virtual void sendReliable( NetServerMessage & message );
	virtual void sendFast( NetServerMessage & message );

	virtual void obtain();

	virtual void setNSSerializablePrototypesContainer( NSSerializablePrototypesContainer * prototypesContainer ){this->prototypesContainer = prototypesContainer;}
	virtual void setNSServerMessagesDispatcher( NSAbstractServerMessagesDispatcher * dispatcher ){this->messageDispatcher = dispatcher;};
private:
	RakNet::RakPeerInterface * rPeer;
	NSSerializablePrototypesContainer * prototypesContainer;
	NSAbstractServerMessagesDispatcher * messageDispatcher;
	inline unsigned char getPacketIdentifier(RakNet::Packet *p);
};

}