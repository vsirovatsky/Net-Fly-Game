#include "StdAfx.h"
#include "SimpleServerUserLoginProcessor.h"
#include "Logger.h"
#include "SimpleServerException.h"
#include "LogicFacade.h"

using namespace simpleserver;

SimpleServerUserLoginProcessor::SimpleServerUserLoginProcessor( IMessagesSenderProvider * _messagesSenderProvider, IUserManagementProvider * _userManagementProvider ) : 
	messagesSenderProvider(_messagesSenderProvider), userManagementProvider(_userManagementProvider)
{
}


SimpleServerUserLoginProcessor::~SimpleServerUserLoginProcessor(void)
{
}

void SimpleServerUserLoginProcessor::process( netsystem::NetServerMessage & mess )
{
	userManagementProvider->addUser( mess.guid );
	OBJECT_IDENTITY oi = userManagementProvider->getIdentity( mess.guid );
	std::cout << "new OBJECT_IDENTITY: " << oi << std::endl;

	LogicFacade::INSTANCE()->getGameObjectsManager().createGameObject( oi );
	LogicFacade::INSTANCE()->getGameObjectsManager().setOperatableByUser( oi, true );

	NetServerMessage nmToCurrent( SIMPLE_MESSAGE_USER_INFO, mess.guid );
	nmToCurrent.broadcast = false;
	nmToCurrent.data = new MessageBodyUserInfo( oi, GetCurrentTime(), 0,0,0 );
	messagesSenderProvider->sendReliable( nmToCurrent );
	delete nmToCurrent.data;
	std::cout << "OBJECT_IDENTITY to user sent" << std::endl;
	// Send to all except current guid
	NetServerMessage nm( SIMPLE_MESSAGE_USER_STATE_CHANGED, mess.guid );
	nm.broadcast = true;
	nm.data = new MessageBodyUserState( oi, USER_STATE_OFFLINE, USER_STATE_ONLINE );
	messagesSenderProvider->sendReliable( nm );
	delete nm.data;
}

NS_MESSAGE_TYPE SimpleServerUserLoginProcessor::getType()
{
	return NS_SYSTEM_SERVER_MESSAGE_CONNECTED;
}