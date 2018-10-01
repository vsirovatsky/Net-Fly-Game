#pragma once

#include "SimpleServerTypeDefs.h"

namespace simpleserver {

class SimpleServerException
{
public:
	SimpleServerException(void){};
	SimpleServerException( SIMPLE_STRING _message ) : message(_message) {};
	virtual ~SimpleServerException(void){};
	SIMPLE_STRING & getMessage();
private:
	SIMPLE_STRING message;
};

class SimpleServerInitializationException : public SimpleServerException
{
public:
	SimpleServerInitializationException() : SimpleServerException() {}
	SimpleServerInitializationException( SIMPLE_STRING mess ) : SimpleServerException( mess ) {}
	virtual ~SimpleServerInitializationException(void){};
};

}