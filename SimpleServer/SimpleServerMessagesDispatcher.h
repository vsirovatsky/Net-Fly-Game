#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"
#include "IUserManagementProvider.h"
#include "IUserMovementInformationDispatcher.h"

namespace simpleserver{

class SimpleServerMessagesDispatcher : public netsystem::NSAbstractServerMessagesDispatcher
{
public:
	SimpleServerMessagesDispatcher( IMessagesSenderProvider *, IUserManagementProvider * );
	virtual ~SimpleServerMessagesDispatcher(void);
};

}