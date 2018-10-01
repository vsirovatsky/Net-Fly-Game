#pragma once

#include "CommunicationsMessage.h"
#include "SimpleNetMessages.h"
#include <vector>

#define MESSAGE_TYPE_INNERPING 2
#define MESSAGE_TYPE_STARTUP_VIDEO 3
#define MESSAGE_TYPE_OBJECT_LOCATION 4
#define MESSAGE_TYPE_USER_ACTION_STATE 5
#define MESSAGE_TYPE_ANOTHER_USER_STATUS_CHANGED 6

#define MESSAGE_TYPE_SOUND_RESOURCE_RESOLVE 100
#define MESSAGE_TYPE_SOUND_RESOURCE_RESPONCE 101
#define MESSAGE_TYPE_SOUND_SINGLE_PLAY 102
#define MESSAGE_TYPE_SOUND_OBJECT_INFO 103
#define MESSAGE_TYPE_SOUND_USER_POSITION 104

namespace simpleclient {

class InnerPingMessage : public communications::IMessage
{
public:
	InnerPingMessage() : communications::IMessage() {}
	virtual ~InnerPingMessage(void){
		PRINTDEBUG( "Innerping: ", "message destroyed" );
	};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_INNERPING;};
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "Message: " << "Innerping";
		return ss.str();
	};
};

class InnerObjectStartUpVideoMessage : public communications::IMessage
{
public:
	InnerObjectStartUpVideoMessage() : communications::IMessage() {}
	virtual ~InnerObjectStartUpVideoMessage(void){PRINTDEBUG("deleted: ",printMe());};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_STARTUP_VIDEO;};
	unsigned long objectIdentity;
	float x;
	float y;
	float z;
	long timeDiffWithServer;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "StartUpVideoMessage: " << "objectIdentity: " << objectIdentity << ", (x,y,z): (" << x << ',' << y << ',' << z << ')';
		return ss.str();
	};
};

class InnerObjectLocationMessage : public communications::IMessage
{
public:
	InnerObjectLocationMessage() : communications::IMessage() {}
	virtual ~InnerObjectLocationMessage(void){};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_OBJECT_LOCATION;};
	std::vector<OBJECT_IDENTITY> objects;
	std::vector<long> currentTimes;
	std::vector<float> currentPositions;
	std::vector<float> nextPositions1;
	std::vector<float> nextPositions2;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerObjectLocationMessage: NONE YET";
		return ss.str();
	};
};

class InnerObjectUserActionState : public communications::IMessage
{
public:
	InnerObjectUserActionState() : communications::IMessage() {}
	virtual ~InnerObjectUserActionState(void){};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_USER_ACTION_STATE;};
	bool forward;
	bool backward;
	bool left;
	bool right;
	float dirX;
	float dirY;
	float dirZ;
	long time;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerObjectUserActionState: " << ", (x,y,z): (" << dirX << ',' << dirY << ',' << dirZ << ')';
		return ss.str();
	};
};

class InnerObjectAnotherUserStatusChanged : public communications::IMessage
{
public:
	InnerObjectAnotherUserStatusChanged() : communications::IMessage() {}
	virtual ~InnerObjectAnotherUserStatusChanged(void){};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_ANOTHER_USER_STATUS_CHANGED;};
	OBJECT_IDENTITY userId;
	bool userConnceted;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerObjectAnotherUserStatusChanged: " << "userId: " << userId << ", userConnceted: " << userConnceted;
		return ss.str();
	};
};

}