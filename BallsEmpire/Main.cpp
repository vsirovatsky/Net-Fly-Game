#include "Main.h"

Main::Main( hgeCallback ff, hgeCallback rf ) : exitRequest(false)
{
	nonlivingObjectsRegister = new NonLivingObjectsRegister();
	livingObjectsRegister = new LivingObjectsRegister();
	soundManager = new SoundManager();

	SystemStartupContext context = SystemStartupContext();
	context.logFile = "hdeLog.txt";
	context.FrameFunc = ff;
	context.RenderFunc = rf;
	context.title = "Balls Empire";
	context.windowed = true;
	context.resolutionx = 800;
	context.resolutiony = 600;
	context.colorDepth = 32;
	SystemFacade::INSTANCE()->initialize( context );

	gameWorld = new GameWorld( this );
	inputManager = new UserInputManager();
	inputManager->setSysCommandListener( this );
	inputManager->setNavigationListener( gameWorld );
}

Main::~Main()
{
	delete inputManager;
	inputManager = 0;
	delete gameWorld;
	gameWorld = 0;
	SystemFacade::INSTANCE()->finilize();
	delete soundManager;
	soundManager = 0;
	delete livingObjectsRegister;
	livingObjectsRegister = 0;
	delete nonlivingObjectsRegister;
	nonlivingObjectsRegister = 0;
}

bool Main::FrameFunc()
{
	if ( inputManager ) 
		inputManager->iterate();
	if ( livingObjectsRegister ) 
		livingObjectsRegister->iterateAll();
	if ( gameWorld ) 
		gameWorld->iterate();
	if ( exitRequest )
		return true;
	else
		return false;
}

bool Main::RenderFunc()
{
	SYSTEMCORE->Gfx_BeginScene();
	SYSTEMCORE->Gfx_Clear(0);
	if ( nonlivingObjectsRegister ) 
		nonlivingObjectsRegister->renderAll();
	if ( livingObjectsRegister ) 
		livingObjectsRegister->renderAll();
	SYSTEMCORE->Gfx_EndScene();
	return false;
}

void Main::run()
{
	SystemFacade::INSTANCE()->start();
}

void Main::notifyExit()
{
	exitRequest = true;
}