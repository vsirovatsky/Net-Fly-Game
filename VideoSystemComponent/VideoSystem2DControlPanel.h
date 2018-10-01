#pragma once

#include "VideoSystemTypeDefs.h"

namespace videosystem {

class VideoSystem2DControlPanel
{
public:
	VideoSystem2DControlPanel(void){}
	virtual ~VideoSystem2DControlPanel(void){}

	virtual void printText( VS_2D_ELEMENT_INDEX , VS_STRING ) = 0;
};

}