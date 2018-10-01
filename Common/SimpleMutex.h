#pragma once

#include "stdafx.h"

namespace common {

class SimpleMutex
{
public:

	SimpleMutex();
	~SimpleMutex();

	void Lock(void);
	void Unlock(void);

private:
	void Init(void);
	CRITICAL_SECTION criticalSection;
};

}
