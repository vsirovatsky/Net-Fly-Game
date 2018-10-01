#pragma once

#include "ThreadWrapper.h"
#include "SimpleMutex.h"
#include "SimpleNetMessages.h"
#include "NetSystemServerFacade.h"
#include "SimpleObjectIdentetyGenerator.h"
#include "SimpleUsersRegister.h"
#include "SimpleServerMessagesDispatcher.h"
#include "IMessagesSenderProvider.h"

#include "GameObjectsManager.h"

namespace simpleserver {

struct SimpleNetManagerContext 
{
	int netSleapType;
	int port;
	int numberOfConnections;
	int numberOfAllowedConnections;
};

class SimpleNetManager : public common::thread, public IMessagesSenderProvider
{
public:
	SimpleNetManager( SimpleNetManagerContext * nContext );
	~SimpleNetManager(void);
	
	IUserManagementProvider * getUserManagementProvider(){return &userRegister;}

	// from IMessagesSenderProvider
	virtual void sendReliable( netsystem::NetServerMessage & message );
	virtual void sendFast( netsystem::NetServerMessage & message );

	virtual void run();
	void iterate();
	void activate();
private:
	netsystem::NetSystemServerFacade * sysNet;
	SerializablePrototypesSimpleContainer * serializableContainer;
	SimpleNetManagerContext * context;
	void runImpl();
	SimpleObjectIdentetyGenerator ioGenerator;
	SimpleUsersRegister userRegister;
};

}

