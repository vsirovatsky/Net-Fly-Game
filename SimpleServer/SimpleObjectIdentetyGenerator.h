#pragma once

#include "SimpleServerTypeDefs.h"
#include "SimpleNetMessages.h"

namespace netsystem {

class SimpleObjectIdentetyGenerator
{
public:
	SimpleObjectIdentetyGenerator(void);
	~SimpleObjectIdentetyGenerator(void);
	OBJECT_IDENTITY getNextOI(void);
private:
	static OBJECT_IDENTITY current;
};

}