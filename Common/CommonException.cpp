#include "StdAfx.h"
#include "CommonException.h"
#include "stdafx.h"

namespace common {

CommonException::CommonException(void) : message( "default error" )
{
}

CommonException::CommonException( COMMON_STRING mess ) : message( mess )
{
}

CommonException::CommonException( COMMON_STRING fileName, COMMON_STRING mess ) : message( "File [" )
{
	message.append( fileName );
	message.append( "]. " );
	message.append( mess );
}

CommonException::~CommonException(void)
{
}

COMMON_STRING & CommonException::getMessage()
{
	return message;
}

}