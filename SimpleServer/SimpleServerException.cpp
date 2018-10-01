#include "stdafx.h"
#include "SimpleServerException.h"


using namespace simpleserver;

SIMPLE_STRING & SimpleServerException::getMessage()
{
	return message;
}