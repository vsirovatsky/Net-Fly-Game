#include "NetSystemException.h"

namespace netsystem {

NetSystemException::NetSystemException(void) : message("default")
{
}

NetSystemException::NetSystemException(NS_STRING mess) : message(mess)
{
}

NetSystemException::~NetSystemException(void)
{
}

NS_STRING & NetSystemException::getMessage()
{
	return message;
}

}