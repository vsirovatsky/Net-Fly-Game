#pragma once

#include "IInputReceiver.h"
#include "VideoSystemIrrlichtManager.h"

namespace videosystem {

class VideoSystemInputReceiver : public IInputReceiver, public IEventReceiver
{
public:
	VideoSystemInputReceiver(void);
	virtual ~VideoSystemInputReceiver(void);

	virtual bool OnEvent(const SEvent& event);

	virtual bool IsKeyDown(VS_KEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	virtual int getX() const {return x;}
	virtual int getY() const {return y;}
	virtual bool getIsLMousePressed(){return lMouse;}
	virtual bool getIsMMousePressed(){return mMouse;}
	virtual bool getIsRMousePressed(){return rMouse;}
private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	int x;
	int y;
	bool lMouse;
	bool mMouse;
	bool rMouse;
};

}