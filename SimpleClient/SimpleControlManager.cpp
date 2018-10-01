#include "StdAfx.h"
#include "SimpleControlManager.h"
#include "SimpleClientMessage.h"

using namespace simpleclient;

SimpleControlManager::SimpleControlManager(void) : prevShot(0), movementRequest(false)
{
	movementProcessor = new SimpleMovementProcessor();
}

SimpleControlManager::~SimpleControlManager(void)
{
	delete movementProcessor;
}

void SimpleControlManager::setInputReceiver( videosystem::IInputReceiver * _inputReceiver )
{
	inputReceiver = _inputReceiver;
}

void SimpleControlManager::setSimpleVideoManagerPanel( ISimpleVideoManagerPanel * _videoPanel )
{
	videoPanel = _videoPanel;
}

void SimpleControlManager::setSimpleMovementListener( ISimpleMovementListener * _movementListener )
{
	movementListener = _movementListener;
}

void SimpleControlManager::iterate()
{
	SimpleInputStateSnapshot * s = new SimpleInputStateSnapshot( inputReceiver );
	videosystem::vector3df rot = videoPanel->getCamera()->getRotaition();
	s->dirX = rot.x;
	s->dirY = rot.y;
	s->dirZ = rot.z;

	if ( movementListener ) {
		bool movementRequestedLocal = (s->forward || s->backward || s->left || s->right);
		if ( movementRequestedLocal && !movementRequest ) {
			movementRequest = true;
			movementListener->notifyMovementPressed();
		}
		else if ( !movementRequestedLocal && movementRequest ) {
			movementRequest = false;
			movementListener->notifyMovementReleased();
		}
	}

	if ( (prevShot == 0) || s->isUpdateTo( *prevShot ) ) {
		if (prevShot != 0) 
			delete prevShot;
		prevShot = s;

		InnerObjectUserActionState * ss = new InnerObjectUserActionState();
		ss->forward = prevShot->forward;
		ss->backward = prevShot->backward;
		ss->left = prevShot->left;
		ss->right = prevShot->right;
		ss->dirX = prevShot->dirX;
		ss->dirY = prevShot->dirY;
		ss->dirZ= prevShot->dirZ;
		ss->time = prevShot->time;

		videoPanel->send( ss, communications::NET_COMPONENT_ID );
	}
}