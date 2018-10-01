#include "StdAfx.h"
#include "CommunicationsManager.h"
#include "CommunicationsException.h"
#include "communicationsTypeDefs.h"
#include "Logger.h"

using namespace communications;

CommunicationsManager::CommunicationsManager(void) : CommunicationsAbstractManager()
{
	postOffice_COMMUNICATIONS = 0;
	postOffice_MASTER = 0;
	postOffice_INPUT = 0;
	postOffice_NET = 0;
	postOffice_FILE = 0;
	postOffice_SOUND = 0;
	postOffice_VIDEO = 0;
}


CommunicationsManager::~CommunicationsManager(void)
{
}

void CommunicationsManager::run()
{
	while ( true ) {
		try {
			Sleep( threadSleepTime );
			topMutex.Lock();
			
			runImpl();

			topMutex.Unlock();
		} catch (...) {
			topMutex.Unlock();
			throw;
		}
	}
}

void CommunicationsManager::activate( int nThreadSleepTime )
{
	if ( IsThreadActive() ) {
		throw CommunicationsException("COMMUNICATIONS already active");
	}
	threadSleepTime = nThreadSleepTime;
	start();
	PRINT("Communications thread started.");
}

PostOffice * CommunicationsManager::getOffice( COMPONENT_IDS officeId )
{
	switch (officeId) {
		case COMMUNICATIONS_COMPONENT_ID:
			return postOffice_COMMUNICATIONS;
		case MASTER_COMPONENT_ID:
			return postOffice_MASTER;
		case INPUT_COMPONENT_ID:
			return postOffice_INPUT;
		case NET_COMPONENT_ID:
			return postOffice_NET;
		case FILE_COMPONENT_ID:
			return postOffice_FILE;
		case SOUND_COMPONENT_ID:
			return postOffice_SOUND;
		case VIDEO_COMPONENT_ID:
			return postOffice_VIDEO;
		default:
			throw CommunicationsException("No id registered for registerPostOffice");
		}
}

void CommunicationsManager::runImpl()
{
	PC_ENVELOPES_LIST toSend;
	if (postOffice_COMMUNICATIONS != 0) 
		postOffice_COMMUNICATIONS->populateToSend( toSend );
	if (postOffice_MASTER != 0) 
		postOffice_MASTER->populateToSend( toSend );
	if (postOffice_INPUT != 0) 
		postOffice_INPUT->populateToSend( toSend );
	if (postOffice_NET != 0) 
		postOffice_NET->populateToSend( toSend );
	if (postOffice_FILE != 0) 
		postOffice_FILE->populateToSend( toSend );
	if (postOffice_SOUND != 0) 
		postOffice_SOUND->populateToSend( toSend );
	if (postOffice_VIDEO != 0) 
		postOffice_VIDEO->populateToSend( toSend );

	if ( toSend.empty() ) 
		return;

	PC_ENVELOPES_LIST * r_COMMUNICATIONS = (postOffice_COMMUNICATIONS!=0) ? postOffice_COMMUNICATIONS->getForPopulateToReceive() : 0;
	PC_ENVELOPES_LIST * r_MASTER = (postOffice_MASTER!=0) ? postOffice_MASTER->getForPopulateToReceive() : 0;
	PC_ENVELOPES_LIST * r_INPUT = (postOffice_INPUT!=0) ? postOffice_INPUT->getForPopulateToReceive() : 0;
	PC_ENVELOPES_LIST * r_NET = (postOffice_NET!=0) ? postOffice_NET->getForPopulateToReceive() : 0;
	PC_ENVELOPES_LIST * r_FILE = (postOffice_FILE!=0) ? postOffice_FILE->getForPopulateToReceive() : 0;
	PC_ENVELOPES_LIST * r_SOUND = (postOffice_SOUND!=0) ? postOffice_SOUND->getForPopulateToReceive() : 0;
	PC_ENVELOPES_LIST * r_VIDEO = (postOffice_VIDEO!=0) ? postOffice_VIDEO->getForPopulateToReceive() : 0;

	for(PC_ENVELOPES_LIST::iterator it = toSend.begin(); it != toSend.end(); ++it ){
		switch ((*it)->receiver) {
			case COMMUNICATIONS_COMPONENT_ID:
				if ( r_COMMUNICATIONS!=0 ) 
					r_COMMUNICATIONS->push_back( *it );
				else 
					lostMessage( *it );
				break;
			case MASTER_COMPONENT_ID:
				if ( r_MASTER!=0 ) 
					r_MASTER->push_back( *it );
				else 
					lostMessage( *it );
				break;
			case INPUT_COMPONENT_ID:
				if ( r_INPUT!=0 ) 
					r_INPUT->push_back( *it );
				else 
					lostMessage( *it );
				break;
			case NET_COMPONENT_ID:
				if ( r_NET!=0 ) 
					r_NET->push_back( *it );
				else 
					lostMessage( *it );
				break;
			case FILE_COMPONENT_ID:
				if ( r_FILE!=0 ) 
					r_FILE->push_back( *it );
				else 
					lostMessage( *it );
				break;
			case SOUND_COMPONENT_ID:
				if ( r_SOUND!=0 ) 
					r_SOUND->push_back( *it );
				else 
					lostMessage( *it );
				break;
			case VIDEO_COMPONENT_ID:
				if ( r_VIDEO!=0 ) 
					r_VIDEO->push_back( *it );
				else 
					lostMessage( *it );
				break;
			default:
				throw CommunicationsException("No id registered for registerPostOffice");
		}
	}

	if (postOffice_COMMUNICATIONS != 0) 
		postOffice_COMMUNICATIONS->endPopulateToReceive();
	if (postOffice_MASTER != 0) 
		postOffice_MASTER->endPopulateToReceive();
	if (postOffice_INPUT != 0) 
		postOffice_INPUT->endPopulateToReceive();
	if (postOffice_NET != 0) 
		postOffice_NET->endPopulateToReceive();
	if (postOffice_FILE != 0) 
		postOffice_FILE->endPopulateToReceive();
	if (postOffice_SOUND != 0) 
		postOffice_SOUND->endPopulateToReceive();
	if (postOffice_VIDEO != 0) 
		postOffice_VIDEO->endPopulateToReceive();
}

