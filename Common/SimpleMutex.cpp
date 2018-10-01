#include "StdAfx.h"
#include "SimpleMutex.h"

using namespace common;

SimpleMutex::SimpleMutex()
{
	Init();
}

SimpleMutex::~SimpleMutex()
{
	DeleteCriticalSection(&criticalSection);
}

void SimpleMutex::Lock(void)
{
	EnterCriticalSection(&criticalSection);
}

void SimpleMutex::Unlock(void)
{
	LeaveCriticalSection(&criticalSection);
}

void SimpleMutex::Init(void)
{
	InitializeCriticalSection(&criticalSection);
}
