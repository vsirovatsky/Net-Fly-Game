#include "System.h"

#pragma comment(lib, "hge.lib")
#pragma comment(lib, "hgehelp.lib")

SystemFacade * SystemFacade::pInstance = 0;

SystemFacade * SystemFacade::INSTANCE(){
	if ( pInstance == 0 ) {
		pInstance = new SystemFacade();
	}
	return pInstance;
}

SystemFacade::SystemFacade(void) : hge(0), initialized(false), running(false), resourceManager(0)
{
	resourceManager = new ResourceManager();
}

SystemFacade::~SystemFacade(void)
{
}

void SystemFacade::initialize( SystemStartupContext & context )
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, context.logFile.c_str());
	hge->System_SetState(HGE_FRAMEFUNC, context.FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, context.RenderFunc);
	hge->System_SetState(HGE_TITLE, context.title.c_str());
	//hge->System_SetState(HGE_FPS, 100);
	hge->System_SetState(HGE_WINDOWED, context.windowed);
	hge->System_SetState(HGE_SCREENWIDTH, context.resolutionx);
	hge->System_SetState(HGE_SCREENHEIGHT, context.resolutiony);
	hge->System_SetState(HGE_SCREENBPP, context.colorDepth);

	initialized = hge->System_Initiate();
	fnt=new hgeFont("mediab/font1.fnt");

	particleManager = new hgeParticleManager();

	gui = new hgeGUI();
}

void SystemFacade::start()
{
	hge->System_Start();
	running = true;
}

void SystemFacade::finilize()
{
	initialized = false;
	running = false;
	if ( resourceManager ) {
		delete resourceManager;
		resourceManager = 0;
	}
	if ( hge ) {
		delete particleManager;
		delete gui;
		gui = 0;
		hge->System_Shutdown();
		hge->Release();
		hge = 0;
	}
	//delete fnt;
}

void SystemFacade::printText( float x, float y, const char * str)
{
	fnt->Render(5, 5, HGETEXT_LEFT, str);
}

void SystemFacade::moveScreenBy( vector2d moveBy )
{
	particleManager->Transpose( moveBy.x, moveBy.y );
	particleManager->Update(1);
}



ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	if ( !textures.empty() ) {
		for ( std::hash_map<COMMON_STRING, HTEXTURE>::iterator it = textures.begin(); it!=textures.end(); ++it) {
			SYSTEMCORE->Texture_Free( it->second );
		}
	}
	if ( !effects.empty() ) {
		for ( std::hash_map<COMMON_STRING, HEFFECT>::iterator it = effects.begin(); it!=effects.end(); ++it) {
			SYSTEMCORE->Effect_Free( it->second );
		}
	}
}

HTEXTURE ResourceManager::getTexture( COMMON_STRING key )
{
	std::hash_map<COMMON_STRING, HTEXTURE>::iterator it = textures.find( key );
	if ( it != textures.end() )
		return it->second;
	HTEXTURE tex = SYSTEMCORE->Texture_Load( key.c_str() );
	textures.insert( std::pair<COMMON_STRING, HTEXTURE>(key,tex) );
	return tex;
}

HEFFECT ResourceManager::getEffect( COMMON_STRING key )
{
	std::hash_map<COMMON_STRING, HEFFECT>::iterator it = effects.find( key );
	if ( it != effects.end() )
		return it->second;
	HEFFECT snd = SYSTEMCORE->Effect_Load( key.c_str()  );
	effects.insert( std::pair<COMMON_STRING, HEFFECT>(key,snd) );
	return snd;
}


