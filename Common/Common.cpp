// Common.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "commonTypeDefs.h"
#include "Logger.h"
#include "ThreadWrapper.h"
#include "SimpleMutex.h"
#include <iostream>

class TestClass : public common::thread {
public:
	static common::SimpleMutex * mut;
	TestClass(int _i) : thread(), i(_i) {}
	virtual void run()
	{
		for (int c = 0; c < 100; ++c) {
			mut->Lock();
			std::cout << "Thread " << i << " is at " << c << std::endl;
			mut->Unlock();
		}
	}
private:
	int i;
};

common::SimpleMutex * TestClass::mut = new common::SimpleMutex();

int _tmain(int argc, _TCHAR* argv[])
{
	/*PRINT( "Hello" );
	TestClass test1(1);
	TestClass test2(2);

	long c1 = GetCurrentTime();
	test1.start();
	test2.start();

	while ( test1.IsThreadActive() || test2.IsThreadActive() ) {
		::Sleep(10);
	}
	long c2 = GetCurrentTime();
	std::cout << "Finished. " << (c2 - c1) << std::endl;
	std::cin.get();
	return 0;*/
	/*common::AbstractLogger * l = common::LoggerFactory::createFileLogger();
	l->print("log log",0);*/
	
	TIME_TRACKER_PROCESS_START("process", "category");
	Sleep(1000);
	TIME_TRACKER_PROCESS_STOP("process");
	TIME_TRACKER_LOGSELF();



}

