#include "StdAfx.h"
#include "CommunicationsException.h"

namespace communications {

CommunicationsException::CommunicationsException(void)
{
}

CommunicationsException::CommunicationsException( PC_STRING mess ) : message( mess )
{
}

CommunicationsException::~CommunicationsException(void)
{
}

PC_STRING & CommunicationsException::getMessage()
{
	return message;
}

}