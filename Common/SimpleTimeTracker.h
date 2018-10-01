#pragma once

#include "stdafx.h"
#include "commonTypeDefs.h"
#include "TimeTracker.h"
#include <time.h>
#include "Logger.h"
#include <sstream>

namespace common {

	class Process
	{
	public:
		Process(COMMON_STRING processId, COMMON_STRING categoryId);
		Process(COMMON_STRING processId);
		~Process(void);
		void start(void);
		void stop(void);
		void logMe(void) const;
	private:
		bool isRunning;
		long duration;
		COMMON_STRING processId;
		COMMON_STRING categoryId;
		long startTime;
		long stopTime;
	};

	class SimpleTimeTracker : public AbstractTimeTracker 
	{
	public:
		SimpleTimeTracker(void);
		~SimpleTimeTracker(void);
		void startProcess(COMMON_STRING processId, COMMON_STRING categoryId);
		void stopProcess(COMMON_STRING processId);
		void stopAll(void);
		void clear(void);
		void logSelf(void);
		
	private:
		std::hash_map<COMMON_STRING, Process *> processes;
		std::hash_map<COMMON_STRING, COMMON_STRING> categoriesHash;
	};

}