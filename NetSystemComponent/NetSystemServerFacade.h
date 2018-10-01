#pragma once

#include "NetSystemAbstractServerManager.h"
#include "netSystemTypeDefs.h"
#include "NetMessage.h"
#include "NetSystemFactory.h"

namespace netsystem {

class NetSystemServerFacade
{
public:
	static NetSystemServerFacade * INSTANCE();
	NetSystemServerFacade(void);
	~NetSystemServerFacade(void);

	void startUp( NS_INT port, NS_INT numberOfConnections, NS_INT numberOfAllowedConnections );
	void shutDown();

	void sendReliable( NetServerMessage & message );
	void sendFast( NetServerMessage & message );

	void obtain();

	void setNSSerializablePrototypesContainer( NSSerializablePrototypesContainer * prototypesContainer );
	virtual void setNSServerMessagesDispatcher( NSAbstractServerMessagesDispatcher * dispatcher );
private:
	static NetSystemServerFacade * pInstance;
	NetSystemAbstractServerManager * manager;
};

}