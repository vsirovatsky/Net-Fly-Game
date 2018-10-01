#include "StdAfx.h"
#include "SimpleVideoState.h"
#include "SimpleClientException.h"
#include "Logger.h"

using namespace simpleclient;

SimpleVideoState::SimpleVideoState(void) : started(false), userObjIdentity( OBJECT_IDENTITY_NOT_FOUND )
{
}

SimpleVideoState::~SimpleVideoState(void)
{
}

void SimpleVideoState::setStarted()
{
	if ( started ) 
		throw SimpleClientVideoException("Video component already started");
	PRINT("Video component started");
	started = true;
}

void SimpleVideoState::setStoped()
{
	if ( !started ) 
		throw SimpleClientVideoException("Video component already stoped");
	PRINT("Video component stoped");
	started = false;
}

bool SimpleVideoState::isStarted()
{
	return started;
}

void SimpleVideoState::setIdentity( OBJECT_IDENTITY & _identity ){
	userObjIdentity = _identity;
}

OBJECT_IDENTITY & SimpleVideoState::getIdentity()
{
	return userObjIdentity;
}

bool SimpleVideoState::isIdentity()
{
	return ( userObjIdentity != OBJECT_IDENTITY_NOT_FOUND );
}