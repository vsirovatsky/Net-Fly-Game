#pragma once

#include "Logger.h"
#include "IMovementProcessor.h"
#include <vector>

namespace simpleclient {

class SingleForce 
{
public:
	SingleForce() : direction(0,0,0), force(0) {}
	SingleForce( float _force, videosystem::vector3df _direction ) : force(_force), direction(_direction) {}
	~SingleForce(){}
	videosystem::vector3df direction;
	float force;
};

class SimpleMovementProcessor
{
public:
	SimpleMovementProcessor(void);
	~SimpleMovementProcessor(void);

	virtual void processNextInputState( SimpleInputStateSnapshot * );
	virtual videosystem::vector3df & getNextPosition();
private:
	void calculateMovement();
	void updateSnapshot( SimpleInputStateSnapshot * );
	void populateTotalForce( SingleForce & );
	void modifyForces( SimpleInputStateSnapshot * );
private:
	videosystem::vector3df nextPos;
	SimpleInputStateSnapshot * currentSnapshot;

	float forwardForce;
	float sideForce;
	float backwardForce;
	float weight;

	float currentVelocity;
	videosystem::vector3df currentDirection;

	std::vector<SingleForce> forces;
	long prevTime;
};

}