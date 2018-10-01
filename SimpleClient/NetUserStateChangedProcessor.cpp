#include "StdAfx.h"
#include "NetUserStateChangedProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"

using namespace simpleclient;

NetUserStateChangedProcessor::NetUserStateChangedProcessor( IMessagesSenderProvider * _messagesSenderProvider ) : messagesSenderProvider(_messagesSenderProvider)
{
}


NetUserStateChangedProcessor::~NetUserStateChangedProcessor(void)
{
}

void NetUserStateChangedProcessor::process( NS_Serializable * data )
{
	MessageBodyUserState * mess = (MessageBodyUserState *) data;

	if ( (mess->previous == USER_STATE_ONLINE) && (mess->next == USER_STATE_OFFLINE) ) {
		InnerObjectAnotherUserStatusChanged * messLocal = new InnerObjectAnotherUserStatusChanged();
		messLocal->userId = mess->obj;
		messLocal->userConnceted = false;
		messagesSenderProvider->sendLocal( messLocal, communications::VIDEO_COMPONENT_ID );
	}
	if ( (mess->previous == USER_STATE_OFFLINE) && (mess->next == USER_STATE_ONLINE) ) {
		InnerObjectAnotherUserStatusChanged * messLocal = new InnerObjectAnotherUserStatusChanged();
		messLocal->userId = mess->obj;
		messLocal->userConnceted = true;
		messagesSenderProvider->sendLocal( messLocal, communications::VIDEO_COMPONENT_ID );
	}
}

NS_MESSAGE_TYPE NetUserStateChangedProcessor::getType()
{
	return SIMPLE_MESSAGE_USER_STATE_CHANGED;
}