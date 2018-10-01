#include "NetMessage.h"
#include "NetSystemException.h"

using namespace netsystem;

//CLIENT:
NSAbstractClientMessagesDispatcher::NSAbstractClientMessagesDispatcher()
{
	defaultCustomProcessor = 0;
	defaultSystemProcessor = 0;
}

NSAbstractClientMessagesDispatcher::~NSAbstractClientMessagesDispatcher()
{
	if ( defaultCustomProcessor != 0 ) {
		delete defaultCustomProcessor;
	}
	if ( defaultSystemProcessor != 0 ) {
		delete defaultSystemProcessor;
	}
	for ( std::hash_map<NS_MESSAGE_TYPE, NSIClientCustomMessageProcessor*>::iterator it = regCustom.begin(); it!=regCustom.end(); ++it) {
		delete it->second;
	}
	for ( std::hash_map<NS_MESSAGE_TYPE, NSIClientSystemMessageProcessor*>::iterator it = regSystem.begin(); it!=regSystem.end(); ++it) {
		delete it->second;
	}
}

void NSAbstractClientMessagesDispatcher::registerCustomProcessor( NSIClientCustomMessageProcessor * processor )
{
	if ( processor == 0 ) {
		throw NetSystemException("processor is null in registerCustomProcessor");
	}
	if ( regCustom.find( processor->getType() ) != regCustom.end() ) {
		regCustom.erase( processor->getType() );
	}
	regCustom.insert( std::pair<NS_MESSAGE_TYPE, NSIClientCustomMessageProcessor*>( processor->getType(), processor ) );
}

void NSAbstractClientMessagesDispatcher::registerCustomDefaultProcessor( NSIClientCustomMessageProcessor * processor )
{
	defaultCustomProcessor = processor;
}

void NSAbstractClientMessagesDispatcher::registerSystemProcessor( NSIClientSystemMessageProcessor * processor )
{
	if ( processor == 0 ) {
		throw NetSystemException("processor is null in registerSystemProcessor");
	}
	if ( regSystem.find( processor->getType() ) != regSystem.end() ) {
		regSystem.erase( processor->getType() );
	}
	regSystem.insert( std::pair<NS_MESSAGE_TYPE, NSIClientSystemMessageProcessor*>( processor->getType(), processor ) );
}

void NSAbstractClientMessagesDispatcher::registerSystemDefaultProcessor( NSIClientSystemMessageProcessor * processor )
{
	defaultSystemProcessor = processor;
}

void NSAbstractClientMessagesDispatcher::dispatch( NS_MESSAGES_LIST & messages )
{
	if ( messages.empty() ) {
		return;
	}
	for( NS_MESSAGES_LIST::iterator it = messages.begin(); it != messages.end(); ++it ){
		if ( it->type < NS_CUSTOM_MESSAGE_START ) {
			NSIClientSystemMessageProcessor * processor = regSystem[it->type];
			if ( processor != 0 ) {
				processor->process( it->data );
			} else if ( defaultSystemProcessor != 0 ) {
				defaultSystemProcessor->process( it->data );
			} else {
				//TODO: notify not processed message
			}
		} else {
			NSIClientCustomMessageProcessor * processor = regCustom[it->type];
			if ( processor != 0 ) {
				processor->process( it->data );
			} else if ( defaultCustomProcessor != 0 ) {
				defaultCustomProcessor->process( it->data );
			} else {
				//TODO: notify not processed message
			}
		}
		if ( it->data != 0 ) 
			delete it->data;
	}
}


// SERVER:
NSAbstractServerMessagesDispatcher::NSAbstractServerMessagesDispatcher()
{
	defaultCustomProcessor = 0;
	defaultSystemProcessor = 0;
}

NSAbstractServerMessagesDispatcher::~NSAbstractServerMessagesDispatcher()
{
	if ( defaultCustomProcessor != 0 ) {
		delete defaultCustomProcessor;
	}
	if ( defaultSystemProcessor != 0 ) {
		delete defaultSystemProcessor;
	}
	for ( std::hash_map<NS_MESSAGE_TYPE, NSIServerCustomMessageProcessor*>::iterator it = regCustom.begin(); it!=regCustom.end(); ++it) {
		delete it->second;
	}
	for ( std::hash_map<NS_MESSAGE_TYPE, NSIServerSystemMessageProcessor*>::iterator it = regSystem.begin(); it!=regSystem.end(); ++it) {
		delete it->second;
	}
}

void NSAbstractServerMessagesDispatcher::registerCustomProcessor( NSIServerCustomMessageProcessor * processor )
{
	if ( processor == 0 ) {
		throw NetSystemException("processor is null in registerCustomProcessor");
	}
	if ( regCustom.find( processor->getType() ) != regCustom.end() ) {
		regCustom.erase( processor->getType() );
	}
	regCustom.insert( std::pair<NS_MESSAGE_TYPE, NSIServerCustomMessageProcessor*>( processor->getType(), processor ) );
}

void NSAbstractServerMessagesDispatcher::registerCustomDefaultProcessor( NSIServerCustomMessageProcessor * processor )
{
	defaultCustomProcessor = processor;
}

void NSAbstractServerMessagesDispatcher::registerSystemProcessor( NSIServerSystemMessageProcessor * processor )
{
	if ( processor == 0 ) {
		throw NetSystemException("processor is null in registerSystemProcessor");
	}
	if ( regSystem.find( processor->getType() ) != regSystem.end() ) {
		regSystem.erase( processor->getType() );
	}
	regSystem.insert( std::pair<NS_MESSAGE_TYPE, NSIServerSystemMessageProcessor*>( processor->getType(), processor ) );
}

void NSAbstractServerMessagesDispatcher::registerSystemDefaultProcessor( NSIServerSystemMessageProcessor * processor )
{
	defaultSystemProcessor = processor;
}

void NSAbstractServerMessagesDispatcher::dispatch( NS_SERVER_MESSAGES_LIST & messages )
{
	if ( messages.empty() ) {
		return;
	}
	for( NS_SERVER_MESSAGES_LIST::iterator it = messages.begin(); it != messages.end(); ++it ){
		if ( it->type < NS_CUSTOM_MESSAGE_START ) {
			NSIServerSystemMessageProcessor * processor = regSystem[it->type];
			if ( processor != 0 ) {
				processor->process( *it );
			} else if ( defaultSystemProcessor != 0 ) {
				defaultSystemProcessor->process( *it );
			} else {
				//TODO: notify not processed message
			}
		} else {
			NSIServerCustomMessageProcessor * processor = regCustom[it->type];
			if ( processor != 0 ) {
				processor->process( *it );
			} else if ( defaultCustomProcessor != 0 ) {
				defaultCustomProcessor->process( *it );
			} else {
				//TODO: notify not processed message
			}
		}
		if ( it->data != 0 ) 
			delete it->data;
	}
}