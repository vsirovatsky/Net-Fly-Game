#pragma once

#include "StdAfx.h"
#include "SoundSystemTypeDefs.h"

namespace soundsystem {

class SoundSystemAbstractManager
{
public:
	SoundSystemAbstractManager(void){}
	virtual ~SoundSystemAbstractManager(void){}

	virtual void stopAllSound() = 0;
	virtual void init() = 0;

	virtual void play2D( SoundData data ) = 0;
	virtual void play3D( SoundData3D data ) = 0;
	virtual void drop( SS_ID id ) = 0;

	virtual void update3DPosition( SS_ID, float x, float y, float z ) = 0;
	virtual void update3DMinDistance( SS_ID, float dis ) = 0;
	virtual void update3DMaxDistance( SS_ID, float dis ) = 0;
	virtual void updateVolume( SS_ID, float volume ) = 0;
};

}