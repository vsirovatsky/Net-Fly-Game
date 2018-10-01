#include "StdAfx.h"
#include "VideoSoundPlayRequester.h"
#include "SimpleSoundMessage.h"

using namespace simpleclient;

#define USER_POS_SENDING_INTERVAL 50
#define OBJECT_POS_SENDING_INTERVAL 50

VideoSoundPlayRequester::VideoSoundPlayRequester(communications::AbstractPostOffice * _office) : office(_office), prevUserPosSent(0)
{
}


VideoSoundPlayRequester::~VideoSoundPlayRequester(void)
{
}

void VideoSoundPlayRequester::updateUserPosition( float x, float y, float z )
{
	long newTime = GetCurrentTime();
	if ( newTime < (prevUserPosSent + USER_POS_SENDING_INTERVAL) )
		return;
	prevUserPosSent = newTime;
	InnerSoundUserPosition * uPos = new InnerSoundUserPosition();
	uPos->pos.x = x;
	uPos->pos.y = y;
	uPos->pos.z = z;
	office->send( uPos, communications::SOUND_COMPONENT_ID );
}

void VideoSoundPlayRequester::updateObjectPosition( OBJECT_IDENTITY id, float x, float y, float z )
{
	long newTime = GetCurrentTime();
	std::hash_map<OBJECT_IDENTITY, long>::iterator it = sendedTimes.find( id );
	if ( it == sendedTimes.end() ) {
		sendedTimes.insert( std::pair<OBJECT_IDENTITY, long>(id, newTime) );
	} else {
		if ( newTime < (it->second + OBJECT_POS_SENDING_INTERVAL) ) 
			return;
		sendedTimes.erase( id );
		sendedTimes.insert( std::pair<OBJECT_IDENTITY, long>(id, newTime) );
	}
	InnerSoundObjectInfo * mes = new InnerSoundObjectInfo();
	mes->info.objId = id;
	mes->info.pos.x = x;
	mes->info.pos.y = y;
	mes->info.pos.z = z;
	office->send( mes, communications::SOUND_COMPONENT_ID );
}

void VideoSoundPlayRequester::remove( OBJECT_IDENTITY id ){
	InnerSoundObjectInfo * mes = new InnerSoundObjectInfo();
	mes->info.objId = id;
	mes->info.remove = true;
	office->send( mes, communications::SOUND_COMPONENT_ID );
}

void VideoSoundPlayRequester::add( OBJECT_IDENTITY id ){
	InnerSoundObjectInfo * mes = new InnerSoundObjectInfo();
	mes->info.objId = id;
	mes->info.create = true;
	office->send( mes, communications::SOUND_COMPONENT_ID );
}

void VideoSoundPlayRequester::requestSoundStart( OBJECT_IDENTITY id, std::string resourceId, std::string soundId )
{
	InnerSoundObjectInfo * mes = new InnerSoundObjectInfo();
	mes->info.objId = id;
	mes->info.start = true;
	mes->resourceId = resourceId;
	mes->info.resourceId = resourceId;
	mes->soundId = soundId;
	mes->info.soundId = soundId;
	office->send( mes, communications::SOUND_COMPONENT_ID );
}

void VideoSoundPlayRequester::requestSoundStop( OBJECT_IDENTITY id, std::string resourceId, std::string soundId )
{
	InnerSoundObjectInfo * mes = new InnerSoundObjectInfo();
	mes->info.objId = id;
	mes->info.stop = true;
	mes->resourceId = resourceId;
	mes->info.resourceId = resourceId;
	mes->soundId = soundId;
	mes->info.soundId = soundId;
	office->send( mes, communications::SOUND_COMPONENT_ID );	
}
