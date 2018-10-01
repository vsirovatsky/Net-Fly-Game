#include "StdAfx.h"
#include "SimpleClientException.h"


using namespace simpleclient;

SIMPLE_STRING & SimpleClientException::getMessage()
{
	return message;
}