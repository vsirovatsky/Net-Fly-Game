#pragma once

#include "SoundSystemTypeDefs.h"

namespace soundsystem {

class SoundSystemException
{
public:
	SoundSystemException(void);
	SoundSystemException( SS_STRING mess );
	~SoundSystemException(void);
	SS_STRING & getMessage();
	SoundSystemException * addMessage( SS_STRING mess );
private:
	SS_STRING message;
};

}