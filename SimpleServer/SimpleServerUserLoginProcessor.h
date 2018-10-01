#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"
#include "IUserManagementProvider.h"

namespace simpleserver {

class SimpleServerUserLoginProcessor : public netsystem::NSIServerSystemMessageProcessor 
{
public:
	SimpleServerUserLoginProcessor( IMessagesSenderProvider *, IUserManagementProvider * );
	virtual ~SimpleServerUserLoginProcessor(void);
	virtual void process( netsystem::NetServerMessage & mess );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
	IUserManagementProvider * userManagementProvider;
};

}