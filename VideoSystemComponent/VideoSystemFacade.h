#pragma once

#include "VideoSystemException.h"
#include "VideoSystemTypeDefs.h"
#include "VideoSystemAbstractManager.h"
#include "VideoSystemFactory.h"
#include "VideoSystemTerrainControlPanel.h"
#include "VideoSystem2DControlPanel.h"
#include "IInputReceiver.h"

namespace videosystem {

class VideoSystemFacade
{
public:
	static VideoSystemFacade * INSTANCE();
	~VideoSystemFacade(void);
public:
	void startUp( VS_Context &context );
	bool isRunning();
	void render();

	IVideoObject * createVideoSimpleObject( VideoSimpleObjectCreateData data );
	IVideoObject * createVideoObject( VideoObjectCreateData data );
	IVideoAnimatedObject * createVideoAnimatedObject( VideoObjectCreateData data );
	IVideoCamera * createCamera();
	ILight * createLight();

	VideoSystemTerrainControlPanel * getTerrainControlPanel();
	VideoSystem2DControlPanel * get2DControlPanel();
	// CUSTOM, TO DE DELETED
	void custom();

	IInputReceiver * getInputReceiver();
private:
	VideoSystemFacade(void);
	static VideoSystemFacade * pInstance;
	VideoSystemAbstractManager * manager;
};

}