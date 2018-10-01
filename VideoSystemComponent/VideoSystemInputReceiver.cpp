#include "StdAfx.h"
#include "VideoSystemInputReceiver.h"

using namespace videosystem;

VideoSystemInputReceiver::VideoSystemInputReceiver(void) : IInputReceiver(), IEventReceiver()
{
	x = 0;
	y = 0;
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}


VideoSystemInputReceiver::~VideoSystemInputReceiver(void)
{
}

bool VideoSystemInputReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
		x = event.MouseInput.X;
		y = event.MouseInput.Y;
		lMouse = event.MouseInput.isLeftPressed();
		mMouse = event.MouseInput.isMiddlePressed();
		rMouse = event.MouseInput.isRightPressed();
	}
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		//if ( event.KeyInput.Key == KEY_UP ) {
			return true;
		//}
	}
	return false;
}
