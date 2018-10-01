#include "StdAfx.h"
#include "NetObjectMovingProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"

#include "SimpleInputStateSnapshot.h"

using namespace simpleclient;

NetObjectMovingProcessor::NetObjectMovingProcessor( IMessagesSenderProvider * _messagesSenderProvider ) : messagesSenderProvider(_messagesSenderProvider)
{
}


NetObjectMovingProcessor::~NetObjectMovingProcessor(void)
{
}

void NetObjectMovingProcessor::process( NS_Serializable * data )
{
	MessageBodyObjectsStatesUpdate * mess = (MessageBodyObjectsStatesUpdate *) data;

	InnerObjectLocationMessage * ss = new InnerObjectLocationMessage();
	for( std::vector<OBJECT_IDENTITY>::iterator it = mess->objects.begin(); it != mess->objects.end(); ++it ){
		ss->objects.push_back( *it );
	}
	for( std::vector<long>::iterator it = mess->currentTimes.begin(); it != mess->currentTimes.end(); ++it ){
		ss->currentTimes.push_back( *it );
	}
	for( std::vector<float>::iterator it = mess->currentPositions.begin(); it != mess->currentPositions.end(); ++it ){
		ss->currentPositions.push_back( *it );
	}
	for( std::vector<float>::iterator it = mess->nextPositions1.begin(); it != mess->nextPositions1.end(); ++it ){
		ss->nextPositions1.push_back( *it );
	}
	for( std::vector<float>::iterator it = mess->nextPositions2.begin(); it != mess->nextPositions2.end(); ++it ){
		ss->nextPositions2.push_back( *it );
	}
	messagesSenderProvider->sendLocal( ss, VIDEO_COMPONENT_ID );
}

NS_MESSAGE_TYPE NetObjectMovingProcessor::getType()
{
	return SIMPLE_MESSAGE_OBJECTS_STATES_UPDATE;
}