#pragma once

#include "stdafx.h"
#include "commonTypeDefs.h"
#include "SimpleTimeTracker.h"

using namespace common;
	
SimpleTimeTracker::SimpleTimeTracker(void): processes(), categoriesHash()
{
};

SimpleTimeTracker::~SimpleTimeTracker(void)
{
	for ( std::hash_map<COMMON_STRING, Process*>::iterator it = processes.begin(); it!=processes.end(); ++it) {		
		delete it->second;
		it->second = 0;
	}
};

void SimpleTimeTracker::startProcess(COMMON_STRING processId, COMMON_STRING categoryId)
{
	
	Process * p; 
	if (processes.find(processId) != processes.end())
	{
		p = processes[processId];
		p->start();
	}
	else 
	{
		p = new Process(processId, categoryId);
		p->start();
		processes.erase(processId);
		categoriesHash.erase(categoryId);
		processes.insert( std::pair<COMMON_STRING, Process*>( processId, p ) );
		categoriesHash.insert( std::pair<COMMON_STRING, COMMON_STRING>( processId, categoryId ) );
	}

};

void SimpleTimeTracker::stopProcess(COMMON_STRING processId)
{
	
	if (processes.find(processId) != processes.end())
	{		
		processes[processId]->stop();		
	}	
};

void SimpleTimeTracker::clear()
{
	for ( std::hash_map<COMMON_STRING, Process*>::iterator it = processes.begin(); it!=processes.end(); ++it) {		
		delete it->second;
		it->second = 0;
	}
	processes.clear();
	categoriesHash.clear();
};

void SimpleTimeTracker::stopAll()
{
	for ( std::hash_map<COMMON_STRING, Process*>::iterator it = processes.begin(); it!=processes.end(); ++it) {		
		delete it->second;
		it->second->stop();
	}
	processes.clear();
	categoriesHash.clear();
};

void SimpleTimeTracker::logSelf()
{
	if (processes.size() == 0)
	{
		Logger::print("No process", 0);
	}
	else
	{
		for ( std::hash_map<COMMON_STRING, Process*>::iterator it = processes.begin(); it!=processes.end(); ++it) 
		{		
			it->second->logMe();
		}
	}
};


Process::Process(COMMON_STRING prId, COMMON_STRING catId)
{	
	processId = prId;
	categoryId = catId;
	isRunning = false;
	startTime = 0;
	stopTime = 0;
	duration = 0;
};
Process::Process(COMMON_STRING prId)
{	
	processId = prId;
	categoryId = "";
	isRunning = false;
	startTime = 0;
	stopTime = 0;
	duration = 0;
};
Process::~Process(void)
{
};
void Process::start(void)
{
	if (isRunning == false)
	{
		startTime = GetCurrentTime();
		isRunning = true;
	}	
};
void Process::stop(void)
{	
	if (isRunning == true)
	{		
		stopTime = GetCurrentTime();
		duration += (stopTime - startTime);
		isRunning = false;
		startTime = 0;
		stopTime = 0;
	}

};

void Process::logMe() const
{
	COMMON_STRING result;
	std::stringstream ss;
	ss << processId << " of " << categoryId << " duration: " << duration << " ms" << " start: " << startTime << " stop: " << stopTime;		
	Logger::print(ss.str(), 0);

	
};