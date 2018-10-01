#pragma once

#include "communicationsTypeDefs.h"
#include "stdafx.h"

namespace communications {

class CommunicationsException
{
public:
	CommunicationsException(void);
	CommunicationsException( PC_STRING mess );
	virtual ~CommunicationsException(void);
	PC_STRING & getMessage();
private:
	PC_STRING message;
};

}