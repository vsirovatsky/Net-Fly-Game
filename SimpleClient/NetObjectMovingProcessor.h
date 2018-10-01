#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"

namespace simpleclient {

class NetObjectMovingProcessor : public netsystem::NSIClientCustomMessageProcessor
{
public:
	NetObjectMovingProcessor( IMessagesSenderProvider * );
	virtual ~NetObjectMovingProcessor(void);
	virtual void process( NS_Serializable * data );
	virtual NS_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSenderProvider;
};

}