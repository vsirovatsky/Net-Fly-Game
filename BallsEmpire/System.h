#pragma once

#include "TypeDef.h"
#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgegui.h"
#include "hgeparticle.h"
#include <hash_map>

#define SYSTEM SystemFacade::INSTANCE()
#define SYSTEMCORE SystemFacade::INSTANCE()->getCore()

struct SystemStartupContext {
	hgeCallback FrameFunc;
	hgeCallback RenderFunc;
	COMMON_STRING logFile;
	COMMON_STRING title;
	BE_INT resolutionx;
	BE_INT resolutiony;
	BE_INT colorDepth;
	bool windowed;
};

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	HTEXTURE getTexture( COMMON_STRING );
	HEFFECT getEffect( COMMON_STRING );
private:
	std::hash_map<COMMON_STRING, HTEXTURE> textures;
	std::hash_map<COMMON_STRING, HEFFECT> effects;
};

class SystemFacade {
public:
	static SystemFacade * INSTANCE();
	~SystemFacade(void);

	void initialize( SystemStartupContext & );

	void start();
	void finilize();

	HTEXTURE getTexture( COMMON_STRING key ){return resourceManager->getTexture(key);}
	HEFFECT getEffect( COMMON_STRING key ){return resourceManager->getEffect(key);}

	HGE * getCore(){return hge;}
	hgeGUI * getGui(){return gui;}
	bool isInitialized(){return initialized;}
	bool isRunning(){return running;}

	void printText( float x, float y, const char * str);

	void moveScreenBy( vector2d );
private:
	SystemFacade(void);
	static SystemFacade * pInstance;
private:
	HGE * hge;
	hgeParticleManager * particleManager;
	ResourceManager * resourceManager;
	hgeFont * fnt;
	hgeGUI * gui;
	bool initialized;
	bool running;
};