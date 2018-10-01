#include "StdAfx.h"
#include "SimpleLogger.h"

namespace common {

SimpleLogger::SimpleLogger(void)
{
	setLogLevel(0);
}


SimpleLogger::~SimpleLogger(void)
{
}

void SimpleLogger::print( COMMON_STRING str, int level )
{
	if (logLevel <= level)
		std::cout << str.c_str() << std::endl;
}

void SimpleLogger::print( COMMON_STRING str, ILogable * logableObject, int level )
{
	if (logLevel <= level)
	std::cout << str.c_str() << logableObject->printMe().c_str() << std::endl;
}

void SimpleLogger::print( COMMON_STRING str, int i, int level )
{	
	if (logLevel <= level)
	std::cout << str.c_str() << " " << i << std::endl;	
}

void SimpleLogger::print( COMMON_STRING str, float f, int level )
{
	if (logLevel <= level)
	std::cout << str.c_str() << " " << f << std::endl;	
}

void SimpleLogger::print( COMMON_STRING str, double d, int level )
{
	if (logLevel <= level)
	std::cout << str.c_str() << " " << d << std::endl;	
}

void SimpleLogger::print( COMMON_STRING str, bool b, int level )
{
	if (logLevel <= level)
	std::cout << str.c_str() << " " << b << std::endl;	
}

void SimpleLogger::print( COMMON_STRING str, COMMON_STRING logStr, int level )
{	
	if (logLevel <= level)
	std::cout << str.c_str() << " " << logStr.c_str() << std::endl;	
}

void SimpleLogger::print( COMMON_STRING str, unsigned char c, int level )
{
	if (logLevel <= level)
	std::cout << str.c_str() << " " << c << std::endl;	
}

void SimpleLogger::setLevelDEBUG( void )
{
	setLogLevel(0);
}
void SimpleLogger::setLevelINFO( void )
{
	setLogLevel(1);
}
void SimpleLogger::setLevelWARNING( void )
{
	setLogLevel(2);
}
void SimpleLogger::setLevelERROR( void )
{
	setLogLevel(3);
}

void SimpleLogger::setLogLevel(int level)
{
	logLevel = level;
}


}