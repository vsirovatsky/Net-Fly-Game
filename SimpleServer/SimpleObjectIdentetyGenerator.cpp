#include "StdAfx.h"
#include "SimpleObjectIdentetyGenerator.h"

using namespace netsystem;

OBJECT_IDENTITY SimpleObjectIdentetyGenerator::current = OBJECT_IDENTITY_NOT_FOUND;

SimpleObjectIdentetyGenerator::SimpleObjectIdentetyGenerator(void)
{
}

SimpleObjectIdentetyGenerator::~SimpleObjectIdentetyGenerator(void)
{
}

OBJECT_IDENTITY SimpleObjectIdentetyGenerator::getNextOI(void)
{
	++current;
	return current;
}