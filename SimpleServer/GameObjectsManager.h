#pragma once

#include "GameObjectsRegister.h"
#include "UserMovementInformationDispatcher.h"

namespace simpleserver {

class GameObjectsManager
{
public:
	GameObjectsManager(void);
	virtual ~GameObjectsManager(void);

	void createGameObject( OBJECT_IDENTITY );
	void deleteGameObject( OBJECT_IDENTITY );

	void setOperatableByUser( OBJECT_IDENTITY, bool );

	void iterate();
	void visitAll( GameObjectsUpdateCollector & );

	UserMovementInformationDispatcher userMovementInformationDispatcher;
private:
	GameObjectsRegister objectsRegister;
};

}