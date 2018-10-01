#pragma once

#include "videosystemabstractmanager.h"
#include "VideoSystemException.h"
#include "VideoSystemTypeDefs.h"
#include "VideoSystemIrrlichtObjects.h"

#include <irrlicht.h>

namespace videosystem {

class VideoSystemIrrlichtManager :	public VideoSystemAbstractManager
{
public:
	VideoSystemIrrlichtManager(void);
	virtual ~VideoSystemIrrlichtManager(void);
public:
	virtual void startUp( VS_Context &context );
	virtual bool isRunning();
	virtual void render();

	virtual IVideoObject * createVideoSimpleObject( VideoSimpleObjectCreateData data );
	virtual IVideoObject * createVideoObject( VideoObjectCreateData data );
	virtual IVideoAnimatedObject * createVideoAnimatedObject( VideoObjectCreateData data );
	virtual IVideoCamera * createCamera();
	virtual ILight * createLight();

	virtual VideoSystemTerrainControlPanel * getTerrainControlPanel();
	virtual VideoSystem2DControlPanel * get2DControlPanel();

	virtual IInputReceiver * getInputReceiver();
	// CUSTOM, TO DE DELETED
	virtual void custom();

	VideoCameraIrrlicht * getCamera();

private:
	bool running;
	VS_Context context;
	irr::IrrlichtDevice * device;
	irr::video::IVideoDriver * driver;
    irr::scene::ISceneManager * smgr;
    irr::gui::IGUIEnvironment * guienv;

	VideoCameraIrrlicht * videoCamera;
	VideoSystemTerrainControlPanel * terrainControlPanel;
	VideoSystem2DControlPanel * m2DControlPanel;

	IInputReceiver * inputReceiver;
private:
	irr::video::E_DRIVER_TYPE toIrrlichtDriverType( VS_DRIVER_TYPE driverType );
	IVideoObject * createVideoSphererObject( VideoSimpleObjectCreateData data );
};

}