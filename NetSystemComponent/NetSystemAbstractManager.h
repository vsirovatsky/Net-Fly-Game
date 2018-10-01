#pragma once

#include "netSystemTypeDefs.h"
#include "NetMessage.h"

namespace netsystem {

	class NetSystemAbstractManager {
	public:
		NetSystemAbstractManager(){}
		virtual ~NetSystemAbstractManager(){}

		virtual void connect(NS_STRING ip, NS_INT port) = 0;
		virtual void disconnect() = 0;
		virtual bool isConnected() = 0;

		virtual void sendReliable( NetMessage & message ) = 0;
		virtual void sendFast( NetMessage & message ) = 0;

		virtual void obtain() = 0;

		virtual void setNSSerializablePrototypesContainer( NSSerializablePrototypesContainer * prototypesContainer ) = 0;
		virtual void setNSClientMessagesDispatcher( NSAbstractClientMessagesDispatcher * dispatcher ) = 0;
	};

}