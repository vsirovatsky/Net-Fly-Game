#pragma once

#include "NetSystemAbstractManager.h"
#include "netSystemTypeDefs.h"
#include "NetMessage.h"
#include "NetSystemFactory.h"

namespace netsystem {

class NetSystemClientFacade
{
public:
	static NetSystemClientFacade * INSTANCE();
	NetSystemClientFacade(void);
	~NetSystemClientFacade(void);

	void connect(NS_STRING ip, NS_INT port);
	void disconnect();
	bool isConnected();

	void sendReliable( NetMessage & message );
	void sendFast( NetMessage & message );

	void obtain();

	void setNSSerializablePrototypesContainer( NSSerializablePrototypesContainer * prototypesContainer );
	void setNSClientMessagesDispatcher( NSAbstractClientMessagesDispatcher * dispatcher );
private:
	static NetSystemClientFacade * pInstance;
	NetSystemAbstractManager * manager;
};

}