#pragma once

#include "stdafx.h"
#include "SimpleNetTypes.h"

namespace simpleclient {

class SimpleClientException
{
public:
	SimpleClientException(void){};
	SimpleClientException( SIMPLE_STRING _message ) : message(_message) {};
	virtual ~SimpleClientException(void){};
	SIMPLE_STRING & getMessage();
private:
	SIMPLE_STRING message;
};

class SimpleClientInitializationException : public SimpleClientException
{
public:
	SimpleClientInitializationException() : SimpleClientException() {}
	SimpleClientInitializationException( SIMPLE_STRING mess ) : SimpleClientException( mess ) {}
	virtual ~SimpleClientInitializationException(void){};
};

class SimpleClientNetworkException : public SimpleClientException
{
public:
	SimpleClientNetworkException() : SimpleClientException() {}
	SimpleClientNetworkException( SIMPLE_STRING mess ) : SimpleClientException( mess ) {}
	virtual ~SimpleClientNetworkException(void){};
};

class SimpleClientVideoException : public SimpleClientException
{
public:
	SimpleClientVideoException() : SimpleClientException() {}
	SimpleClientVideoException( SIMPLE_STRING mess ) : SimpleClientException( mess ) {}
	virtual ~SimpleClientVideoException(void){};
};

class SimpleClientSoundException : public SimpleClientException
{
public:
	SimpleClientSoundException() : SimpleClientException() {}
	SimpleClientSoundException( SIMPLE_STRING mess ) : SimpleClientException( mess ) {}
	virtual ~SimpleClientSoundException(void){};
};

}