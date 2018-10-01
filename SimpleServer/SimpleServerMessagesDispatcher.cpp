#include "StdAfx.h"
#include "SimpleServerMessagesDispatcher.h"

//Processors
#include "SimpleServerUserLoginProcessor.h"
#include "SimpleServerUserLogoutProcessor.h"
#include "SimpleServerUserMoveProcessor.h"

using namespace simpleserver;

SimpleServerMessagesDispatcher::SimpleServerMessagesDispatcher( IMessagesSenderProvider * messagesSenderProvider, IUserManagementProvider * userManagementProvider ) : netsystem::NSAbstractServerMessagesDispatcher()
{
	//System processors
	registerSystemProcessor( new SimpleServerUserLoginProcessor(messagesSenderProvider, userManagementProvider) );
	registerSystemProcessor( new SimpleServerUserLogoutProcessor(messagesSenderProvider, userManagementProvider) );

	//Custom processors
	registerCustomProcessor( new SimpleServerUserMoveProcessor(messagesSenderProvider, userManagementProvider) );
}


SimpleServerMessagesDispatcher::~SimpleServerMessagesDispatcher(void)
{
}
