#include "StdAfx.h"
#include "NetUserStatusReceiveProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"

using namespace simpleclient;

NetUserStatusReceiveProcessor::NetUserStatusReceiveProcessor( IMessagesSenderProvider * _messagesSenderProvider, ISimpleNetState * _netState ) : messagesSenderProvider(_messagesSenderProvider), netState(_netState)
{
}


NetUserStatusReceiveProcessor::~NetUserStatusReceiveProcessor(void)
{
}

void NetUserStatusReceiveProcessor::process( NS_Serializable * data )
{
	PRINTDEBUG("NetUserStatusReceiveProcessor recieved: ", data);
	MessageBodyUserInfo * ui = (MessageBodyUserInfo *)data;
	netState->setIdentity( ui->obj );

	InnerObjectStartUpVideoMessage * innerMes = new InnerObjectStartUpVideoMessage();
	innerMes->objectIdentity = ui->obj;
	innerMes->x = ui->x;
	innerMes->y = ui->y;
	innerMes->z = ui->z;
	innerMes->timeDiffWithServer = GetCurrentTime() - ui->serverCurrentTime;
	PRINTDEBUG("NetUserStatusReceiveProcessor sent: ", innerMes);
	messagesSenderProvider->sendLocal( innerMes, VIDEO_COMPONENT_ID );
}

NS_MESSAGE_TYPE NetUserStatusReceiveProcessor::getType()
{
	return SIMPLE_MESSAGE_USER_INFO;
}