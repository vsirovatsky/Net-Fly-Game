#pragma once

#include "stdafx.h"
#include "SoundSystemAbstractManager.h"
#include "SoundSystemFactory.h"

namespace soundsystem {

class SoundSystemFacade
{
public:
	static SoundSystemFacade * INSTANCE();
	~SoundSystemFacade(void);

	void stopAllSound();
	void init();

	void play2D( SoundData data );
	void play3D( SoundData3D data );
	void drop( SS_ID id );

	void update3DPosition( SS_ID, float x, float y, float z );
	void update3DMinDistance( SS_ID, float dis );
	void update3DMaxDistance( SS_ID, float dis );
	void updateVolume( SS_ID, float volume );

private:
	SoundSystemFacade(void);
	static SoundSystemFacade * pInstance;
	SoundSystemAbstractManager * manager;
};

}