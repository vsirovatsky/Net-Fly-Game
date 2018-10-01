#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"

namespace simpleclient {

class NetUserStateChangedProcessor : public netsystem::NSIClientCustomMessageProcessor
{
public:
	NetUserStateChangedProcessor( IMessagesSenderProvider * );
	virtual ~NetUserStateChangedProcessor(void);
	virtual void process( NS_Serializable * data );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
};

}
