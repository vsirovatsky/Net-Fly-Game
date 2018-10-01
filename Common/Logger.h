#pragma once

#include "stdafx.h"
#include "commonTypeDefs.h"
#include "TimeTracker.h"

#ifdef  NDEBUG
	#define PRINT(x)     ((void)0)
#endif
#ifdef  _DEBUG
	#define PRINT(x) common::Logger::print(x, 0)
#endif

#ifdef  NDEBUG
	#define PRINTDEBUG(x,y)     ((void)0)
#endif
#ifdef  _DEBUG
	#define PRINTDEBUG(x,y) common::Logger::print(x,y, 0)
#endif

#ifdef  NDEBUG
	#define PRINTINFO(x,y) common::Logger::print(x,y,1)
#endif
#ifdef  _DEBUG
	#define PRINTINFO(x,y) common::Logger::print(x,y,1)
#endif

#ifdef  NDEBUG
	#define PRINTWARNING(x,y) common::Logger::print(x,y,2)
#endif
#ifdef  _DEBUG
	#define PRINTWARNING(x,y) common::Logger::print(x,y,2)
#endif

#ifdef  NDEBUG
	#define PRINTERROR(x,y) common::Logger::print(x,y,3)
#endif
#ifdef  _DEBUG
	#define PRINTERROR(x,y) common::Logger::print(x,y,3)
#endif

namespace common {

class ILogable
{
public:
	ILogable(){}
	virtual ~ILogable(){}
	virtual COMMON_STRING printMe() const = 0;	
};

class AbstractLogger {
public:
	AbstractLogger(void){};
	virtual ~AbstractLogger(void){};
	virtual void print( COMMON_STRING str, int level ) = 0;
	virtual void print( COMMON_STRING str, ILogable * logableObject, int level ) = 0;
	virtual void print( COMMON_STRING str, int i, int level ) = 0;
	virtual void print( COMMON_STRING str, float f, int level ) = 0;
	virtual void print( COMMON_STRING str, double d, int level) = 0;
	virtual void print( COMMON_STRING str, bool b, int level ) = 0;
	virtual void print( COMMON_STRING str, COMMON_STRING logStr, int level ) = 0;
	virtual void print( COMMON_STRING str, unsigned char c, int level) = 0;
	virtual void setLevelDEBUG( void ) = 0;
	virtual void setLevelINFO( void ) = 0;
	virtual void setLevelWARNING( void ) = 0;
	virtual void setLevelERROR( void ) = 0;
};


class LoggerFactory 
{
public:
	static AbstractLogger * createSimpleLogger();
	static AbstractLogger * createFileLogger();
};

class Logger {
public:
	static void print( COMMON_STRING str, int level ){
		log->print( str, level );
	}
	static void print( COMMON_STRING str, ILogable * logableObject, int level ){
		log->print( str, logableObject, level );
	}
	static void print( COMMON_STRING str, int i, int level ){
		log->print( str, i, level );
	}
	static void print( COMMON_STRING str, float f, int level ){
		log->print( str, f, level );
	}
	static void print( COMMON_STRING str, double d, int level ){
		log->print( str, d, level );
	}
	static void print( COMMON_STRING str, bool b, int level ){
		log->print( str, b, level );
	}
	static void print( COMMON_STRING str, COMMON_STRING logStr, int level ){
		log->print( str, logStr, level );
	}
	static void print( COMMON_STRING str, unsigned char c, int level ){
		log->print( str, c, level );
	}
	static void setLevelDEBUG( void ){
		log->setLevelDEBUG();
	}
	static void setLevelINFO( void ){
		log->setLevelINFO();
	}
	static void setLevelWARNING( void ){
		log->setLevelWARNING();
	}
	static void setLevelERROR( void ){
		log->setLevelERROR();
	}
private:
	static AbstractLogger * log;
};


}