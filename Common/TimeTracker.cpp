#include "stdafx.h"
#include "TimeTracker.h"
#include "SimpleTimeTracker.h"

using namespace common;

AbstractTimeTracker * TimeTracker::timeTracker = TimeTrackerFactory::createSimpleTimeTracker();

AbstractTimeTracker * TimeTrackerFactory::createSimpleTimeTracker()
{
	return new SimpleTimeTracker();
}