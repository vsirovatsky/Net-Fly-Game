#include "StdAfx.h"
#include "VideoSystemFacade.h"

using namespace videosystem;

VideoSystemFacade * VideoSystemFacade::pInstance = 0;

VideoSystemFacade * VideoSystemFacade::INSTANCE(){
	if ( pInstance == 0 ) {
		pInstance = new VideoSystemFacade();
	}
	return pInstance;
}

VideoSystemFacade::VideoSystemFacade(void)
{
	manager = VideoSystemFactory::createVideoSystemManager();
}


VideoSystemFacade::~VideoSystemFacade(void)
{
	if ( manager ) {
		delete manager;
	}
}

void VideoSystemFacade::startUp( VS_Context &context )
{
	manager->startUp( context );
}

bool VideoSystemFacade::isRunning()
{
	return manager->isRunning();
}

void VideoSystemFacade::render()
{
	manager->render();
}

IVideoObject * VideoSystemFacade::createVideoSimpleObject( VideoSimpleObjectCreateData data )
{
	return manager->createVideoSimpleObject( data );
}

IVideoObject * VideoSystemFacade::createVideoObject( VideoObjectCreateData data )
{
	return manager->createVideoObject( data );
}

IVideoAnimatedObject * VideoSystemFacade::createVideoAnimatedObject( VideoObjectCreateData data )
{
	return manager->createVideoAnimatedObject( data );
}

IVideoCamera * VideoSystemFacade::createCamera()
{
	return manager->createCamera();
}

ILight * VideoSystemFacade::createLight()
{
	return manager->createLight();
}

VideoSystemTerrainControlPanel * VideoSystemFacade::getTerrainControlPanel()
{
	return manager->getTerrainControlPanel();
}

VideoSystem2DControlPanel * VideoSystemFacade::get2DControlPanel()
{
	return manager->get2DControlPanel();
}

IInputReceiver * VideoSystemFacade::getInputReceiver()
{
	return manager->getInputReceiver();
}

void  VideoSystemFacade::custom()
{
	manager->custom();
}
