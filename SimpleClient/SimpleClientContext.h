#pragma once

#include "SimpleClientTypeDefs.h"
#include <iostream>

namespace simpleclient {

struct SimpleNetManagerContext 
{
	SIMPLE_INT netSleapType;
	SIMPLE_INT port;
	std::string ip;
};

struct SimpleVideoManagerContext
{
	SIMPLE_INT resolutionx;
	SIMPLE_INT resolutiony;
	bool fullscreen;
};

struct SimpleSoundManagerContext
{
	SIMPLE_FLOAT mastervolumesound;
	SIMPLE_FLOAT volumemusic;
	SIMPLE_INT soundSleapType;
};

struct SimpleClientContext 
{
	SIMPLE_INT postthreadsleeptime;
	SIMPLE_INT mainthreadsleeptime;
	SimpleNetManagerContext * mSimpleNetManagerContext;
	SimpleVideoManagerContext * mSimpleVideoManagerContext;
	SimpleSoundManagerContext * mSimpleSoundManagerContext;
};

}