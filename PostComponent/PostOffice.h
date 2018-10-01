#pragma once

#include "communicationsTypeDefs.h"
#include "CommunicationsMessage.h"
#include "Logger.h"
#include "SimpleMutex.h"
#include <hash_map>


namespace communications {

class IPostFilter
{
public:
	IPostFilter(){}
	virtual ~IPostFilter(){}
	virtual bool pass( Envelope * en ) = 0;
};

class IPostMessageProcessor 
{
public:
	IPostMessageProcessor(){}
	virtual ~IPostMessageProcessor(){}
	virtual void process( Envelope * en ) = 0;
	virtual PC_MESSAGE_TYPE getType() = 0;
};

class AbstractPostOffice
{
public:
	AbstractPostOffice( COMPONENT_IDS id )
	{
		mId = id;
		PRINTDEBUG("Post office created", mId);
	};
	virtual ~AbstractPostOffice(void)
	{
		PRINTDEBUG("Post office created", mId);
	};
	COMPONENT_IDS getId()
	{
		return mId;
	};

	virtual void send( IMessage * mess, COMPONENT_IDS receiverId ) = 0;
	virtual void send( PC_MESSAGES_LIST * messagesList, COMPONENT_IDS receiverId ) = 0;
	virtual void obtain() = 0;
	virtual void flush() = 0;
	virtual void registerProcessor( IPostMessageProcessor * processor ) = 0;
	virtual void registerDefaultProcessor( IPostMessageProcessor * processor ) = 0;
	virtual void refisterDefaultFilter( IPostFilter * ) = 0;
private: 
	COMPONENT_IDS mId;
};

class PostOffice : public AbstractPostOffice
{
public:
	PostOffice( COMPONENT_IDS id );
	virtual ~PostOffice();

	virtual void send( IMessage * mess, COMPONENT_IDS receiverId );
	virtual void send( PC_MESSAGES_LIST * messagesList, COMPONENT_IDS receiverId );
	virtual void obtain();
	virtual void flush();
	virtual void registerProcessor( IPostMessageProcessor * processor );
	virtual void registerDefaultProcessor( IPostMessageProcessor * processor );
	virtual void refisterDefaultFilter( IPostFilter * filter );

	void populateToSend( PC_ENVELOPES_LIST & en );

	PC_ENVELOPES_LIST * getForPopulateToReceive();
	void endPopulateToReceive();
private:
	PC_ENVELOPES_LIST received;
	PC_ENVELOPES_LIST toSend;
	PC_ENVELOPES_LIST toSendCache;
	common::SimpleMutex mut;
	std::hash_map<PC_MESSAGE_TYPE, IPostMessageProcessor*> regProcessors;
	IPostMessageProcessor * defaultProcessor;
	IPostFilter * defaultFilter;
};

}