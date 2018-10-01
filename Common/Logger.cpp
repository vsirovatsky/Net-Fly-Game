#include "stdafx.h"
#include "Logger.h"
#include "SimpleLogger.h"
#include "FileLogger.h"

namespace common {

AbstractLogger * Logger::log = LoggerFactory::createFileLogger();

AbstractLogger * LoggerFactory::createSimpleLogger()
{
	return new SimpleLogger();
}

AbstractLogger * LoggerFactory::createFileLogger()
{
	return new FileLogger();
}

}