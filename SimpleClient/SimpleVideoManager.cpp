#include "StdAfx.h"
#include "SimpleVideoManager.h"
#include "SimpleClientException.h"
#include "SimpleSoundMessage.h"

#include "PostVideoDefaultProcessor.h"
#include "PostVideoObjectMovingProcessor.h"
#include "PostVideoStartupProcessor.h"
#include "PostVideoAnotherUserStatusChangedProcessor.h"

using namespace simpleclient;
using namespace communications;

SimpleVideoManager::SimpleVideoManager( SimpleVideoManagerContext * nContext )
{
	prevSendingPositionTime = 0;
	context = nContext;
	videoState = new SimpleVideoState();
	postOffice = communications::CommunicationsFacade::INSTANCE()->registerPostOffice( communications::VIDEO_COMPONENT_ID );
	sysVideo = videosystem::VideoSystemFacade::INSTANCE();

	controlMan = new SimpleControlManager();
	cameraMovementController = new VideoObjectMovementController( 0 );
	videoSoundPlayRequester = new VideoSoundPlayRequester( postOffice );
	objectsRegister = new VideoObjectsRegister( videoSoundPlayRequester );

	postOffice->refisterDefaultFilter( this );
	postOffice->registerDefaultProcessor( new PostVideoDefaultProcessor() );
	postOffice->registerProcessor( new PostVideoObjectMovingProcessor( this ) );
	postOffice->registerProcessor( new PostVideoStartupProcessor( this ) );
	postOffice->registerProcessor( new PostVideoAnotherUserStatusChangedProcessor(this) );
}

SimpleVideoManager::~SimpleVideoManager(void)
{
	delete controlMan;
	delete videoState;
	delete videoSoundPlayRequester;
	delete cameraMovementController;
	delete context;
	delete sysVideo;
}

void SimpleVideoManager::initialize()
{
	videosystem::VS_Context vscontext = videosystem::VS_Context( videosystem::VS_DT_OPENGL, context->resolutionx, context->resolutiony );
	vscontext.cursorVisible = false;
	vscontext.videoSystemToCaptureEvents = true;
	vscontext.fullscreen = context->fullscreen;
	
	sysVideo->startUp( vscontext );
	controlMan->setInputReceiver( sysVideo->getInputReceiver() );
	controlMan->setSimpleVideoManagerPanel( this );
	controlMan->setSimpleMovementListener( this );
	camera = sysVideo->createCamera();
}

void SimpleVideoManager::run()
{
	PRINTINFO("SimpleVideoManager: ","started");
	while ( true ) {
		try {
			Sleep( 200 );
			// Top block over video cycle
			postOffice->obtain();
			postOffice->flush();
			runImpl();
		} catch (...) {
			throw;
		}
	}
}

void SimpleVideoManager::runImpl()
{
	if ( !videoState->isStarted() ) {
		return;
	}
	while ( sysVideo->isRunning() ) {
		postOffice->obtain();
		controlMan->iterate();
		postOffice->flush();
		updateObjectsLocations();
		sysVideo->render();
	}
}

void SimpleVideoManager::updateObjectsLocations()
{
	if ( !videoState->isStarted() ) 
		return;
	if ( cameraMovementController->isMoving() ) {
		videosystem::vector3df & pos = cameraMovementController->getNextPos();
		camera->setPosition( pos );
		videoSoundPlayRequester->updateUserPosition( pos.x, pos.y, pos.z );
		videoSoundPlayRequester->updateObjectPosition( videoState->getIdentity(), pos.x, pos.y, pos.z );
	}
	objectsRegister->updateUbjectsPositions();

	/*VideoObjectMovementController * c = objectsRegister.getMovementController( 1 );
	if ( c!=0 ) {
		videosystem::vector3df v = c->getNextPos();
		camera->setPosition( v );
		std::stringstream ss;
		ss << "MY POS: " << '(' << v.x << ',' << v.y << ',' << v.z << ')';
		sysVideo->get2DControlPanel()->printText(12, ss.str());
	}*/
	

		/*long curr = GetCurrentTime();
		if ( (prevSendingPositionTime + 500) > curr ) {
			return;
		}
		prevSendingPositionTime = curr;
		InnerObjectLocationMessage * innerMes = new InnerObjectLocationMessage();
		innerMes->objectIdentity = videoState->getIdentity();
		innerMes->x = camera->getPosition().x;
		innerMes->y = camera->getPosition().y;
		innerMes->z = camera->getPosition().z;

		postOffice->send( innerMes, NET_COMPONENT_ID );*/

		/*InnerSoundSinglePlay * playSoundTemp = new InnerSoundSinglePlay();
		playSoundTemp->x = 0;
		playSoundTemp->y = 0;
		playSoundTemp->z = 0;
		playSoundTemp->resourceId = "spheresound";
		playSoundTemp->soundId = "move1";

		postOffice->send( playSoundTemp, SOUND_COMPONENT_ID );*/
}

bool SimpleVideoManager::pass( communications::Envelope * en )
{
	PRINTDEBUG("SimpleVideoManager filtering: ", en);
	if ( videoState->isStarted() )
		return true;
	if ( (en->message!=0) && (en->message->getType() == MESSAGE_TYPE_STARTUP_VIDEO) )
		return true;
	return false;
}

void SimpleVideoManager::send( IMessage * mess, COMPONENT_IDS receiverId )
{
	postOffice->send( mess, receiverId );
}

void SimpleVideoManager::notifyMovementPressed()
{
	videoSoundPlayRequester->requestSoundStart( videoState->getIdentity(), "spheresound", "move1");
}

void SimpleVideoManager::notifyMovementReleased()
{
	videoSoundPlayRequester->requestSoundStop( videoState->getIdentity(), "spheresound", "move1");
}