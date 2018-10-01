#pragma once

#include "VideoSystemIrrlichtManager.h"
#include "VideoSystemAbstractManager.h"

namespace videosystem {

class VideoSystemFactory
{
public:
	~VideoSystemFactory(void){}
	static VideoSystemAbstractManager * createVideoSystemManager(){
		return new VideoSystemIrrlichtManager();
	}
private:
	VideoSystemFactory(void){}
};

}
