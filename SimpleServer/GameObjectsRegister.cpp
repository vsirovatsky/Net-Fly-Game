#include "StdAfx.h"
#include "GameObjectsRegister.h"

using namespace simpleserver;

GameObjectsRegister::GameObjectsRegister(void)
{
}


GameObjectsRegister::~GameObjectsRegister(void)
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<OBJECT_IDENTITY, GameObject *>::iterator it = objects.begin(); it!=objects.end(); ++it ) {
		delete it->second;
	}
}

bool GameObjectsRegister::isObjectExists( OBJECT_IDENTITY id )
{
	if ( objects.find(id) == objects.end() )
		return false;
	else
		return true;
}

void GameObjectsRegister::addObject( OBJECT_IDENTITY id , GameObject * obj )
{
	if (objects.find(id) != objects.end()){
		objects.erase(id);
	}
	objects.insert( std::pair<OBJECT_IDENTITY, GameObject *>( id, obj ) );
}

void GameObjectsRegister::removeObject( OBJECT_IDENTITY id )
{
	if (objects.find(id) != objects.end()){
		delete (objects.find(id)->second);
		objects.erase(id);
	}
}

GameObject * GameObjectsRegister::getObject( OBJECT_IDENTITY id )
{
	return objects[id];
}

void GameObjectsRegister::iterateAll()
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<OBJECT_IDENTITY, GameObject *>::iterator it = objects.begin(); it!=objects.end(); ++it ) {
		it->second->iterate();
	}
}

void GameObjectsRegister::visitAll( GameObjectsUpdateCollector & visitor )
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<OBJECT_IDENTITY, GameObject *>::iterator it = objects.begin(); it!=objects.end(); ++it ) {
		it->second->visit( visitor );
	}
}