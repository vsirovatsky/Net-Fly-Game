#pragma once

#include "stdafx.h"
#include "commonTypeDefs.h"
#include "Logger.h"

namespace common {

class SimpleLogger : public AbstractLogger
{
public:
	SimpleLogger(void);
	~SimpleLogger(void);
	virtual void print( COMMON_STRING str, int level );
	virtual void print( COMMON_STRING str, ILogable * logableObject, int level );
	virtual void print( COMMON_STRING str, int i, int level );
	virtual void print( COMMON_STRING str, float f, int level );
	virtual void print( COMMON_STRING str, double d, int level );
	virtual void print( COMMON_STRING str, bool b, int level );
	virtual void print( COMMON_STRING str, COMMON_STRING logStr, int level );
	virtual void print( COMMON_STRING str, unsigned char c, int level);
	virtual void setLevelDEBUG( void );
	virtual void setLevelINFO( void );
	virtual void setLevelWARNING( void );
	virtual void setLevelERROR( void );

private:
	int logLevel;
	void setLogLevel(int level);
};

}