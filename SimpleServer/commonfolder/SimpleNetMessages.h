#pragma once

#include "NetMessage.h"
#include "SimpleNetTypes.h"
#include <map>
#include <vector>

using namespace netsystem;

#define OBJECT_IDENTITY unsigned long
#define OBJECT_IDENTITY_NOT_FOUND 0

#define USER_STATE unsigned char
#define SIMPLE_LOGICAL bool

#define USER_STATE_ONLINE 1
#define USER_STATE_OFFLINE 2

#define SIMPLE_MESSAGE_USER_STATE_CHANGED 113
#define SIMPLE_MESSAGE_USER_INFO 114
#define SIMPLE_MESSAGE_OBJECT_LOCATION 115
#define SIMPLE_MESSAGE_USER_ACTION_STATE 116
#define SIMPLE_MESSAGE_OBJECTS_STATES_UPDATE 117


class MessageBodyUserState : public NS_Serializable {
public:
	MessageBodyUserState(){}
	MessageBodyUserState(OBJECT_IDENTITY nType) : type(SIMPLE_MESSAGE_USER_STATE_CHANGED), obj(nType) {}
	MessageBodyUserState(OBJECT_IDENTITY nType, USER_STATE nPrevious, USER_STATE nNext ) : type(SIMPLE_MESSAGE_USER_STATE_CHANGED), obj(nType), previous(nPrevious), next(nNext) {}
	virtual ~MessageBodyUserState(){}
	void serialize( NS_SERIALIZE_STREAM * stream ){
		NS_WRITE(stream, type);
		NS_WRITE(stream, obj);
		NS_WRITE(stream, previous);
		NS_WRITE(stream, next);
	}
	void deserialize( NS_SERIALIZE_STREAM * stream ) {
		NS_READ(stream, type);
		NS_READ(stream, obj);
		NS_READ(stream, previous);
		NS_READ(stream, next);
	}
	virtual NS_Serializable * clone()
	{
		return new MessageBodyUserState();
	}
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "MessageBodyUserState: " << "OBJECT_IDENTITY: " << obj << ", previous USER_STATE: " << previous << ", next USER_STATE: " << next;
		return ss.str();
	}
public:
	NS_MESSAGE_TYPE type;
	OBJECT_IDENTITY obj;
	USER_STATE previous;
	USER_STATE next;
};

// Setup info for user
class MessageBodyUserInfo : public NS_Serializable {
public:
	MessageBodyUserInfo(){}
	MessageBodyUserInfo(OBJECT_IDENTITY nObj) : type(SIMPLE_MESSAGE_USER_INFO), obj(nObj) {}
	MessageBodyUserInfo(OBJECT_IDENTITY nObj, long _serverCurrentTime, NS_FLOAT nx, NS_FLOAT ny, NS_FLOAT nz ) : type(SIMPLE_MESSAGE_USER_INFO), obj(nObj), serverCurrentTime(_serverCurrentTime), x(nx), y(ny), z(nz) {}
	virtual ~MessageBodyUserInfo(){}
	void serialize( NS_SERIALIZE_STREAM * stream ){
		NS_WRITE(stream, type);
		NS_WRITE(stream, obj);
		NS_WRITE(stream, serverCurrentTime);
		NS_WRITE(stream, x);
		NS_WRITE(stream, y);
		NS_WRITE(stream, z);
	}
	void deserialize( NS_SERIALIZE_STREAM * stream ) {
		NS_READ(stream, type);
		NS_READ(stream, obj);
		NS_READ(stream, serverCurrentTime);
		NS_READ(stream, x);
		NS_READ(stream, y);
		NS_READ(stream, z);
	}
	virtual NS_Serializable * clone()
	{
		return new MessageBodyUserInfo();
	}
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "MessageBodyUserInfo: " << "OBJECT_IDENTITY: " << obj << ", time: " << serverCurrentTime << ", x: " << x << ", y: " << y << ", z: " << z;
		return ss.str();
	}
