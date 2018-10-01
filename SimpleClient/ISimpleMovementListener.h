#pragma once

#include "VideoSystemTypeDefs.h"

namespace simpleclient {

class ISimpleMovementListener {
public:
	ISimpleMovementListener(){}
	virtual ~ISimpleMovementListener(){}
	virtual void notifyMovementPressed() = 0;
	virtual void notifyMovementReleased() = 0;
};

}