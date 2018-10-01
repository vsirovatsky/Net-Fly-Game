#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"
#include "SimpleNetState.h"

namespace simpleclient {

class NetUserStatusReceiveProcessor : public netsystem::NSIClientCustomMessageProcessor
{
public:
	NetUserStatusReceiveProcessor( IMessagesSenderProvider *, ISimpleNetState * );
	virtual ~NetUserStatusReceiveProcessor(void);
	virtual void process( NS_Serializable * data );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
	ISimpleNetState * netState;
};

}