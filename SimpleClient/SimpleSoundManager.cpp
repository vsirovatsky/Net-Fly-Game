#include "StdAfx.h"
#include "SimpleSoundManager.h"
#include "SimpleClientException.h"
#include "SimpleSoundMessage.h"

#include "PostSoundDefaultProcessor.h"
#include "PostSoundSingleSoundPlayProcessor.h"
#include "PostSoundResourceResolvedProcessor.h"
#include "PostSoundObjectInfoProcessor.h"
#include "PostSoundUserPositionUpdate.h"

using namespace simpleclient;
using namespace communications;

SimpleSoundManager::SimpleSoundManager( SimpleSoundManagerContext * nContext )
{
	sysSound = soundsystem::SoundSystemFacade::INSTANCE();
	postOffice = communications::CommunicationsFacade::INSTANCE()->registerPostOffice( communications::SOUND_COMPONENT_ID );
	resolvedResourcesContainer = new SimpleSoundResolvedResourcesContainer();
	soundObjectsRegister = new GameObjectSoundViewsRegister( sysSound, resolvedResourcesContainer );
	context = nContext;
	soundState = new SimpleSoundState();
	soundState->setSoundVolume( context->mastervolumesound );
	soundState->setMusicVolume( context->volumemusic );
	

	postOffice->registerDefaultProcessor( new PostSoundDefaultProcessor() );
	postOffice->registerProcessor( new PostSoundSingleSoundPlayProcessor( this ) );
	postOffice->registerProcessor( new PostSoundResourceResolvedProcessor( this ) );
	postOffice->registerProcessor( new PostSoundObjectInfoProcessor( this ) );
	postOffice->registerProcessor( new PostSoundUserPositionUpdate(this) );
}


SimpleSoundManager::~SimpleSoundManager(void)
{
	delete context;
	delete soundState;
	delete soundObjectsRegister;
	delete resolvedResourcesContainer;
	delete sysSound;
}

void SimpleSoundManager::activate(void)
{
	if ( IsThreadActive() ) {
		throw SimpleClientInitializationException("Sound component already active");
	}
	sysSound->init();
	start();
}

void SimpleSoundManager::run()
{
	PRINTINFO("SimpleSoundManager: ","started");
	int sleapTime = context->soundSleapType;
	while ( true ) {
		try {
			Sleep( sleapTime );
			//topMutex.Lock();
			
			runImpl();

			//topMutex.Unlock();
		} catch (...) {
			//topMutex.Unlock();
			throw;
		}
	}
}

void SimpleSoundManager::runImpl()
{
	postOffice->obtain();
	postOffice->flush();
	soundObjectsRegister->iterate();
}