#pragma once

#include "VideoSystemException.h"
#include "VideoSystemTypeDefs.h"
#include "VideoSystemTerrainControlPanel.h"
#include "VideoSystem2DControlPanel.h"
#include "IInputReceiver.h"

namespace videosystem {

class VideoSystemAbstractManager
{
public:
	VideoSystemAbstractManager(void){}
	virtual ~VideoSystemAbstractManager(void){}
	virtual void startUp( VS_Context &context ) = 0;
	virtual bool isRunning() = 0;
	virtual void render() = 0;

	virtual IVideoObject * createVideoSimpleObject( VideoSimpleObjectCreateData data ) = 0;
	virtual IVideoObject * createVideoObject( VideoObjectCreateData data ) = 0;
	virtual IVideoAnimatedObject * createVideoAnimatedObject( VideoObjectCreateData data ) = 0;
	virtual IVideoCamera * createCamera() = 0;
	virtual ILight * createLight() = 0;

	virtual VideoSystemTerrainControlPanel * getTerrainControlPanel() = 0;
	virtual VideoSystem2DControlPanel * get2DControlPanel() = 0;

	virtual IInputReceiver * getInputReceiver() = 0;
	// CUSTOM, TO DE DELETED
	virtual void custom() = 0;

};

}