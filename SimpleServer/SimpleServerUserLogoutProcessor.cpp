#include "StdAfx.h"
#include "SimpleServerUserLogoutProcessor.h"
#include "LogicFacade.h"

using namespace simpleserver;

SimpleServerUserLogoutProcessor::SimpleServerUserLogoutProcessor( IMessagesSenderProvider * _messagesSenderProvider, IUserManagementProvider * _userManagementProvider ) : 
	messagesSenderProvider(_messagesSenderProvider), userManagementProvider(_userManagementProvider)
{
}


SimpleServerUserLogoutProcessor::~SimpleServerUserLogoutProcessor(void)
{
}

void SimpleServerUserLogoutProcessor::process( netsystem::NetServerMessage & mess )
{
	OBJECT_IDENTITY oi = userManagementProvider->getIdentity( mess.guid );
	userManagementProvider->removeUser( mess.guid );

	LogicFacade::INSTANCE()->getGameObjectsManager().setOperatableByUser( oi, false );
	LogicFacade::INSTANCE()->getGameObjectsManager().deleteGameObject( oi );

	NetServerMessage nm( SIMPLE_MESSAGE_USER_STATE_CHANGED, mess.guid );
	nm.broadcast = true;
	nm.data = new MessageBodyUserState( oi, USER_STATE_ONLINE, USER_STATE_OFFLINE );
	messagesSenderProvider->sendReliable( nm );
	delete nm.data;
}

NS_MESSAGE_TYPE SimpleServerUserLogoutProcessor::getType()
{
	return NS_SYSTEM_SERVER_MESSAGE_DISCONNECTED;
}