AbstractPostOffice * CommunicationsManager::registerPostOffice( COMPONENT_IDS officeId )
{
	try {
		AbstractPostOffice * office;
		topMutex.Lock();
		try {
			switch (officeId) {
			case COMMUNICATIONS_COMPONENT_ID:
				if ( postOffice_COMMUNICATIONS == 0 ) {
					postOffice_COMMUNICATIONS = new PostOffice( officeId );
					office = postOffice_COMMUNICATIONS;
				} else {
					throw CommunicationsException("PostOffice For COMMUNICATIONS already registered");
				}
				break;
			case MASTER_COMPONENT_ID:
				if ( postOffice_MASTER == 0 ) {
					postOffice_MASTER = new PostOffice( officeId );
					office = postOffice_MASTER;
				} else {
					throw CommunicationsException("PostOffice For MASTER already registered");
				}
				break;
			case INPUT_COMPONENT_ID:
				if ( postOffice_INPUT == 0 ) {
					postOffice_INPUT = new PostOffice( officeId );
					office = postOffice_INPUT;
				} else {
					throw CommunicationsException("PostOffice For INPUT already registered");
				}
				break;
			case NET_COMPONENT_ID:
				if ( postOffice_NET == 0 ) {
					postOffice_NET = new PostOffice( officeId );
					office = postOffice_NET;
				} else {
					throw CommunicationsException("PostOffice For NET already registered");
				}
				break;
			case FILE_COMPONENT_ID:
				if ( postOffice_FILE == 0 ) {
					postOffice_FILE = new PostOffice( officeId );
					office = postOffice_FILE;
				} else {
					throw CommunicationsException("PostOffice For FILE already registered");
				}
				break;
			case SOUND_COMPONENT_ID:
				if ( postOffice_SOUND == 0 ) {
					postOffice_SOUND = new PostOffice( officeId );
					office = postOffice_SOUND;
				} else {
					throw CommunicationsException("PostOffice For SOUND already registered");
				}
				break;
			case VIDEO_COMPONENT_ID:
				if ( postOffice_VIDEO == 0 ) {
					postOffice_VIDEO = new PostOffice( officeId );
					office = postOffice_VIDEO;
				} else {
					throw CommunicationsException("PostOffice For VIDEO already registered");
				}
				break;
			default:
				throw CommunicationsException("No id registered for registerPostOffice");
			}
		} catch (CommunicationsException ex) {
			throw ex;
		} catch (...) {
			throw CommunicationsException("Unknown exception in registerPostOffice");
		}
		topMutex.Unlock();
		return office;
	} catch (...) {
		topMutex.Unlock();
		throw;
	}
}

void CommunicationsManager::lostMessage( Envelope * en )
{
	// TODO: inform
	delete en;
}