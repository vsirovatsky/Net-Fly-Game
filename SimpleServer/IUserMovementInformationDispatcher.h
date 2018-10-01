#pragma once

#include "SimpleServerTypeDefs.h"
#include "SimpleNetMessages.h"

namespace simpleserver {

class UserMovementInformation {
public:
	UserMovementInformation(bool _forward, bool _backward, bool _left, bool _right, SERVER_FLOAT _dirX, SERVER_FLOAT _dirY, SERVER_FLOAT _dirZ, long _time) : 
		forward(_forward), backward(_backward), left(_left), right(_right), dirX(_dirX), dirY(_dirY), dirZ(_dirZ), time(_time) {}
	~UserMovementInformation(){}
	bool forward;
	bool backward;
	bool left;
	bool right;
	SERVER_FLOAT dirX;
	SERVER_FLOAT dirY;
	SERVER_FLOAT dirZ;
	long time;
};

class IUserMovementInformationProcessor {
public:
	IUserMovementInformationProcessor(){}
	virtual ~IUserMovementInformationProcessor(){}

	virtual void process( UserMovementInformation * ) = 0;
};

class IUserMovementInformationDispatcher {
public:
	IUserMovementInformationDispatcher(){}
	virtual ~IUserMovementInformationDispatcher(){}

	virtual void process( OBJECT_IDENTITY, UserMovementInformation * ) = 0;
};

}