public:
	NS_MESSAGE_TYPE type;
	OBJECT_IDENTITY obj;
	long serverCurrentTime;
	NS_FLOAT x;
	NS_FLOAT y;
	NS_FLOAT z;
};

class MessageBodyObjectLocation : public NS_Serializable {
public:
	MessageBodyObjectLocation(){}
	MessageBodyObjectLocation(OBJECT_IDENTITY nObj) : type(SIMPLE_MESSAGE_OBJECT_LOCATION), obj(nObj) {}
	MessageBodyObjectLocation(OBJECT_IDENTITY nObj, NS_FLOAT nx, NS_FLOAT ny, NS_FLOAT nz ) : type(SIMPLE_MESSAGE_OBJECT_LOCATION), obj(nObj), x(nx), y(ny), z(nz) {}
	virtual ~MessageBodyObjectLocation(){}
	void serialize( NS_SERIALIZE_STREAM * stream ){
		NS_WRITE(stream, type);
		NS_WRITE(stream, obj);
		NS_WRITE(stream, x);
		NS_WRITE(stream, y);
		NS_WRITE(stream, z);
	}
	void deserialize( NS_SERIALIZE_STREAM * stream ) {
		NS_READ(stream, type);
		NS_READ(stream, obj);
		NS_READ(stream, x);
		NS_READ(stream, y);
		NS_READ(stream, z);
	}
	virtual NS_Serializable * clone()
	{
		return new MessageBodyObjectLocation();
	}
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "MessageBodyObjectLocation: " << "OBJECT_IDENTITY: " << obj << ", x: " << x << ", y: " << y << ", z: " << z;
		return ss.str();
	}
public:
	NS_MESSAGE_TYPE type;
	OBJECT_IDENTITY obj;
	NS_FLOAT x;
	NS_FLOAT y;
	NS_FLOAT z;
};

class MessageBodyUserAction : public NS_Serializable {
public:
	MessageBodyUserAction() : type(SIMPLE_MESSAGE_USER_ACTION_STATE) {}
	MessageBodyUserAction( bool _forward, bool _backward, bool _left, bool _right, NS_FLOAT _dirX, NS_FLOAT _dirY, NS_FLOAT _dirZ, long _time ) : type(SIMPLE_MESSAGE_USER_ACTION_STATE),
		forward(_forward), backward(_backward), left(_left), right(_right), dirX(_dirX), dirY(_dirY), dirZ(_dirZ), time(_time) {}
	virtual ~MessageBodyUserAction(){}
	void serialize( NS_SERIALIZE_STREAM * stream ){
		NS_WRITE(stream, type);
		NS_WRITE(stream, forward);
		NS_WRITE(stream, backward);
		NS_WRITE(stream, left);
		NS_WRITE(stream, right);
		NS_WRITE(stream, dirX);
		NS_WRITE(stream, dirY);
		NS_WRITE(stream, dirZ);
		NS_WRITE(stream, time);
	}
	void deserialize( NS_SERIALIZE_STREAM * stream ) {
		NS_READ(stream, type);
		NS_READ(stream, forward);
		NS_READ(stream, backward);
		NS_READ(stream, left);
		NS_READ(stream, right);
		NS_READ(stream, dirX);
		NS_READ(stream, dirY);
		NS_READ(stream, dirZ);
		NS_READ(stream, time);
	}
	virtual NS_Serializable * clone()
	{
		return new MessageBodyUserAction();
	}
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "MessageBodyUserAction: " << "forward: " << forward << ", backward: " << backward << ", left: " << left << ", right: " << right
			<< ", dirX: " << dirX << ", dirY: " << dirY << ", dirZ: " << dirZ << ", time: " << time;
		return ss.str();
	}
public:
	NS_MESSAGE_TYPE type;
	bool forward;
	bool backward;
	bool left;
	bool right;
	NS_FLOAT dirX;
	NS_FLOAT dirY;
	NS_FLOAT dirZ;
	long time;

};

