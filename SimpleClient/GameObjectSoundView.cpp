#include "StdAfx.h"
#include "GameObjectSoundView.h"

using namespace simpleclient;

GameObjectSoundView::GameObjectSoundView( OBJECT_IDENTITY _id, soundsystem::SoundSystemFacade * _sysSound, vector3df * _currentUserPos, SimpleSoundResolvedResourcesContainer * _resourcesContainer ) : 
	id(_id), sysSound(_sysSound), currentUserPos(_currentUserPos), resourcesContainer(_resourcesContainer)
{
}


GameObjectSoundView::~GameObjectSoundView(void)
{
}

void GameObjectSoundView::iterate()
{
	if ( sounds.empty() )
		return;
	for ( std::hash_map<SS_ID, One3DSound>::iterator it = sounds.begin(); it != sounds.end(); ++it ) {
		if ( it->second.dirty || dirty ) {
			iterateForOne( it->second );
		}
	}
	dirty = false;
	
}

void GameObjectSoundView::iterateForOne( One3DSound & s )
{
	if ( s.dirty ) {
		if ( s.playing && s.stopSound ) {
			sysSound->drop( s.id );
			s.playing = false;
			s.stopSound = false;
			s.startSound = false;
		} else if ( !s.playing && s.startSound ) {
			SS_STRING * soundAddress = resourcesContainer->getAddress( s.resourceId, s.soundId );
			if ( soundAddress!=0 ) {
				soundsystem::SoundData3D sd = soundsystem::SoundData3D();
				sd.id = s.id;
				sd.address = *soundAddress;
				sd.looped = true;
				sd.maxDis = 1000;
				sd.minDis = 0;
				sd.volume = 0.5f;
				sd.track = true;
				sd.x = 0;//x;
				sd.y = 0;//y;
				sd.z = 0;//z;
				sysSound->play3D( sd );
				s.playing = true;
			} else {
				s.playing = false;
			}
			s.stopSound = false;
			s.startSound = false;
		}
		s.dirty = false;
	}
	if ( s.playing ) {
		//sysSound->update3DPosition( s.id, x, y, z );
	}
}

void GameObjectSoundView::processSoundData( SoundInformation & info )
{
	if ( info.isWithSound() ) {
		SS_STRING soundKey = "";
		soundKey.append( info.resourceId );
		soundKey.append( ":" );
		soundKey.append( info.soundId );

		std::hash_map<SS_ID, One3DSound>::iterator it = sounds.find( soundKey );
		if ( info.stop ) {
			if ( it == sounds.end() )
				return;
			it->second.stopSound = true;
			it->second.dirty = true;
			return;
		}
		if ( info.start ) {
			if ( it == sounds.end() ) {
				sounds.insert( std::pair<SS_ID, One3DSound>( soundKey, One3DSound() ) );
				it = sounds.find( soundKey );
				it->second.id = soundKey;
			} else if ( it->second.playing ) {
				return;
			}
			it->second.startSound = true;
			it->second.dirty = true;
			it->second.resourceId = info.resourceId;
			it->second.soundId = info.soundId;
			return;
		}
	} else {
		dirty = true;
		x = info.pos.x;
		y = info.pos.y;
		z = info.pos.z;
	}
}
