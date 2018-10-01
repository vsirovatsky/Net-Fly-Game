#include "StdAfx.h"
#include "PostNetObjectMovingProcessor.h"
#include "SimpleClientMessage.h"
#include "SimpleNetMessages.h"
#include "Logger.h"

using namespace simpleclient;

PostNetObjectMovingProcessor::PostNetObjectMovingProcessor( IMessagesSenderProvider * _messagesSender, ISimpleNetState * _netState ) : messagesSender(_messagesSender), netState(_netState)
{
}


PostNetObjectMovingProcessor::~PostNetObjectMovingProcessor(void)
{
}

void PostNetObjectMovingProcessor::process( communications::Envelope * en )
{
	if ( !netState->isIdentity() ) {
		PRINT("OBJECT_IDENTITY_NOT_FOUND");
	}
	PRINT("SENDING LOCATION");
	NetMessage nm = NetMessage( SIMPLE_MESSAGE_OBJECT_LOCATION );
	InnerObjectUserActionState * innerMes = (InnerObjectUserActionState *)(en->message);
	nm.data = new MessageBodyUserAction( innerMes->forward, innerMes->backward, innerMes->left, innerMes->right, innerMes->dirX, innerMes->dirY, innerMes->dirZ, innerMes->time );
	messagesSender->sendReliable( nm );
	delete nm.data;
}

PC_MESSAGE_TYPE PostNetObjectMovingProcessor::getType()
{
	return MESSAGE_TYPE_USER_ACTION_STATE;
}