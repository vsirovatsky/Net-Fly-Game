#pragma once

#include "SimpleInputStateSnapshot.h"
#include "VideoSystemTypeDefs.h"

namespace simpleclient {

class IMovementProcessor
{
public:
	IMovementProcessor(void);
	~IMovementProcessor(void);

	virtual void processNextInputState( SimpleInputStateSnapshot * ) = 0;
	virtual videosystem::vector3df & getNextPosition() = 0;
};

}