#pragma once

#include "IInputReceiver.h"

namespace simpleclient {

class SimpleInputStateSnapshot
{
public:
	SimpleInputStateSnapshot( videosystem::IInputReceiver * );
	~SimpleInputStateSnapshot(void);
	bool forward;
	bool backward;
	bool left;
	bool right;
	float dirX;
	float dirY;
	float dirZ;
	long time;
	bool isUpdateTo( SimpleInputStateSnapshot & );
};

}