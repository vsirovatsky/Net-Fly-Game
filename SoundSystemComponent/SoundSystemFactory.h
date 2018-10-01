#pragma once

#include "stdafx.h"
#include "SoundSystemAbstractManager.h"
#include "SoundSystemManager.h"

namespace soundsystem {

	class SoundSystemFactory
	{
	public:
		SoundSystemFactory(void){}
		~SoundSystemFactory(void){}

		static SoundSystemAbstractManager * createSoundSystemManager(){
			return new SoundSystemManager();
		}
	};

}