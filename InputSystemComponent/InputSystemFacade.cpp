#include "StdAfx.h"
#include "InputSystemFacade.h"
#include "InputSystemFactory.h"

#pragma comment(lib, "OIS_static_d.lib")

namespace inputsystem {

InputSystemFacade * InputSystemFacade::pInstance = 0;

InputSystemFacade * InputSystemFacade::INSTANCE()
{
	if ( pInstance == 0 ) {
		pInstance = new InputSystemFacade();
	}
	return pInstance;
}

InputSystemFacade::InputSystemFacade(void)
{
	pManager = InputSystemFactory::createInputSystemManager();
}


InputSystemFacade::~InputSystemFacade(void)
{
	if ( pManager ) {
		delete pManager;
	}
}

void InputSystemFacade::init( HWND hWnd, int sizeX, int sizeY, bool showCursor, bool buffered, bool debugEnabled )
{
	pManager->init(hWnd, sizeX, sizeY, showCursor, buffered, debugEnabled);
}

void InputSystemFacade::capture( MouseState * mouseState, KeyboardBufferedState * kbs, KeyboardUnbufferedState * kus )
{
	pManager->capture( mouseState, kbs, kus ) ;
}

}