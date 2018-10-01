#pragma once

#include "windows.h"
#include "InputSystemTypeDefs.h"

namespace inputsystem {

class InputSystemAbstractManager
{
public:
	InputSystemAbstractManager(void){}
	virtual ~InputSystemAbstractManager(void){}

	virtual void init( HWND hWnd, int, int, bool showCursor, bool buffered, bool debugEnabled ) = 0;
	virtual void capture( MouseState*, KeyboardBufferedState*, KeyboardUnbufferedState* ) = 0;
};

}