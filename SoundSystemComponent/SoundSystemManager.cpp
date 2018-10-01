#include "StdAfx.h"
#include "SoundSystemManager.h"

namespace soundsystem {

SoundSystemManager::SoundSystemManager(void) : sounds()
{
}

SoundSystemManager::~SoundSystemManager(void)
{
	sounds.clear();
	if (engine) {
		engine->drop();
	}
}

void SoundSystemManager::init()
{
	engine = createIrrKlangDevice();
	if (!engine) {
		throw new SoundSystemException( "cannot create irr klang device" );
	}
}

void SoundSystemManager::stopAllSound()
{
	engine->stopAllSounds();
}

void SoundSystemManager::play2D( SoundData data )
{
	if ( !(data.track) ) {
		// play single without tracking of sound
		engine->play2D( data.address.data(), data.looped, false, data.track );
		return;
	}
	validateNotExisted( data.id );
	ISound* music = engine->play2D( data.address.data(), data.looped, true, data.track );
	music->setVolume( data.volume );
	music->setIsPaused( false );
	std::pair<SS_ID, ISound *> p = std::pair<SS_ID, ISound*>( SS_ID(data.id), music );
	sounds.insert( p );
}

void SoundSystemManager::play3D( SoundData3D data )
{
	if ( !(data.track) ) {
		// play single without tracking of sound
		engine->play3D( data.address.data(), vec3df(data.x, data.y, data.z), data.looped, false, data.track );
		return;
	}
	validateNotExisted( data.id );
	ISound* music = engine->play3D( data.address.data(), vec3df(data.x, data.y, data.z), data.looped, false, data.track );
	music->setMinDistance( data.minDis );
	music->setMaxDistance( data.maxDis );
	music->setVolume( data.volume );
	music->setIsPaused( false );
	std::pair<SS_ID, ISound *> p = std::pair<SS_ID, ISound*>( SS_ID(data.id), music );
	sounds.insert( p );
}

void SoundSystemManager::validateNotExisted( SS_ID id )
{
	if ( sounds.find(id) != sounds.end() ) {
		throw (new SoundSystemException( "sound with such id already tracked: " ))->addMessage( id );
	}
}

void SoundSystemManager::drop( SS_ID id )
{
	ISound * sound = getById( id );
	sound->setIsPaused(true);
	sound->drop();
	sounds.erase( sounds.find(id) );
}

ISound * SoundSystemManager::getById( SS_ID id )
{
	std::hash_map<SS_ID, ISound*>::iterator & it = sounds.find(id);
	if ( it != sounds.end() ) {
		return it->second;
	} else {
		throw (new SoundSystemException( "sound with such id do not exists: " ))->addMessage( id );
	}
}

void SoundSystemManager::update3DPosition( SS_ID id, float x, float y, float z )
{
	getById( id )->setPosition( vec3df(x,y,z) );
}

void SoundSystemManager::update3DMinDistance( SS_ID id, float dis )
{
	getById( id )->setMinDistance( dis );
}

void SoundSystemManager::update3DMaxDistance( SS_ID id, float dis )
{
	getById( id )->setMaxDistance( dis );
}

void SoundSystemManager::updateVolume( SS_ID id, float volume )
{
	getById( id )->setVolume( volume );
}

}