#pragma once

#include "stdafx.h"
#include "commonTypeDefs.h"
#include <hash_map>

#ifdef  NDEBUG
	#define TIME_TRACKER_PROCESS_START(x,y)     ((void)0)
#endif
#ifdef  _DEBUG
	#define TIME_TRACKER_PROCESS_START(x,y) common::TimeTracker::startProcess(x,y)
#endif

#ifdef  NDEBUG
	#define TIME_TRACKER_PROCESS_STOP(x)     ((void)0)
#endif
#ifdef  _DEBUG
	#define TIME_TRACKER_PROCESS_STOP(x) common::TimeTracker::stopProcess(x)
#endif

#ifdef  NDEBUG
	#define TIME_TRACKER_CLEAR()     ((void)0)
#endif
#ifdef  _DEBUG
	#define TIME_TRACKER_CLEAR() common::TimeTracker::clear()
#endif

#ifdef  NDEBUG
	#define TIME_TRACKER_LOGSELF()     ((void)0)
#endif
#ifdef  _DEBUG
	#define TIME_TRACKER_LOGSELF() common::TimeTracker::logSelf()
#endif

namespace common {

class AbstractTimeTracker
{
public:
	AbstractTimeTracker(void){};
	virtual ~AbstractTimeTracker(void){};
	virtual void startProcess(COMMON_STRING processId, COMMON_STRING categoryId){};
	virtual void stopProcess(COMMON_STRING processId){};
	virtual void stopAll(void){};
	virtual void clear(void){};
	virtual void logSelf(void){};
};

class TimeTrackerFactory
{
public:
	static AbstractTimeTracker * createSimpleTimeTracker(void);
};

class TimeTracker
{
public:
	static void startProcess(COMMON_STRING processId, COMMON_STRING categoryId)
	{
		timeTracker->startProcess(processId, categoryId);
	}	
	static void stopProcess(COMMON_STRING processId)
	{
		timeTracker->stopProcess(processId);
	};
	static void stopAll(void)
	{
		timeTracker->stopAll();
	};
	static void clear(void)
	{
		timeTracker->clear();
	};
	static void logSelf(void)
	{
		timeTracker->logSelf();
	};
private:
	static AbstractTimeTracker * timeTracker;
};

}