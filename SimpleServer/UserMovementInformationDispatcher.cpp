#include "StdAfx.h"
#include "UserMovementInformationDispatcher.h"
#include "SimpleServerException.h"

using namespace simpleserver;

UserMovementInformationDispatcher::UserMovementInformationDispatcher(void)
{
}


UserMovementInformationDispatcher::~UserMovementInformationDispatcher(void)
{
}

void UserMovementInformationDispatcher::process( OBJECT_IDENTITY id, UserMovementInformation * info )
{
	std::hash_map<OBJECT_IDENTITY, IUserMovementInformationProcessor *>::iterator it = processors.find(id);
	if ( it != processors.end() ) 
		it->second->process( info );
	else
		delete info;
}

void UserMovementInformationDispatcher::addProcessor( OBJECT_IDENTITY id, IUserMovementInformationProcessor * processor )
{
	if ( processor == 0 ) 
		throw SimpleServerException("UserMovementInformationDispatcher addProcessor got processor = 0");
	processors.insert( std::pair<OBJECT_IDENTITY, IUserMovementInformationProcessor *>( id, processor ) );
}

void UserMovementInformationDispatcher::clearProcessor( OBJECT_IDENTITY id )
{
	if ( processors.find(id) == processors.end() )
		throw SimpleServerException("UserMovementInformationDispatcher clearProcessor not exist");
	processors.erase( id );
}