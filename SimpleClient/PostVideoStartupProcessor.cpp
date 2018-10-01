#include "StdAfx.h"
#include "PostVideoStartupProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"
#include "VideoSystemTypeDefs.h"

using namespace simpleclient;

PostVideoStartupProcessor::PostVideoStartupProcessor( ISimpleVideoManagerPanel * _panel ) : panel(_panel)
{
}

PostVideoStartupProcessor::~PostVideoStartupProcessor(void)
{
}

void PostVideoStartupProcessor::process( communications::Envelope * en )
{
	PRINTDEBUG("PostVideoStartupProcessor received: ", en);
	InnerObjectStartUpVideoMessage * startUp = (InnerObjectStartUpVideoMessage *)(en->message);
	panel->getState()->setIdentity( startUp->objectIdentity );
	panel->getVideoSoundPlayRequester()->add( startUp->objectIdentity );
	panel->initialize();
	initTerrain();
	initSky();
	initLight();
	panel->getObjectsRegister().setTimeDiffWithServer( startUp->timeDiffWithServer );
	panel->getCameraMovementController()->setTimeDiffWithServer( startUp->timeDiffWithServer );
	panel->getCameraMovementController()->setCurrentPosition( startUp->x,startUp->y,startUp->z );
	panel->getCameraMovementController()->setNextPosition1( startUp->x,startUp->y,startUp->z );
	panel->getCameraMovementController()->setNextPosition2( startUp->x,startUp->y,startUp->z );
	panel->getCameraMovementController()->checkReceivedInfo();
	panel->getCamera()->setPosition(videosystem::vector3df(startUp->x,startUp->y,startUp->z));
	panel->getCamera()->setTarget(videosystem::vector3df(-70,30,-60));
	panel->getState()->setStarted();
}

void PostVideoStartupProcessor::initTerrain()
{
	videosystem::TerrainCreateData terrainData = videosystem::TerrainCreateData(1, -500.0f, -500.0f, -70.0f, 40.f, 4.4f, 40.f);
	terrainData.terrainHeightmapFile = new VS_STRING( "media/terrain-heightmap.bmp" );
	terrainData.terrainFirstTextureFile = new VS_STRING( "media/terrain-texture.jpg" );
	terrainData.terrainSecondTextureFile = new VS_STRING( "media/detailmap3.jpg" );
	terrainData.firstTerrainScale = 1.0f;
	terrainData.secondTerrainScale = 20.0f;
	panel->getVideoSystem()->getTerrainControlPanel()->createTerrainNode( terrainData );
	//panel->getVideoSystem()->getTerrainControlPanel()->addTerrainNodeToCollision( 1, videosystem::vector3df(50,50,50) );
}

void PostVideoStartupProcessor::initSky()
{
	videosystem::SkyCreateData skyData = videosystem::SkyCreateData( true );
	skyData.skyBox_Up = new VS_STRING( "media/up.jpg" );
	skyData.skyBox_Down = new VS_STRING( "media/dn.jpg" );
	skyData.skyBox_Left = new VS_STRING( "media/lt.jpg" );
	skyData.skyBox_Right = new VS_STRING( "media/rt.jpg" );
	skyData.skyBox_Forward = new VS_STRING( "media/ft.jpg" );
	skyData.skyBox_Back = new VS_STRING( "media/bk.jpg" );
	skyData.skyDom = new VS_STRING( "media/skydome2.jpg" );
	panel->getVideoSystem()->getTerrainControlPanel()->createSky( skyData );
}

void PostVideoStartupProcessor::initLight()
{
	videosystem::ILight * l = panel->getVideoSystem()->createLight();
	l->setColor( videosystem::color4d(1.0f, 1.0f, 1.0f, 1.0f) );
	l->setRadius( 600.0f );
	l->setPosition( videosystem::vector3df(-60,100,400) );
}

PC_MESSAGE_TYPE PostVideoStartupProcessor::getType()
{
	return MESSAGE_TYPE_STARTUP_VIDEO;
}