#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"

namespace simpleclient {

class NetCannotConnectProcessor : public netsystem::NSIClientSystemMessageProcessor
{
public:
	NetCannotConnectProcessor( IMessagesSenderProvider * );
	virtual ~NetCannotConnectProcessor(void);
	virtual void process( NS_Serializable * data );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
};

}