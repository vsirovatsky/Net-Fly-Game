#pragma once

#include "stdafx.h"
#include "SoundSystemAbstractManager.h"
#include "SoundSystemException.h"
#include "SoundSystemTypeDefs.h"
#include <stdio.h>
#include "irrKlang.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <hash_map>

#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

namespace soundsystem {

class SoundSystemManager : public SoundSystemAbstractManager
{
public:
	SoundSystemManager(void);
	virtual ~SoundSystemManager(void);

	virtual void stopAllSound();
	virtual void init();

	virtual void play2D( SoundData data );
	virtual void play3D( SoundData3D data );
	virtual void drop( SS_ID id );

	virtual void update3DPosition( SS_ID, float x, float y, float z );
	virtual void update3DMinDistance( SS_ID, float dis );
	virtual void update3DMaxDistance( SS_ID, float dis );
	virtual void updateVolume( SS_ID, float volume );

private:
	ISoundEngine * engine;
	std::hash_map<SS_ID, ISound*> sounds;

	ISound* getById( SS_ID );
	void validateNotExisted( SS_ID );
};

}