#include "StdAfx.h"
#include "VideoObjectsRegister.h"

using namespace simpleclient;

VideoObjectsRegister::VideoObjectsRegister( VideoSoundPlayRequester * _soundPlayRequester ) : timeDiffWithServer(0), soundPlayRequester(_soundPlayRequester)
{
}


VideoObjectsRegister::~VideoObjectsRegister(void)
{
}

videosystem::IVideoObject * VideoObjectsRegister::get( OBJECT_IDENTITY oi )
{
	if ( regObjects.find(oi) == regObjects.end() ) {
		return 0;
	} else {
		return regObjects.find(oi)->second;
	}
}

VideoObjectMovementController * VideoObjectsRegister::getMovementController( OBJECT_IDENTITY oi )
{
	if ( regControllers.find(oi) == regControllers.end() ) {
		return 0;
	} else {
		return regControllers.find(oi)->second;
	}
}

void VideoObjectsRegister::store( OBJECT_IDENTITY oi, videosystem::IVideoObject * obj)
{
	if (regObjects.find(oi) != regObjects.end()){
		regObjects.erase(oi);
		regControllers.erase(oi);
	}
	regObjects.insert( std::pair<OBJECT_IDENTITY, videosystem::IVideoObject *>( oi, obj ) );
	regControllers.insert( std::pair<OBJECT_IDENTITY, VideoObjectMovementController *>( oi, new VideoObjectMovementController( timeDiffWithServer ) ) );
	soundPlayRequester->add( oi );
}

void VideoObjectsRegister::remove( OBJECT_IDENTITY oi)
{
	if (regObjects.find(oi) != regObjects.end()){
		soundPlayRequester->remove( oi );
		regObjects.find(oi)->second->remove();
		delete (regObjects.find(oi)->second);
		delete (regControllers.find(oi)->second);
		regObjects.erase(oi);
		regControllers.erase(oi);
	}
}

void VideoObjectsRegister::updateUbjectsPositions()
{
	if ( regObjects.empty() ) 
		return;
	for ( std::hash_map<OBJECT_IDENTITY, VideoObjectMovementController *>::iterator it = regControllers.begin(); it != regControllers.end(); ++it ) {
		std::hash_map<OBJECT_IDENTITY, videosystem::IVideoObject *>::iterator objIt = regObjects.find( it->first );
		if ( it->second->isMoving() ) {
			videosystem::vector3df pos = it->second->getNextPos();
			objIt->second->setPosition( pos );
			soundPlayRequester->updateObjectPosition( it->first, pos.x, pos.y, pos.z );
		}
	}
}