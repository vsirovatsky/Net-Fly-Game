#pragma once

#include "netSystemTypeDefs.h"

namespace netsystem {

class NetSystemException
{
public:
	NetSystemException(void);
	NetSystemException( NS_STRING mess );
	~NetSystemException(void);
	NS_STRING & getMessage();
private:
	NS_STRING message;
};

}