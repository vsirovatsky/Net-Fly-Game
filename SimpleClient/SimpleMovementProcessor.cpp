#include "StdAfx.h"
#include "SimpleMovementProcessor.h"

using namespace simpleclient;

SimpleMovementProcessor::SimpleMovementProcessor(void) : nextPos(0,0,0), currentSnapshot(0)
{
	forwardForce = 1200;
	sideForce = 400;
	backwardForce = 200;
	weight = 10;
	currentVelocity = 0;
	prevTime = 0;
}


SimpleMovementProcessor::~SimpleMovementProcessor(void)
{
}

void SimpleMovementProcessor::processNextInputState( SimpleInputStateSnapshot * shot )
{
	calculateMovement();
	updateSnapshot( shot );
}

videosystem::vector3df & SimpleMovementProcessor::getNextPosition()
{
	return nextPos;
}

void SimpleMovementProcessor::populateTotalForce( SingleForce & totalForce )
{
	if ( forces.empty() )
		return;

	for ( std::vector<SingleForce>::iterator it = forces.begin(); it != forces.end(); ++it) {
		totalForce.direction.x += it->direction.x * it->force;
		totalForce.direction.y += it->direction.y * it->force;
		totalForce.direction.z += it->direction.z * it->force;
	}
	totalForce.force = totalForce.direction.length();
	if ( totalForce.force == 0 ) 
		return;
	totalForce.direction.x /= totalForce.force;
	totalForce.direction.y /= totalForce.force;
	totalForce.direction.z /= totalForce.force;
}

void SimpleMovementProcessor::updateSnapshot( SimpleInputStateSnapshot * newSnapshot )
{
	if ( currentSnapshot == 0 ) {
		currentSnapshot = newSnapshot;
		return;
	}
	if ( !newSnapshot->isUpdateTo(*currentSnapshot) )
		return;
	delete currentSnapshot;
	currentSnapshot = newSnapshot;
	forces.clear();
	if ( currentSnapshot->forward ) {
		forces.push_back( SingleForce( forwardForce, videosystem::vector3df(currentSnapshot->dirX, currentSnapshot->dirY, currentSnapshot->dirZ) ) );
	}
	if ( currentSnapshot->backward ) {
		forces.push_back( SingleForce( forwardForce, videosystem::vector3df(-currentSnapshot->dirX, -currentSnapshot->dirY, -currentSnapshot->dirZ) ) );
	}
	if ( currentSnapshot->left ) {
		//TODO: implement
	}
	if ( currentSnapshot->right ) {
		//TODO: implement
	}
}

void SimpleMovementProcessor::calculateMovement()
{
	if ( prevTime == 0 ) {
		prevTime = GetCurrentTime();
		return;
	}
	long newTime = GetCurrentTime();
	float deltaTime = (newTime - prevTime) / 1000.f;
	SingleForce totalForce;
	populateTotalForce( totalForce );

	videosystem::vector3df newMovement = videosystem::vector3df();

	float newAcceleratedVelocity = deltaTime * (totalForce.force / weight);

	newMovement.x = newAcceleratedVelocity * totalForce.direction.x + currentVelocity * currentDirection.x;
	newMovement.y = newAcceleratedVelocity * totalForce.direction.y + currentVelocity * currentDirection.y;
	newMovement.z = newAcceleratedVelocity * totalForce.direction.z + currentVelocity * currentDirection.z;

	currentVelocity = newMovement.length();
	currentDirection.x = (currentVelocity!=0) ? newMovement.x / currentVelocity : 0;
	currentDirection.y = (currentVelocity!=0) ? newMovement.y / currentVelocity : 0;
	currentDirection.z = (currentVelocity!=0) ? newMovement.z / currentVelocity : 0;

	nextPos.x += deltaTime * currentVelocity * currentDirection.x;
	nextPos.y += deltaTime * currentVelocity * currentDirection.y;
	nextPos.z += deltaTime * currentVelocity * currentDirection.z;

	prevTime = newTime;
}