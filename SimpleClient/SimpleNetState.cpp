#include "StdAfx.h"
#include "SimpleNetState.h"
#include "SimpleClientException.h"

using namespace simpleclient;

SimpleNetState::SimpleNetState(void) : ISimpleNetState(), connected(false), userObjIdentity( OBJECT_IDENTITY_NOT_FOUND )
{
}

SimpleNetState::~SimpleNetState(void)
{
}

void SimpleNetState::setConnected()
{
	if ( connected ) 
		throw SimpleClientNetworkException("Client already connected");
	PRINT("connected");
	connected = true;
}

void SimpleNetState::setDisconnected()
{
	if ( !connected ) 
		throw SimpleClientNetworkException("Client already disconnected");
	PRINT("disconnected");
	connected = false;
}

bool SimpleNetState::isConnected()
{
	return connected;
}

void SimpleNetState::setIdentity( OBJECT_IDENTITY & _identity ){
	userObjIdentity = _identity;
}

OBJECT_IDENTITY & SimpleNetState::getIdentity()
{
	return userObjIdentity;
}

bool SimpleNetState::isIdentity()
{
	return ( userObjIdentity != OBJECT_IDENTITY_NOT_FOUND );
}