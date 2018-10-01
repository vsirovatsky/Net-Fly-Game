#pragma once

#include <hash_map>
#include "Logger.h"
#include "CommunicationsFacade.h"
#include "SimpleNetMessages.h"

namespace simpleclient {

class VideoSoundPlayRequester
{
public:
	VideoSoundPlayRequester( communications::AbstractPostOffice * );
	~VideoSoundPlayRequester(void);

	void updateUserPosition( float x, float y, float z );
	void updateObjectPosition( OBJECT_IDENTITY id, float x, float y, float z );

	void add( OBJECT_IDENTITY id );
	void remove( OBJECT_IDENTITY id );

	void requestSoundStart( OBJECT_IDENTITY id, std::string resourceId, std::string soundId );
	void requestSoundStop( OBJECT_IDENTITY id, std::string resourceId, std::string soundId );
private:
	communications::AbstractPostOffice * office;
	long prevUserPosSent;
	std::hash_map<OBJECT_IDENTITY, long> sendedTimes;
};

}