#include "GameObjectsManager.h"

LivingObjectsRegister::~LivingObjectsRegister(void)
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, LivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		delete it->second;
	}
}

void LivingObjectsRegister::put( LivingObject * obj )
{
	objects.insert( std::pair<BE_ID, LivingObject *>(obj->getId(), obj) );
}

void LivingObjectsRegister::remove( BE_ID id )
{
	std::hash_map<BE_ID, LivingObject *>::iterator it = objects.find( id );
	if ( it != objects.end() ) {
		delete it->second;
		objects.erase( it );
	}
}

LivingObject * LivingObjectsRegister::get( BE_ID id )
{
	std::hash_map<BE_ID, LivingObject *>::iterator it = objects.find( id );
	if ( it == objects.end() ) 
		return 0;
	else
		return it->second;
}

void LivingObjectsRegister::renderAll()
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, LivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		it->second->render();
	}
}

void LivingObjectsRegister::iterateAll()
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, LivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		it->second->iterate();
	}
}

void LivingObjectsRegister::moveAllBy( vector2d & moveBy )
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, LivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		it->second->movePos( moveBy );
	}
}

void LivingObjectsRegister::populateNearBy( std::vector<LivingObject*> & container, vector2d center, BE_FLOAT dist )
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, LivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		if ( center.getDistance(it->second->getPos()) <= dist ) 
			container.push_back( it->second );
	}
}



//Non living
NonLivingObjectsRegister::~NonLivingObjectsRegister(void)
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, NonLivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		delete it->second;
	}
}

void NonLivingObjectsRegister::put( NonLivingObject * obj )
{
	objects.insert( std::pair<BE_ID, NonLivingObject *>(obj->getId(), obj) );
}

void NonLivingObjectsRegister::remove( BE_ID id )
{
	std::hash_map<BE_ID, NonLivingObject *>::iterator it = objects.find( id );
	if ( it != objects.end() ) {
		delete it->second;
		objects.erase( it );
	}
}

NonLivingObject * NonLivingObjectsRegister::get( BE_ID id )
{
	std::hash_map<BE_ID, NonLivingObject *>::iterator it = objects.find( id );
	if ( it == objects.end() ) 
		return 0;
	else
		return it->second;
}

void NonLivingObjectsRegister::renderAll()
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, NonLivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		it->second->render();
	}
}

void NonLivingObjectsRegister::moveAllBy( vector2d & moveBy )
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, NonLivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		it->second->movePos( moveBy );
	}
}

void NonLivingObjectsRegister::populateNearBy( std::vector<NonLivingObject*> & container, vector2d center, BE_FLOAT dist )
{
	if ( objects.empty() ) 
		return;
	for ( std::hash_map<BE_ID, NonLivingObject *>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		if ( center.getDistance(it->second->getPos()) <= dist ) 
			container.push_back( it->second );
	}
}
