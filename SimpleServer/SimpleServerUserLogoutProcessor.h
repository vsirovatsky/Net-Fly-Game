#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"
#include "IUserManagementProvider.h"

namespace simpleserver {

class SimpleServerUserLogoutProcessor : public netsystem::NSIServerSystemMessageProcessor 
{
public:
	SimpleServerUserLogoutProcessor( IMessagesSenderProvider *, IUserManagementProvider * );
	virtual ~SimpleServerUserLogoutProcessor(void);
	virtual void process( netsystem::NetServerMessage & mess );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
	IUserManagementProvider * userManagementProvider;
};

}