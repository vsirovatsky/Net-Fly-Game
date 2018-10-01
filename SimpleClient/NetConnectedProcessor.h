#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"
#include "SimpleNetState.h"

namespace simpleclient {

class NetConnectedProcessor : public netsystem::NSIClientSystemMessageProcessor
{
public:
	NetConnectedProcessor( IMessagesSenderProvider *, ISimpleNetState * );
	virtual ~NetConnectedProcessor(void);
	virtual void process( NS_Serializable * data );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
	ISimpleNetState * netState;
};

}