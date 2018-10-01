#include "StdAfx.h"
#include "SimpleServerUserMoveProcessor.h"
#include "LogicFacade.h"

using namespace simpleserver;

SimpleServerUserMoveProcessor::SimpleServerUserMoveProcessor( IMessagesSenderProvider * _messagesSenderProvider, IUserManagementProvider * _userManagementProvider ) : 
	messagesSenderProvider(_messagesSenderProvider), userManagementProvider(_userManagementProvider)
{
}


SimpleServerUserMoveProcessor::~SimpleServerUserMoveProcessor(void)
{
}

void SimpleServerUserMoveProcessor::process( netsystem::NetServerMessage & mess )
{
	PRINTDEBUG("SimpleServerUserMoveProcessor received: ", &mess);

	MessageBodyUserAction * messResolved = (MessageBodyUserAction *) mess.data;

	UserMovementInformation * info = new UserMovementInformation( messResolved->forward, messResolved->backward, messResolved->left, messResolved->right, messResolved->dirX, messResolved->dirY, messResolved->dirZ, messResolved->time );

	OBJECT_IDENTITY id = userManagementProvider->getIdentity( mess.guid );

	LogicFacade::INSTANCE()->getGameObjectsManager().userMovementInformationDispatcher.process( id, info );

	//NetServerMessage nm( SIMPLE_MESSAGE_USER_ACTION_STATE, mess.guid );
	//nm.broadcast = false;
	//nm.data = new MessageBodyUserAction( messResolved->forward, messResolved->backward, messResolved->left, messResolved->right, messResolved->dirX, messResolved->dirY, messResolved->dirZ, messResolved->time );

	/*OBJECT_IDENTITY oi = userManagementProvider->getIdentity( mess.guid );

	MessageBodyObjectLocation * messResolved = (MessageBodyObjectLocation *) mess.data;

	NetServerMessage nm( SIMPLE_MESSAGE_OBJECT_LOCATION, mess.guid );
	nm.broadcast = true;
	nm.data = new MessageBodyObjectLocation( oi, messResolved->x, messResolved->y, messResolved->z );*/

	//PRINTDEBUG("SimpleServerUserMoveProcessor sent: ", &nm);
	//messagesSenderProvider->sendReliable( nm );
	//delete nm.data;
}

NS_MESSAGE_TYPE SimpleServerUserMoveProcessor::getType()
{
	return SIMPLE_MESSAGE_USER_ACTION_STATE;
}