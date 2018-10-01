#pragma once

#include "PostOffice.h"
#include "IMessagesSenderProvider.h"
#include "SimpleNetState.h"

namespace simpleclient {

class PostNetObjectMovingProcessor : public communications::IPostMessageProcessor
{
public:
	PostNetObjectMovingProcessor( IMessagesSenderProvider *, ISimpleNetState * );
	virtual ~PostNetObjectMovingProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	IMessagesSenderProvider * messagesSender;
	ISimpleNetState * netState;
};

}