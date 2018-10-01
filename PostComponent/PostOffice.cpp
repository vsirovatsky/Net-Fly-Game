#include "StdAfx.h"
#include "PostOffice.h"
#include "CommunicationsException.h"

using namespace communications;

PostOffice::PostOffice( COMPONENT_IDS id )  : AbstractPostOffice(id)
{
	defaultProcessor = 0;
	defaultFilter = 0;
}


PostOffice::~PostOffice(void)
{
	if ( defaultFilter != 0 ) {
		delete defaultFilter;
	}
	if ( defaultProcessor != 0 ) {
		delete defaultProcessor;
	}
	if ( !regProcessors.empty() ) {
		for ( std::hash_map<PC_MESSAGE_TYPE, IPostMessageProcessor*>::iterator it = regProcessors.begin(); it!=regProcessors.end(); ++it) {
			delete it->second;
		}
		regProcessors.clear();
	}
}

void PostOffice::send( IMessage * mess, COMPONENT_IDS receiverId )
{
	Envelope * en = new Envelope( getId(), receiverId, mess );
	PRINTDEBUG("Postoffice Accespted to send: ", en);
	toSendCache.push_back( en );
}

void PostOffice::send( PC_MESSAGES_LIST * messagesList, COMPONENT_IDS receiverId )
{
	for(PC_MESSAGES_LIST::iterator it = messagesList->begin(); it != messagesList->end(); ++it ){
		Envelope * en = new Envelope( getId(), receiverId, *it );
		toSendCache.push_back( en );
	}
}

void PostOffice::populateToSend( PC_ENVELOPES_LIST & en )
{
	mut.Lock();
	if ( toSend.empty() ) {
		mut.Unlock();
		return;
	}
	for(PC_ENVELOPES_LIST::iterator it = toSend.begin(); it != toSend.end(); ++it ){
		en.push_back( *it );
	}
	toSend.clear();
	mut.Unlock();
}

PC_ENVELOPES_LIST * PostOffice::getForPopulateToReceive()
{
	mut.Lock();
	return &received;
}

void PostOffice::endPopulateToReceive()
{
	mut.Unlock();
}

void PostOffice::flush()
{
	mut.Lock();
	if ( toSendCache.empty() ) {
		mut.Unlock();
		return;
	}
	for(PC_ENVELOPES_LIST::iterator it = toSendCache.begin(); it != toSendCache.end(); ++it ){
		toSend.push_back( *it );
	}
	toSendCache.clear();
	mut.Unlock();
}

void PostOffice::obtain()
{
	PC_ENVELOPES_LIST envelopes = PC_ENVELOPES_LIST();
	mut.Lock();
	if ( received.empty() ) {
		mut.Unlock();
		return;
	}
	for(PC_ENVELOPES_LIST::iterator it = received.begin(); it != received.end(); ++it ){
		envelopes.push_back( *it );
	}
	received.clear();
	mut.Unlock();

	for(PC_ENVELOPES_LIST::iterator it = envelopes.begin(); it != envelopes.end(); ++it ){
		if ( (defaultFilter != 0) && !(defaultFilter->pass( *it )) ) {
			delete (*it);
			continue;
		}
		IPostMessageProcessor * processor = regProcessors[(*it)->message->getType()];
		if ( processor != 0 ) {
			processor->process( *it );
		} else if ( defaultProcessor != 0 ) {
			defaultProcessor->process( *it );
		} else {
			//TODO: notify not processed message
		}
		delete (*it);
	}
}

void PostOffice::registerProcessor( IPostMessageProcessor * processor )
{
	if ( processor == 0 ) {
		throw CommunicationsException("processor is null in registerProcessor");
	}
	if ( regProcessors.find( processor->getType() ) != regProcessors.end() ) {
		regProcessors.erase( processor->getType() );
	}
	regProcessors.insert( std::pair<PC_MESSAGE_TYPE, IPostMessageProcessor*>( processor->getType(), processor ) );
}

void PostOffice::registerDefaultProcessor( IPostMessageProcessor * processor )
{
	defaultProcessor = processor;
}

void PostOffice::refisterDefaultFilter( IPostFilter * filter )
{
	defaultFilter = filter;
}
