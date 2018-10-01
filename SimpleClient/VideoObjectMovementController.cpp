#include "StdAfx.h"
#include "VideoObjectMovementController.h"
#include "Logger.h"

using namespace simpleclient;

#define TIME_STEP_IN_MOVEMENT 500
#define ACCURACY_IN_MOVEMENT 0.005f

VideoObjectMovementController::VideoObjectMovementController( long _timeDiffWithServer ) : timeDiffWithServer(_timeDiffWithServer), timeCurrentFromServer(0), initialized(false), moving(false)
{
}

VideoObjectMovementController::~VideoObjectMovementController(void)
{
}

void VideoObjectMovementController::setCurrentTimeFromServer( long time )
{
	timeCurrentFromServer = time;
}

void VideoObjectMovementController::initPosition( float x, float y, float z )
{
	posCurrent.x = x;
	posCurrent.y = y;
	posCurrent.z = z;
}

void VideoObjectMovementController::setCurrentPosition( float x, float y, float z )
{
	posCurrentFromServer.x = x;
	posCurrentFromServer.y = y;
	posCurrentFromServer.z = z;
	if ( !initialized ) {
		initPosition( x, y, x );
		moving = true;
		initialized = true;
	}
}

void VideoObjectMovementController::setNextPosition1( float x, float y, float z )
{
	posNext1FromServer.x = x;
	posNext1FromServer.y = y;
	posNext1FromServer.z = z;
}

void VideoObjectMovementController::setNextPosition2( float x, float y, float z )
{
	posNext2FromServer.x = x;
	posNext2FromServer.y = y;
	posNext2FromServer.z = z;
}

void VideoObjectMovementController::checkReceivedInfo()
{
	if ( (posCurrentFromServer.x!=posNext1FromServer.x) || (posCurrentFromServer.x!=posNext2FromServer.x) ) {
		moving = true;
		return;
	}
	if ( (posCurrentFromServer.y!=posNext1FromServer.y) || (posCurrentFromServer.y!=posNext2FromServer.y) ) {
		moving = true;
		return;
	}
	if ( (posCurrentFromServer.z!=posNext1FromServer.z) || (posCurrentFromServer.z!=posNext2FromServer.z) ) {
		moving = true;
		return;
	}
}

videosystem::vector3df & VideoObjectMovementController::getNextPos()
{
	//return posNext2FromServer;
	long newTime = GetCurrentTime();
	if ( !moving )
		return posCurrent;
	long time0 = timeCurrentFromServer + timeDiffWithServer;
	long time1 = time0 + TIME_STEP_IN_MOVEMENT;
	long time2 = time1 + TIME_STEP_IN_MOVEMENT;

	if ( newTime > time2 ) {
		posCurrent.x = posNext2FromServer.x;
		posCurrent.y = posNext2FromServer.y;
		posCurrent.z = posNext2FromServer.z;
		moving = false;
	} else if ( newTime > time1 ) {
		processCurrentPos( posNext1FromServer, posNext2FromServer, newTime, time1, time2 );
	} else {
		processCurrentPos( posCurrentFromServer, posNext1FromServer, newTime, time0, time1 );
	}
	prevTime = newTime;
	return posCurrent;
}

void VideoObjectMovementController::processCurrentPos( videosystem::vector3df & source, videosystem::vector3df & target, long & currentTime, long & sourceTime, long & targetTime )
{
	float timeStep = currentTime - sourceTime;
	float timeBaseStep = targetTime - sourceTime;
	float timeRatio = timeStep / timeBaseStep;

	posCurrent.x = source.x + (target.x - source.x) * timeRatio;
	posCurrent.y = source.y + (target.y - source.y) * timeRatio;
	posCurrent.z = source.z + (target.z - source.z) * timeRatio;
}