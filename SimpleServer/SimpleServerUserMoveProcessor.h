#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"
#include "IUserManagementProvider.h"

namespace simpleserver {

class SimpleServerUserMoveProcessor : public netsystem::NSIServerCustomMessageProcessor
{
public:
	SimpleServerUserMoveProcessor( IMessagesSenderProvider *, IUserManagementProvider *);
	virtual ~SimpleServerUserMoveProcessor(void);
	virtual void process( netsystem::NetServerMessage & mess );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
	IUserManagementProvider * userManagementProvider;
};

}