#include "StdAfx.h"
#include "SimpleMainComponent.h"
#include "SimpleClientMessage.h"
#include "SimpleSoundMessage.h"

#include "PostMainCompDefaultProcessor.h"
#include "PostMainCompSoundResourceResolveProcessor.h"

using namespace simpleclient;
using namespace communications;

#define CLIENTSETTINGS "clientsettings.txt"
//#define CLIENTSOUNDSREGISTER "clientsettings.txt"

SimpleMainComponent::SimpleMainComponent(void)
{
	postOffice = communications::CommunicationsFacade::INSTANCE()->registerPostOffice( communications::MASTER_COMPONENT_ID );
	postOffice->registerDefaultProcessor( new PostMainCompDefaultProcessor() );
	postOffice->registerProcessor( new PostMainCompSoundResourceResolveProcessor( this ) );

	ff = filesystem::FileSystemFacade::INSTANCE();

	ff->addToRegisterFile( CLIENTSETTINGS );
	populateContext();
}

void SimpleMainComponent::populateContext( void )
{
	int mainSleapType = ff->getIntInFile( CLIENTSETTINGS, "mainthreadsleeptime" );
	int netSleapType = ff->getIntInFile( CLIENTSETTINGS, "networkthreadsleeptime" );
	int postthreadsleeptime = ff->getIntInFile( CLIENTSETTINGS, "postthreadsleeptime" );
	SIMPLE_STRING serverip = ff->getValueInFile( CLIENTSETTINGS, "serverip" );
	int serverPort = ff->getIntInFile( CLIENTSETTINGS, "serverport" );

	std::cout << mainSleapType << std::endl;
	std::cout << netSleapType << std::endl;
	std::cout << postthreadsleeptime << std::endl;
	std::cout << serverip << std::endl;
	std::cout << serverPort << std::endl;

	context = new SimpleClientContext();
	context->mainthreadsleeptime = mainSleapType;
	context->postthreadsleeptime = postthreadsleeptime;
	context->mSimpleNetManagerContext = new SimpleNetManagerContext();
	context->mSimpleNetManagerContext->netSleapType = netSleapType;
	context->mSimpleNetManagerContext->ip = serverip;
	context->mSimpleNetManagerContext->port = serverPort;

	context->mSimpleVideoManagerContext = new SimpleVideoManagerContext();
	context->mSimpleVideoManagerContext->resolutionx = ff->getIntInFile( CLIENTSETTINGS, "resolutionx" );
	context->mSimpleVideoManagerContext->resolutiony = ff->getIntInFile( CLIENTSETTINGS, "resolutiony" );
	context->mSimpleVideoManagerContext->fullscreen = ff->getBoolInFile( CLIENTSETTINGS, "fullscreen" );

	context->mSimpleSoundManagerContext = new SimpleSoundManagerContext();
	context->mSimpleSoundManagerContext->soundSleapType = ff->getIntInFile( CLIENTSETTINGS, "soundthreadsleeptime" );
	context->mSimpleSoundManagerContext->volumemusic = ff->getFloatInFile( CLIENTSETTINGS, "volumemusic" );
	context->mSimpleSoundManagerContext->mastervolumesound = ff->getFloatInFile( CLIENTSETTINGS, "volumesound" );
	ff->addToRegisterFile( ff->getValueInFile( CLIENTSETTINGS, "soundsregister" ) );
}

SimpleMainComponent::~SimpleMainComponent(void)
{
}

void SimpleMainComponent::activate(void)
{
	start();
}

void SimpleMainComponent::run(void)
{
	PRINTINFO("SimpleMainComponent: ","started");

	netMan = new SimpleNetManager( context->mSimpleNetManagerContext );
	soundMan = new SimpleSoundManager( context->mSimpleSoundManagerContext );

	communications::CommunicationsFacade::INSTANCE()->activate( context->postthreadsleeptime );

	netMan->activate();
	soundMan->activate();

	while ( true ) {
		Sleep( context->mainthreadsleeptime );
		postOffice->obtain();
		postOffice->flush();
	}

	soundMan->terminate();
	netMan->terminate();

	delete soundMan;
	delete netMan;
}