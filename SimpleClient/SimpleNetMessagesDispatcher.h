#pragma once

#include "SimpleNetMessages.h"
#include "IMessagesSenderProvider.h"
#include "SimpleNetState.h"

namespace simpleclient {

class SimpleNetMessagesDispatcher : public netsystem::NSAbstractClientMessagesDispatcher
{
public:
	SimpleNetMessagesDispatcher( IMessagesSenderProvider *, ISimpleNetState * );
	virtual ~SimpleNetMessagesDispatcher(void);
};

}