class MessageBodyObjectsStatesUpdate : public NS_Serializable {
public:
	MessageBodyObjectsStatesUpdate() : type(SIMPLE_MESSAGE_OBJECTS_STATES_UPDATE) {}
	virtual ~MessageBodyObjectsStatesUpdate(){}
	void serialize( NS_SERIALIZE_STREAM * stream ){
		NS_WRITE(stream, type);
		NS_WRITE(stream, objects.size());
		for( std::vector<OBJECT_IDENTITY>::iterator it = objects.begin(); it != objects.end(); ++it ){
			NS_WRITE(stream, *it);
		}
		for( std::vector<long>::iterator it = currentTimes.begin(); it != currentTimes.end(); ++it ){
			NS_WRITE(stream, *it);
		}
		for( std::vector<float>::iterator it = currentPositions.begin(); it != currentPositions.end(); ++it ){
			NS_WRITE(stream, *it);
		}
		for( std::vector<float>::iterator it = nextPositions1.begin(); it != nextPositions1.end(); ++it ){
			NS_WRITE(stream, *it);
		}
		for( std::vector<float>::iterator it = nextPositions2.begin(); it != nextPositions2.end(); ++it ){
			NS_WRITE(stream, *it);
		}
	}
	void deserialize( NS_SERIALIZE_STREAM * stream ) {
		NS_READ(stream, type);
		int size = 0;
		NS_READ(stream, size);
		for ( int i = 0; i < size; ++i ) {
			OBJECT_IDENTITY id; 
			NS_READ(stream, id);
			objects.push_back( id );
		}
		for ( int i = 0; i < size; ++i ) {
			long currTime; 
			NS_READ(stream, currTime);
			currentTimes.push_back( currTime );
		}
		size *= 3;
		for ( int i = 0; i < size; ++i ) {
			float pos; 
			NS_READ(stream, pos);
			currentPositions.push_back( pos );
		}
		for ( int i = 0; i < size; ++i ) {
			float pos; 
			NS_READ(stream, pos);
			nextPositions1.push_back( pos );
		}
		for ( int i = 0; i < size; ++i ) {
			float pos; 
			NS_READ(stream, pos);
			nextPositions2.push_back( pos );
		}
	}
	virtual NS_Serializable * clone()
	{
		return new MessageBodyObjectsStatesUpdate();
	}
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "MessageBodyObjectsStatesUpdate: " << "update for " << objects.size() << " objects ";
		return ss.str();
	}
public:
	NS_MESSAGE_TYPE type;
	std::vector<OBJECT_IDENTITY> objects;
	std::vector<long> currentTimes;
	std::vector<float> currentPositions;
	std::vector<float> nextPositions1;
	std::vector<float> nextPositions2;
};

class SerializablePrototypesSimpleContainer : public NSSerializablePrototypesContainer
{
private:
	std::map<NS_MESSAGE_TYPE, NS_Serializable*> reg;
public:
	SerializablePrototypesSimpleContainer()
	{
		reg.insert( std::pair<NS_MESSAGE_TYPE, NS_Serializable *>( SIMPLE_MESSAGE_USER_STATE_CHANGED, new MessageBodyUserState() ) );
		reg.insert( std::pair<NS_MESSAGE_TYPE, NS_Serializable *>( SIMPLE_MESSAGE_USER_INFO, new MessageBodyUserInfo() ) );
		reg.insert( std::pair<NS_MESSAGE_TYPE, NS_Serializable *>( SIMPLE_MESSAGE_OBJECT_LOCATION, new MessageBodyObjectLocation() ) );
		reg.insert( std::pair<NS_MESSAGE_TYPE, NS_Serializable *>( SIMPLE_MESSAGE_USER_ACTION_STATE, new MessageBodyUserAction() ) );
		reg.insert( std::pair<NS_MESSAGE_TYPE, NS_Serializable *>( SIMPLE_MESSAGE_OBJECTS_STATES_UPDATE, new MessageBodyObjectsStatesUpdate() ) );
	}
	virtual NS_Serializable * create( NS_MESSAGE_TYPE type )
	{
		return reg.find(type)->second->clone();
	}
};
