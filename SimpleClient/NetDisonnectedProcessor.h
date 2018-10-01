#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"
#include "SimpleNetState.h"

namespace simpleclient {

class NetDisonnectedProcessor : public netsystem::NSIClientSystemMessageProcessor
{
public:
	NetDisonnectedProcessor( IMessagesSenderProvider *, ISimpleNetState * );
	virtual ~NetDisonnectedProcessor(void);
	virtual void process( NS_Serializable * data );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
	ISimpleNetState * netState;
};

}
