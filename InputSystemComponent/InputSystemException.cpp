#include "StdAfx.h"
#include "InputSystemException.h"

namespace inputsystem {

InputSystemException::InputSystemException(void) : message("default")
{
}

InputSystemException::InputSystemException(IS_STRING mess) : message(mess)
{
}

InputSystemException::~InputSystemException(void)
{
}

IS_STRING & InputSystemException::getMessage()
{
	return message;
}

InputSystemException * InputSystemException::addMessage( IS_STRING mess )
{
	message.append( mess );
	return this;
}

}