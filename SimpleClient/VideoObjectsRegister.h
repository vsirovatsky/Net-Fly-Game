#pragma once

#include <hash_map>
#include "SimpleNetMessages.h"
#include "VideoSystemTypeDefs.h"
#include "VideoObjectMovementController.h"
#include "VideoSoundPlayRequester.h"

namespace simpleclient {

class VideoObjectsRegister
{
public:
	VideoObjectsRegister( VideoSoundPlayRequester * );
	~VideoObjectsRegister(void);

	void setTimeDiffWithServer( long _timeDiffWithServer ){timeDiffWithServer = _timeDiffWithServer;}

	videosystem::IVideoObject * get( OBJECT_IDENTITY );
	VideoObjectMovementController * getMovementController( OBJECT_IDENTITY );
	void store( OBJECT_IDENTITY, videosystem::IVideoObject * );
	void remove( OBJECT_IDENTITY );
	void updateUbjectsPositions();
private:
	long timeDiffWithServer;
	std::hash_map<OBJECT_IDENTITY, videosystem::IVideoObject *> regObjects;
	std::hash_map<OBJECT_IDENTITY, VideoObjectMovementController *> regControllers;
	VideoSoundPlayRequester * soundPlayRequester;
};

}