#include "StdAfx.h"
#include "MovementObjectController.h"
#include "SimpleServerException.h"
#include "Logger.h"

using namespace simpleserver;

#define TIME_STEP_IN_MOVEMENT 0.5f

MovementObjectController::MovementObjectController() : movementType(MOVEMENT_STRATEGY_BLANK), simpleMovementProcessor(0)
{	

}

MovementObjectController::~MovementObjectController()
{
	if ( simpleMovementProcessor!=0 ) {
		delete simpleMovementProcessor;
	}
}

void MovementObjectController::setPositionForced( float x, float y, float z )
{
	state.setAllPositions( x, y, z );
}

void MovementObjectController::obtainYourselfStrategy( MOVEMENT_STRATEGY_TYPE type )
{
	movementType = type;
	if ( movementType == MOVEMENT_STRATEGY_BLANK ) {
		if ( simpleMovementProcessor ) {
			delete simpleMovementProcessor;
			simpleMovementProcessor = 0;
		}
		state.setAllPositions( state.positionCurrent.x, state.positionCurrent.y, state.positionCurrent.z );
		state.timeCurrent = GetCurrentTime();
		return;
	}
	if ( movementType == MOVEMENT_STRATEGY_USER_FLY ) {
		if ( simpleMovementProcessor ) 
			delete simpleMovementProcessor;
		simpleMovementProcessor = new SimpleMovementProcessor();
		state.setAllPositions( state.positionCurrent.x, state.positionCurrent.y, state.positionCurrent.z );
		state.timeCurrent = GetCurrentTime();
	}
}

MovementState & MovementObjectController::getState()
{
	return state;
}

void MovementObjectController::iterate()
{
	if ( movementType == MOVEMENT_STRATEGY_BLANK ) 
		return;
	if ( movementType == MOVEMENT_STRATEGY_USER_FLY ) {
		simpleMovementProcessor->calculateMovement( state );
	}
}

void MovementObjectController::process( UserMovementInformation * info )
{
	if ( movementType == MOVEMENT_STRATEGY_BLANK ) 
		return;
	if ( movementType == MOVEMENT_STRATEGY_USER_FLY ) {
		if ( simpleMovementProcessor ) {
			state.dirty = true;
			simpleMovementProcessor->processNextInputState( info );
		}
	}
}



//SimpleMovementProcessor
SimpleMovementProcessor::SimpleMovementProcessor(void) : nextPos(0,0,0), currentSnapshot(0)
{
	forwardForce = 1200;
	sideForce = 400;
	backwardForce = 200;
	weight = 10;
	currentVelocity = 0;
	prevTime = GetCurrentTime();
}

SimpleMovementProcessor::~SimpleMovementProcessor(void)
{
	if ( currentSnapshot != 0 )
		delete currentSnapshot;
}

void SimpleMovementProcessor::processNextInputState( UserMovementInformation * shot )
{
	updateSnapshot( shot );
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

void SimpleMovementProcessor::updateSnapshot( UserMovementInformation * newSnapshot )
{
	if ( currentSnapshot == 0 ) {
		currentSnapshot = newSnapshot;
		return;
	}
	if ( currentSnapshot != 0 )
		delete currentSnapshot;
	currentSnapshot = newSnapshot;
	forces.clear();
	std::cout << "new newSnapshot " << newSnapshot->time << std::endl;
	if ( currentSnapshot->forward ) {
		forces.push_back( SingleForce( forwardForce, vector3df(currentSnapshot->dirX, currentSnapshot->dirY, currentSnapshot->dirZ) ) );
	}
	if ( currentSnapshot->backward ) {
		forces.push_back( SingleForce( forwardForce, vector3df(-currentSnapshot->dirX, -currentSnapshot->dirY, -currentSnapshot->dirZ) ) );
	}
	if ( currentSnapshot->left ) {
		//TODO: implement better
		forces.push_back( SingleForce( forwardForce, vector3df(currentSnapshot->dirX, currentSnapshot->dirY, currentSnapshot->dirZ).getLeftPerpendicularXY() ) );
	}
	if ( currentSnapshot->right ) {
		//TODO: implement better
		forces.push_back( SingleForce( forwardForce, vector3df(currentSnapshot->dirX, currentSnapshot->dirY, currentSnapshot->dirZ).getRightPerpendicularXY() ) );
	}
}

void SimpleMovementProcessor::calculateMovement( MovementState & state )
{
	long newTime = GetCurrentTime();

	float deltaTime = (newTime - prevTime)/ 1000.f;
	SingleForce totalForce;
	populateTotalForce( totalForce );

	vector3df newMovement = vector3df();

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

	//Making projections in time

	if ( state.dirty ) {
		state.timeCurrent = prevTime;
		state.positionCurrent.x = nextPos.x;
		state.positionCurrent.y = nextPos.y;
		state.positionCurrent.z = nextPos.z;

		state.positionNext1.x = state.positionCurrent.x + TIME_STEP_IN_MOVEMENT * currentVelocity * currentDirection.x;
		state.positionNext1.y = state.positionCurrent.y + TIME_STEP_IN_MOVEMENT * currentVelocity * currentDirection.y;
		state.positionNext1.z = state.positionCurrent.z + TIME_STEP_IN_MOVEMENT * currentVelocity * currentDirection.z;

		state.positionNext2.x = state.positionCurrent.x + (TIME_STEP_IN_MOVEMENT + TIME_STEP_IN_MOVEMENT) * currentVelocity * currentDirection.x;
		state.positionNext2.y = state.positionCurrent.y + (TIME_STEP_IN_MOVEMENT + TIME_STEP_IN_MOVEMENT) * currentVelocity * currentDirection.y;
		state.positionNext2.z = state.positionCurrent.z + (TIME_STEP_IN_MOVEMENT + TIME_STEP_IN_MOVEMENT) * currentVelocity * currentDirection.z;

		state.dirty = true;
	} else {
		if ( (state.timeCurrent + TIME_STEP_IN_MOVEMENT*1000.f) > prevTime ) {
			return;
		}
		state.timeCurrent = prevTime;
		//long timeCurrent = state.timeCurrent;
		//long timeNext1 = state.timeCurrent + TIME_STEP_IN_MOVEMENT;
		//long timeNext2 = state.timeCurrent + TIME_STEP_IN_MOVEMENT + TIME_STEP_IN_MOVEMENT;

		state.positionCurrent.x = nextPos.x;
		state.positionCurrent.y = nextPos.y;
		state.positionCurrent.z = nextPos.z;

		state.positionNext1.x = state.positionCurrent.x + TIME_STEP_IN_MOVEMENT * currentVelocity * currentDirection.x;
		state.positionNext1.y = state.positionCurrent.y + TIME_STEP_IN_MOVEMENT * currentVelocity * currentDirection.y;
		state.positionNext1.z = state.positionCurrent.z + TIME_STEP_IN_MOVEMENT * currentVelocity * currentDirection.z;

		state.positionNext2.x = state.positionCurrent.x + (TIME_STEP_IN_MOVEMENT + TIME_STEP_IN_MOVEMENT) * currentVelocity * currentDirection.x;
		state.positionNext2.y = state.positionCurrent.y + (TIME_STEP_IN_MOVEMENT + TIME_STEP_IN_MOVEMENT) * currentVelocity * currentDirection.y;
		state.positionNext2.z = state.positionCurrent.z + (TIME_STEP_IN_MOVEMENT + TIME_STEP_IN_MOVEMENT) * currentVelocity * currentDirection.z;

		state.dirty = true;
	}
}
