#pragma once

#include "ThreadWrapper.h"
#include "SimpleMutex.h"
#include "SimpleNetMessages.h"
#include "NetSystemClientFacade.h"
#include "SimpleClientContext.h"
#include "CommunicationsFacade.h"
#include "IMessagesSenderProvider.h"
#include "SimpleNetState.h"

namespace simpleclient {

using namespace communications;

class SimpleNetManager : public common::thread, public IMessagesSenderProvider, public IPostFilter
{
public:
	SimpleNetManager( SimpleNetManagerContext * nContext );
	~SimpleNetManager(void);
	
	virtual void run();
	void activate();

	// from IMessagesSenderProvider
	virtual void sendReliable( netsystem::NetMessage & message );
	virtual void sendFast( netsystem::NetMessage & message );
	virtual void sendLocal( IMessage * mess, COMPONENT_IDS receiverId );
	virtual void sendLocal( PC_MESSAGES_LIST * messagesList, COMPONENT_IDS receiverId );

	// from IPostFilter
	virtual bool pass( Envelope * en );

	bool isConnected(){return netState->isConnected();};
private:
	ISimpleNetState * netState;
	netsystem::NetSystemClientFacade * sysNet;
	SerializablePrototypesSimpleContainer * serializableContainer;
	SimpleNetManagerContext * context;
	AbstractPostOffice * postOffice;
	void runImpl();
};

}