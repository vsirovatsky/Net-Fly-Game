#pragma once

#include "stdafx.h"
#include "commonTypeDefs.h"
#include "Logger.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "CommonException.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "SimpleMutex.h"

namespace common {
class FileLogger : public AbstractLogger
{
public:
	FileLogger(void);
	FileLogger(COMMON_STRING name);
	~FileLogger(void);
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
	std::ofstream *outputFile;
	COMMON_STRING mFileName;
	int logLevel;
	void initialize(void);
	void printLine(COMMON_STRING str);
	void setLogLevel(int level);
	SimpleMutex mut;
};
}