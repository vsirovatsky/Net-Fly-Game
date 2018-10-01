#pragma once

#include "commonTypeDefs.h"
#include "SimpleClientTypeDefs.h"
#include "SimpleClientMessage.h"

namespace simpleclient {

class SoundInformation {
public:
	SoundInformation() : create(false), remove(false), start(false), stop(false), pos(), objId(OBJECT_IDENTITY_NOT_FOUND) {};
	~SoundInformation(){};
	OBJECT_IDENTITY objId;
	COMMON_STRING resourceId;
	COMMON_STRING soundId;
	bool create;
	bool remove;
	bool start;
	bool stop;
	bool isWithSound() {return start || stop;}
	vector3df pos;
};

class InnerSoundMessage : public communications::IMessage 
{
public:
	InnerSoundMessage() : communications::IMessage() {}
	~InnerSoundMessage(){}
	virtual COMMON_STRING printMe() const {
		return "sound message UNSPECIFIED";
	};
};

class InnerSoundUserPosition : public InnerSoundMessage
{
public:
	InnerSoundUserPosition() : InnerSoundMessage() {}
	~InnerSoundUserPosition(){}
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_SOUND_USER_POSITION;};
	vector3df pos;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerSoundUserPosition: " << '(' << pos.x << ',' << pos.y << ',' << pos.z << ')';
		return ss.str();
	};
};

class InnerSoundPlayMessage : public communications::IMessage 
{
public:
	InnerSoundPlayMessage() : communications::IMessage() {}
	~InnerSoundPlayMessage(){}
	COMMON_STRING resourceId;
	COMMON_STRING soundId;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerSoundPlayMessage: " << "resourceId: " << resourceId << ", soundId: " << soundId;
		return ss.str();
	};
};

class InnerSoundObjectInfo : public InnerSoundPlayMessage
{
public:
	InnerSoundObjectInfo() : InnerSoundPlayMessage(), info() {}
	virtual ~InnerSoundObjectInfo(void){};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_SOUND_OBJECT_INFO;};
	SoundInformation info;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerSoundObjectInfo: id: " << info.objId << '(' << info.create << ',' << info.remove << ',' << info.start << ',' << info.stop << ')' << ", resourceId: " << info.resourceId << ", soundId: " << info.soundId << ", (x,y,z): (" << info.pos.x << ',' << info.pos.y << ',' << info.pos.z << ')';
		return ss.str();
	};
};

class InnerSoundSinglePlay : public InnerSoundPlayMessage
{
public:
	InnerSoundSinglePlay() : InnerSoundPlayMessage() {}
	virtual ~InnerSoundSinglePlay(void){};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_SOUND_SINGLE_PLAY;};
	// sound position
	float x;
	float y;
	float z;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerSoundSinglePlay: " << "resourceId: " << resourceId << ", soundId: " << soundId << ", (x,y,z): (" << x << ',' << y << ',' << z << ')';
		return ss.str();
	};
};

class InnerSoundResourceResolveRequest : public InnerSoundMessage
{
public:
	InnerSoundResourceResolveRequest() : InnerSoundMessage() {}
	~InnerSoundResourceResolveRequest() {}
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_SOUND_RESOURCE_RESOLVE;};
	InnerSoundPlayMessage * body;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerSoundResourceResolveRequest: " << "contens: ";
		if ( body != 0 ) 
			ss << body->printMe();
		else
			ss << 0;
		return ss.str();
	};
};

class InnerSoundResourceResolveResponce : public InnerSoundMessage
{
public:
	InnerSoundResourceResolveResponce() : InnerSoundMessage() {}
	~InnerSoundResourceResolveResponce() {}
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_SOUND_RESOURCE_RESPONCE;};
	InnerSoundPlayMessage * body;
	COMMON_STRING resource;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "InnerSoundResourceResolveRequest: " << "resource: " << resource << ", contens: ";
		if ( body != 0 ) 
			ss << body->printMe();
		else
			ss << 0;
		return ss.str();
	};
};

}