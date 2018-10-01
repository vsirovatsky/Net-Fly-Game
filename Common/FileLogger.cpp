#include "StdAfx.h"
#include "FileLogger.h"

namespace common {

FileLogger::FileLogger(void)
{
	this->mFileName = "Logs.txt";
	initialize();
}

FileLogger::FileLogger(COMMON_STRING name)
{
	this->mFileName = name;
	initialize();
}


FileLogger::~FileLogger(void)
{
	this->outputFile->close();
	delete this->outputFile;
	this->outputFile = 0;
}

void FileLogger::print( COMMON_STRING str, int level )
{
	if (logLevel <= level)
	printLine(str);
}

void FileLogger::print( COMMON_STRING str, ILogable * logableObject, int level )
{
	if (logLevel <= level)		
		printLine( (str + logableObject->printMe()) );	
}

void FileLogger::print( COMMON_STRING str, int i, int level )
{	
	if (logLevel <= level)
	{
		std::stringstream ss;
		ss << " " << i;
		printLine( (str + ss.str()) );
	}
}

void FileLogger::print( COMMON_STRING str, float f, int level )
{
	if (logLevel <= level)
	{
		std::stringstream ss;
		ss << " " << f;
		printLine( (str + ss.str()) );
	}

}

void FileLogger::print( COMMON_STRING str, double d, int level )
{
	if (logLevel <= level)
	{
		std::stringstream ss;
		ss << " " << d;
		printLine( (str + ss.str()) );
	}
}

void FileLogger::print( COMMON_STRING str, bool b, int level )
{
	if (logLevel <= level)
	{
		std::stringstream ss;
		ss << " " << b;
		printLine( (str + ss.str()) );
	}
}

void FileLogger::print( COMMON_STRING str, COMMON_STRING logStr, int level )
{	
	if (logLevel <= level)
	printLine( (str + " " + logStr) );
}

void FileLogger::print( COMMON_STRING str, unsigned char c, int level )
{
	if (logLevel <= level)
	{
		std::stringstream ss;
		ss << " " << c;
		printLine( (str + ss.str()) );
	}
}	

void FileLogger::printLine( COMMON_STRING str )
{	
	time_t t;	
	struct tm parts;
	struct tm *p;

	time(&t);
	p = localtime(&t);
	if (p != NULL)
        parts = *p;

	try	{
		COMMON_STRING str_time = asctime(&parts);		
		int size = str_time.size();
		str_time[size-1] = ':';
		mut.Lock();
		*outputFile << str_time.c_str()<< ' ' << str.c_str() << std::endl;
		mut.Unlock();
	} catch (CommonException ex) {
		mut.Unlock();
		throw ex;
	} catch (...) {
		mut.Unlock();
		throw CommonException( mFileName, "Can't write in log file" );
	}
}

void FileLogger::initialize()
{	
	setLogLevel(0);
	try {
		outputFile = new std::ofstream(mFileName, std::ios_base::out | std::ios_base::app);			
		printLine(" [NEW INSTANCE]");
	} catch (CommonException ex) {
		throw ex;
	} catch (...) {
		throw CommonException( mFileName, "Can't create log file" );
	}
}

void FileLogger::setLevelDEBUG( void )
{
	setLogLevel(0);
}
void FileLogger::setLevelINFO( void )
{
	setLogLevel(1);
}
void FileLogger::setLevelWARNING( void )
{
	setLogLevel(2);
}
void FileLogger::setLevelERROR( void )
{
	setLogLevel(3);
}

void FileLogger::setLogLevel(int level)
{
	logLevel = level;
}

}