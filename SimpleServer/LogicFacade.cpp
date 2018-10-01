#include "StdAfx.h"
#include "LogicFacade.h"
#include "GameObjectsUpdateCollector.h"

using namespace simpleserver;

LogicFacade * LogicFacade::instance = new LogicFacade();

LogicFacade * LogicFacade::INSTANCE(){
	return instance;
}

LogicFacade::LogicFacade(void)
{
}


LogicFacade::~LogicFacade(void)
{
}

void LogicFacade::iterate()
{
	manager.iterate();
}

void LogicFacade::sendUpdates( IMessagesSenderProvider * senderProvider, IUserManagementProvider * userManagementProvider )
{
	GameObjectsUpdateCollector visitor = GameObjectsUpdateCollector();
	manager.visitAll( visitor );
	visitor.sendUpdates( senderProvider, userManagementProvider );
}