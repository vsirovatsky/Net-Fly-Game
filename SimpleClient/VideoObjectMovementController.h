#pragma once

#include "VideoSystemTypeDefs.h"

namespace simpleclient {

class VideoObjectMovementController
{
public:
	VideoObjectMovementController( long _timeDiffWithServer );
	~VideoObjectMovementController(void);

	void setTimeDiffWithServer( long _timeDiffWithServer ){timeDiffWithServer = _timeDiffWithServer;}

	void setCurrentTimeFromServer( long time );
	void setCurrentPosition( float x, float y, float z );
	void setNextPosition1( float x, float y, float z );
	void setNextPosition2( float x, float y, float z );
	void checkReceivedInfo();

	bool isMoving(){return moving;}
	videosystem::vector3df & getNextPos();
private:
	long prevTime;
	videosystem::vector3df posCurrent;

	bool moving;

	bool initialized;

	long timeDiffWithServer;
	long timeCurrentFromServer;
	videosystem::vector3df posCurrentFromServer;
	videosystem::vector3df posNext1FromServer;
	videosystem::vector3df posNext2FromServer;

	void initPosition( float x, float y, float z );
	void processCurrentPos( videosystem::vector3df & source, videosystem::vector3df & target, long & currentTime, long & sourceTime, long & targetTime );
};

}