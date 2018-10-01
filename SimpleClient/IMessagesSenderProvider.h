#pragma once

#include "SimpleNetMessages.h"
#include "CommunicationsMessage.h"

namespace simpleclient {

using namespace communications;

class IMessagesSenderProvider {
public:
	IMessagesSenderProvider(){}
	virtual ~IMessagesSenderProvider(){}
	virtual void sendReliable( netsystem::NetMessage & message ) = 0;
	virtual void sendFast( netsystem::NetMessage & message ) = 0;

	// Local sending
	virtual void sendLocal( IMessage * mess, COMPONENT_IDS receiverId ) = 0;
	virtual void sendLocal( PC_MESSAGES_LIST * messagesList, COMPONENT_IDS receiverId ) = 0;

};

}
