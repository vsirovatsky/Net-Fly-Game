#include "StdAfx.h"
#include "VideoSystemIrrlichtManager.h"
#include "VideoSystemIrrLichtTerrainControlPanel.h"
#include "VideoSystem2DIrrLichtControlPanel.h"
#include "VideoSystemInputReceiver.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

using namespace videosystem;


VideoSystemIrrlichtManager::VideoSystemIrrlichtManager(void)
{
	videoCamera = 0;
}


VideoSystemIrrlichtManager::~VideoSystemIrrlichtManager(void)
{
	if ( device ) {
	    device->drop();
	}
}

void VideoSystemIrrlichtManager::startUp( VS_Context &nContext )
{
	this->context = nContext;
	try {
		inputReceiver = new VideoSystemInputReceiver();
		device = createDevice( toIrrlichtDriverType(context.driverType), dimension2d<u32>(context.width, context.height), context.colorDepth, context.fullscreen, context.stencilbuffer, context.vsync, (VideoSystemInputReceiver*)inputReceiver);
	} catch (...) {
		throw VideoSystemInitializeException("Error in creating device");
	}
	try {
		driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();
		running = true;
		device->getCursorControl()->setVisible( nContext.cursorVisible );
		terrainControlPanel = new VideoSystemIrrLichtTerrainControlPanel( this, device, driver, smgr );
		m2DControlPanel = new VideoSystem2DIrrLichtControlPanel( this, device, driver, smgr );
		driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
	} catch (...) {
		throw VideoSystemInitializeException("Error in obtaining managing object from device");
	}
}

irr::video::E_DRIVER_TYPE VideoSystemIrrlichtManager::toIrrlichtDriverType( VS_DRIVER_TYPE driverType )
{
	switch ( driverType ) {
	case VS_DT_BURNINGSVIDEO: 
		return EDT_BURNINGSVIDEO;
	case VS_DT_COUNT: 
		return EDT_COUNT;
	case VS_DT_DIRECT3D8: 
		return EDT_DIRECT3D8;
	case VS_DT_DIRECT3D9: 
		return EDT_DIRECT3D9;
	case VS_DT_NULL: 
		return EDT_NULL;
	case VS_DT_OPENGL: 
		return EDT_OPENGL;
	case VS_DT_SOFTWARE: 
		return EDT_SOFTWARE;
	}
	return EDT_NULL;
}

bool VideoSystemIrrlichtManager::isRunning()
{
	if ( context.videoSystemToCaptureEvents && running ) {
		return device->run();
	} else 
		return running;
}

void VideoSystemIrrlichtManager::render()
{
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, SColor(255,0,0,0), SExposedVideoData(), 0);
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();		
	}
	else
		device->yield();
}

IVideoObject * VideoSystemIrrlichtManager::createVideoSimpleObject( VideoSimpleObjectCreateData data )
{
	if ( data.type == VS_SIMPLE_OBJECT_TYPE_SPHERE ) {
		return createVideoSphererObject( data );
	}
	throw VideoSystemNoSimpleTypeException("No convertion for ", data.type);
}

IVideoObject * VideoSystemIrrlichtManager::createVideoObject( VideoObjectCreateData data )
{
	VideoObjectIrrlicht * obj = new VideoObjectIrrlicht( data.id, this->smgr, this->driver);
	obj->create( data );
	return obj;
}

IVideoAnimatedObject * VideoSystemIrrlichtManager::createVideoAnimatedObject( VideoObjectCreateData data )
{
	VideoAnimatedObjectIrrlicht * obj = new VideoAnimatedObjectIrrlicht( data.id, this->smgr, this->driver);
	obj->create( data );
	return obj;
}

IVideoCamera * VideoSystemIrrlichtManager::createCamera()
{
	if ( videoCamera != 0 ) {
		throw VideoSystemException("Camera already exists");
	}
	videoCamera = new VideoCameraIrrlicht( this->smgr );
	videoCamera->create();
	return videoCamera;
}

VideoCameraIrrlicht * VideoSystemIrrlichtManager::getCamera(){
	if ( videoCamera == 0 ) {
		throw VideoSystemException("Camera not yet exists");
	}
	return videoCamera;
}

ILight * VideoSystemIrrlichtManager::createLight()
{
	VideoLightIrrlicht * l = new VideoLightIrrlicht( this->smgr );
	l->create();
	return l;
}

// Custom hardcoded functionality
void VideoSystemIrrlichtManager::custom()
{
	device->getFileSystem()->addZipFileArchive("media/map-20kdm2.pk3");
	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");

	if (q3levelmesh)
	{
		scene::IMeshSceneNode* q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, -1);
		q3node->setPosition(core::vector3df(-1350,-130,-1400));
	}
}

IVideoObject * VideoSystemIrrlichtManager::createVideoSphererObject( VideoSimpleObjectCreateData data )
{
	VideoSphereIrrLicht * obj = new VideoSphereIrrLicht( data.id, this->smgr, this->driver);
	obj->create( data );
	return obj;
}

VideoSystemTerrainControlPanel * VideoSystemIrrlichtManager::getTerrainControlPanel()
{
	return terrainControlPanel;
}

VideoSystem2DControlPanel * VideoSystemIrrlichtManager::get2DControlPanel()
{
	return m2DControlPanel;
}

IInputReceiver * VideoSystemIrrlichtManager::getInputReceiver()
{
	return inputReceiver;
}