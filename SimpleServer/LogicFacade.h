#pragma once

#include "GameObjectsManager.h"
#include "IMessagesSenderProvider.h"
#include "IUserManagementProvider.h"

namespace simpleserver {

class LogicFacade
{
public:
	LogicFacade(void);
	~LogicFacade(void);

	static LogicFacade * INSTANCE();

	GameObjectsManager & getGameObjectsManager(){return manager;}

	void iterate();
	void sendUpdates( IMessagesSenderProvider *, IUserManagementProvider * );
private:
	static LogicFacade * instance;

	GameObjectsManager manager;
};

}