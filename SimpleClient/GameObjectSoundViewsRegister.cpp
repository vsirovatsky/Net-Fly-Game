#include "StdAfx.h"
#include "GameObjectSoundViewsRegister.h"

using namespace simpleclient;

GameObjectSoundViewsRegister::GameObjectSoundViewsRegister( soundsystem::SoundSystemFacade * _sysSound, SimpleSoundResolvedResourcesContainer * _resourcesContainer ) : sysSound(_sysSound), resourcesContainer(_resourcesContainer)
{
}

GameObjectSoundViewsRegister::~GameObjectSoundViewsRegister(void)
{
	if ( soundObjects.empty() ) 
		return;
	for ( std::hash_map<OBJECT_IDENTITY, GameObjectSoundView *>::iterator it = soundObjects.begin(); it != soundObjects.end(); ++it ) {
		delete it->second;
	}
}

void GameObjectSoundViewsRegister::addObject( OBJECT_IDENTITY id )
{
	removeObject(id);
	soundObjects.insert( std::pair<OBJECT_IDENTITY, GameObjectSoundView *>(id, new GameObjectSoundView(id, sysSound, &currentUserPos, resourcesContainer)) );
}

void GameObjectSoundViewsRegister::removeObject( OBJECT_IDENTITY id )
{
	if ( soundObjects.find(id) != soundObjects.end() ) {
		delete soundObjects.find(id)->second;
		soundObjects.erase(id);
	}
}

void GameObjectSoundViewsRegister::iterate()
{
	for ( std::hash_map<OBJECT_IDENTITY, GameObjectSoundView *>::iterator it = soundObjects.begin(); it != soundObjects.end(); ++it ) {
		it->second->iterate();
	}
}

void GameObjectSoundViewsRegister::processSoundData( SoundInformation & info )
{
	if ( info.create ) {
		addObject( info.objId );
		std::hash_map<OBJECT_IDENTITY, GameObjectSoundView *>::iterator it = soundObjects.find( info.objId );
		it->second->processSoundData( info );
		return;
	}
	if ( info.remove ) {
		std::hash_map<OBJECT_IDENTITY, GameObjectSoundView *>::iterator it = soundObjects.find( info.objId );
		if ( it != soundObjects.end() ) {
			it->second->processSoundData( info );
		}
		removeObject( info.objId );
		return;
	}
	std::hash_map<OBJECT_IDENTITY, GameObjectSoundView *>::iterator it = soundObjects.find( info.objId );
	if ( it == soundObjects.end() ) {
		return;
	}
	it->second->processSoundData( info );
}

void GameObjectSoundViewsRegister::setCurrentPos( vector3df & _currentUserPos )
{
	currentUserPos.x = _currentUserPos.x;
	currentUserPos.y = _currentUserPos.y;
	currentUserPos.z = _currentUserPos.z;
}