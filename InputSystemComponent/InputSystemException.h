#pragma once

#include "InputSystemTypeDefs.h"

namespace inputsystem {

class InputSystemException
{
public:
	InputSystemException(void);
	InputSystemException( IS_STRING mess );
	~InputSystemException(void);
	IS_STRING & getMessage();
	InputSystemException * addMessage( IS_STRING mess );
private:
	IS_STRING message;
};

}