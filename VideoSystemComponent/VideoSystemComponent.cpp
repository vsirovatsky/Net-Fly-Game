// VideoSystemComponent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"
#include "VideoSystemFacade.h"
#include "VideoSystemTypeDefs.h"
#include <time.h>

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "../Debug/common.lib")
#endif
#ifdef NDEBUG
#pragma comment(lib, "../Release/common.lib")
#endif
#endif

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#define ROCKETLAUNCHER_POSITION_OFFSET vector3df( -1.5f, 3.5f, -2.5f )
#define ROCKETLAUNCHER_ROTATION_OFFSET vector3df( 0.0f, -90.0f, -4.0f )


using namespace videosystem;

int _tmain(int argc, _TCHAR* argv[])
{
	VS_Context context = VS_Context( VS_DT_OPENGL, 1280, 1024 );
	context.cursorVisible = false;
	context.videoSystemToCaptureEvents = true;
	context.fullscreen = true;
	VideoSystemFacade * f = VideoSystemFacade::INSTANCE();
	f->startUp( context );
	// TODO: HARDCODED
	//f->custom();
	IVideoCamera * camera = f->createCamera();
	camera->setPosition(vector3df(50,50,60));
	camera->setTarget(vector3df(-70,30,-60));

	VideoSimpleObjectCreateData sd = VideoSimpleObjectCreateData();
	sd.id = 1;
	sd.polynum = 32;
	sd.radius = 20.0f;
	sd.type = VS_SIMPLE_OBJECT_TYPE_SPHERE;
	sd.isTextured = true;
	sd.textureFile = VS_STRING( "media/wall.bmp" );

	IVideoObject * sphere1 = f->createVideoSimpleObject( sd );
	sphere1->setPosition( vector3df( -50, -50, -50) );

	IVideoObject * sphere2 = f->createVideoSimpleObject( sd );
	sphere2->setPosition( vector3df( 50, -50, -50) );

	IVideoObject * sphere3 = f->createVideoSimpleObject( sd );
	sphere3->setPosition( vector3df( -50, 50, -50) );

	IVideoObject * sphere4 = f->createVideoSimpleObject( sd );
	sphere4->setPosition( vector3df( -50, -50, 50) );
	sphere4->setScale( vector3df( 5, 5, 5 ) );

	IVideoObject * sphere5 = f->createVideoSimpleObject( sd );
	sphere5->setPosition( vector3df( -50, 50, 50) );

	IVideoObject * sphere6 = f->createVideoSimpleObject( sd );
	sphere6->setPosition( vector3df( 50, -50, 50) );

	IVideoObject * sphere7 = f->createVideoSimpleObject( sd );
	sphere7->setPosition( vector3df( 50, 50, -50) );

	IVideoObject * sphere8 = f->createVideoSimpleObject( sd );
	sphere8->setPosition( vector3df( 50, 50, 50) );

	TerrainCreateData terrainData = TerrainCreateData(1, -500.0f, -500.0f, -70.0f, 40.f, 4.4f, 40.f);
	terrainData.terrainHeightmapFile = new VS_STRING( "media/terrain-heightmap.bmp" );
	terrainData.terrainFirstTextureFile = new VS_STRING( "media/terrain-texture.jpg" );
	terrainData.terrainSecondTextureFile = new VS_STRING( "media/detailmap3.jpg" );
	terrainData.firstTerrainScale = 1.0f;
	terrainData.secondTerrainScale = 20.0f;
	//f->getTerrainControlPanel()->createTerrainNode( terrainData );
	//f->getTerrainControlPanel()->addTerrainNodeToCollision( 1, vector3df(50,50,50) );

	SkyCreateData skyData = SkyCreateData( true );
	skyData.skyBox_Up = new VS_STRING( "media/up.jpg" );
	skyData.skyBox_Down = new VS_STRING( "media/dn.jpg" );
	skyData.skyBox_Left = new VS_STRING( "media/lt.jpg" );
	skyData.skyBox_Right = new VS_STRING( "media/rt.jpg" );
	skyData.skyBox_Forward = new VS_STRING( "media/ft.jpg" );
	skyData.skyBox_Back = new VS_STRING( "media/bk.jpg" );
	/*skyData.skyBox_Up = new VS_STRING( "media/irrlicht2_up.jpg" );
	skyData.skyBox_Down = new VS_STRING( "media/irrlicht2_dn.jpg" );
	skyData.skyBox_Left = new VS_STRING( "media/irrlicht2_lf.jpg" );
	skyData.skyBox_Right = new VS_STRING( "media/irrlicht2_rt.jpg" );
	skyData.skyBox_Forward = new VS_STRING( "media/irrlicht2_ft.jpg" );
	skyData.skyBox_Back = new VS_STRING( "media/irrlicht2_bk.jpg" );*/
	skyData.skyDom = new VS_STRING( "media/pan_luna_lg.jpg" );
	f->getTerrainControlPanel()->createSky( skyData );

	//VideoObjectCreateData d = VideoObjectCreateData();
	//d.id = 1;
	//d.file = VS_STRING( "media/dwarf.x" );
	//d.file = VS_STRING( "media/ninja.b3d" );
	//d.isTextured = false;
	//d.isMaterialized = true;
	//IVideoAnimatedObject * v = f->createVideoAnimatedObject( d );
	//v->setAnimationSpead( 10.0f );
	//v->setScale( vector3df(10,10,10) );
	//v->setPosition( vector3df(-70,-66,-60) );
	//v->setRotation( vector3df(0,90,0) );
	//v->setAnimationPosition(0,100);

	//VideoObjectCreateData d1 = VideoObjectCreateData();

	//d1.id = 2;
	//d1.file =  VS_STRING( "media/ak47.3DS" );
	//IVideoObject * ak = f->createVideoObject( d1 );
	//ak->setScale( vector3df(10,10,10) );
	//ak->setPosition( vector3df(0,0,0)  );
	//ak->setRotation( vector3df(0,0,0)  );

	
	//v->setPosition( ROCKETLAUNCHER_POSITION_OFFSET );
	//v->setRotation( ROCKETLAUNCHER_ROTATION_OFFSET );
	//((VideoObjectIrrlicht*)v)->getNode()->setParent( ((VideoCameraIrrlicht*)camera)->getCameraNode() );
	//((VideoObjectIrrlicht*)ak)->getNode()->setMaterialFlag( irr::video::EMF_LIGHTING, false );

	ILight * l = f->createLight();
	l->setColor( color4d(1.0f, 1.0f, 1.0f, 1.0f) );
	l->setRadius( 600.0f );
	l->setPosition( vector3df(-60,100,400) );

	

	//gui::IGUIStaticText* diagnostics = f->getGUIEnvironment()->addStaticText(
	//	L"", core::rect<s32>(10, 10, 400, 20));
	//diagnostics->setOverrideColor(video::SColor(255, 255, 255, 0));
	//f->get2DControlPanel()->addText( "" );
	const f32 MOVEMENT_SPEED = 750.f;
	
	long then = GetCurrentTime();

	
	//time_t mytime = time(0);
	while ( f->isRunning() ) {

		long now = GetCurrentTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		videosystem::vector3df camPosition = camera->getPosition();
		videosystem::vector3df camRotation = camera->getRotaition();

		/*time_t mytime2 = time( 0 );
		if ( ((mytime2 - mytime) > 1) && v ) {
			delete v;
			v = 0;
		}*/

		VS_STRING str("");
		if ( f->getInputReceiver()->IsKeyDown( VS_KEY_CODE::KEY_LEFT ) ) {
			str.append( " [LEFT] " );
		}
		if ( f->getInputReceiver()->IsKeyDown( VS_KEY_CODE::KEY_UP ) || f->getInputReceiver()->IsKeyDown( VS_KEY_CODE::KEY_KEY_W ) ) {
			str.append( " [UP] " );
			camPosition.x += MOVEMENT_SPEED * frameDeltaTime * camRotation.x;
			camPosition.y += MOVEMENT_SPEED * frameDeltaTime * camRotation.y;
			camPosition.z += MOVEMENT_SPEED * frameDeltaTime * camRotation.z;
		}
		if ( f->getInputReceiver()->IsKeyDown( VS_KEY_CODE::KEY_RIGHT ) ) {
			str.append( " [RIGHT] " );
		}
		if ( f->getInputReceiver()->IsKeyDown( VS_KEY_CODE::KEY_DOWN ) ) {
			str.append( " [DOWN] " );
		}
		if ( f->getInputReceiver()->getIsLMousePressed() ) {
			str.append( " [MOUSE] " );
		}
		
		camera->setPosition( camPosition );

		std::stringstream ss;
		ss << "rotation: " << "(" << camRotation.x << "," << camRotation.y << "," << camRotation.z << ")";
		//ss << "x:" << f->getInputReceiver()->getX();
		//ss << " y:" << f->getInputReceiver()->getY();
		//str.append( ss.str() );
		f->get2DControlPanel()->printText( 1, str );
		f->get2DControlPanel()->printText( 2, ss.str() );

		f->render();
		/*vector3df camPos = camera->getPosition();
		vector3df camRot = camera->getRotaition();
		camPos.y -= 20;
		ak->setPosition( camPos );
		ak->setRotation( camRot );*/
	}
	//delete v;
	//delete ak;
	char ch;
	std::cin >> ch;
	return 0;
}

