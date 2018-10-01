#pragma once

#include "SimpleNetMessages.h"

namespace simpleserver {

class IMessagesSenderProvider {
public:
	IMessagesSenderProvider(){}
	virtual ~IMessagesSenderProvider(){}
	virtual void sendReliable( netsystem::NetServerMessage & message ) = 0;
	virtual void sendFast( netsystem::NetServerMessage & message ) = 0;
};

}