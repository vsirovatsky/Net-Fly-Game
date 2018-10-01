#pragma once

#include "SimpleServerTypeDefs.h"
#include "IUserMovementInformationDispatcher.h"

namespace simpleserver {

class MovementState {
public:
	MovementState() : dirty(true) {};
	virtual ~MovementState(){};

	vector3df positionCurrent;
	SERVER_TIME timeCurrent;

	vector3df positionNext1;

	vector3df positionNext2;

	void setAllPositions( float x, float y, float z ){
		positionCurrent.x = x;
		positionCurrent.y = y;
		positionCurrent.z = z;

		positionNext1.x = x;
		positionNext1.y = y;
		positionNext1.z = z;

		positionNext2.x = x;
		positionNext2.y = y;
		positionNext2.z = z;
	}

	bool dirty;
};

class SingleForce 
{
public:
	SingleForce() : direction(0,0,0), force(0) {}
	SingleForce( float _force, vector3df _direction ) : force(_force), direction(_direction) {}
	~SingleForce(){}
	vector3df direction;
	float force;
};

class SimpleMovementProcessor
{
public:
	SimpleMovementProcessor(void);
	~SimpleMovementProcessor(void);

	virtual void processNextInputState( UserMovementInformation * );
	void calculateMovement( MovementState & state );

private:
	void updateSnapshot( UserMovementInformation * );
	void populateTotalForce( SingleForce & );
	void modifyForces( UserMovementInformation * );
private:
	UserMovementInformation * currentSnapshot;
	vector3df nextPos;

	float forwardForce;
	float sideForce;
	float backwardForce;
	float weight;

	float currentVelocity;
	vector3df currentDirection;

	std::vector<SingleForce> forces;
	long prevTime;
};

class MovementObjectController : public IUserMovementInformationProcessor {
public:
	MovementObjectController();
	virtual ~MovementObjectController();

	virtual void setPositionForced(float, float, float);

	void iterate();
	void obtainYourselfStrategy( MOVEMENT_STRATEGY_TYPE );

	bool isDirty(){return state.dirty;}
	void setDirty(bool _dirty){state.dirty = _dirty;}
	MovementState & getState();

	// from IUserMovementInformationProcessor
	virtual void process( UserMovementInformation * );
private:
	MovementState state;
	MOVEMENT_STRATEGY_TYPE movementType;

	SimpleMovementProcessor * simpleMovementProcessor;
};

}