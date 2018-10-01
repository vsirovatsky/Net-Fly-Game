#include "StdAfx.h"
#include "GameObjectsManager.h"
#include "SimpleServerException.h"
#include "SimpleServerTypeDefs.h"

using namespace simpleserver;

GameObjectsManager::GameObjectsManager(void)
{
}


GameObjectsManager::~GameObjectsManager(void)
{
}

void GameObjectsManager::createGameObject( OBJECT_IDENTITY id )
{
	GameObject * obj  = new GameObject( id );
	objectsRegister.addObject( id, obj );
}

void GameObjectsManager::deleteGameObject( OBJECT_IDENTITY id )
{
	objectsRegister.removeObject( id );
}

void GameObjectsManager::setOperatableByUser( OBJECT_IDENTITY id, bool isOperatable )
{
	if ( !objectsRegister.isObjectExists(id) )
		throw SimpleServerException("GameObjectsManager setOperatableByUser user not found");
	GameObject * obj  = objectsRegister.getObject( id );
	if ( isOperatable ) {
		obj->movementController.obtainYourselfStrategy( MOVEMENT_STRATEGY_USER_FLY );
		userMovementInformationDispatcher.addProcessor( id, &(obj->movementController) );
	} else {
		obj->movementController.obtainYourselfStrategy( MOVEMENT_STRATEGY_BLANK );
		userMovementInformationDispatcher.clearProcessor( id );
	}
}

void GameObjectsManager::iterate()
{
	objectsRegister.iterateAll();
}

void GameObjectsManager::visitAll( GameObjectsUpdateCollector & visitor )
{
	objectsRegister.visitAll( visitor );
}