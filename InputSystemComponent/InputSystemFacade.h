#pragma once

#include "windows.h"
#include "InputSystemTypeDefs.h"
#include "InputSystemAbstractManager.h"

namespace inputsystem {

class InputSystemFacade
{
public:
	static InputSystemFacade * INSTANCE();
	~InputSystemFacade(void);

	void init( HWND hWnd, int, int, bool showCursor, bool buffered, bool debugEnabled );
	void capture( MouseState*, KeyboardBufferedState*, KeyboardUnbufferedState* );

private:
	InputSystemFacade(void);
private:
	static InputSystemFacade * pInstance;
	InputSystemAbstractManager * pManager;
};

}