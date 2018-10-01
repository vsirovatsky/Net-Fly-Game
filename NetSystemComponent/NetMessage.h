#pragma once

#include "Logger.h"
#include "netSystemTypeDefs.h"
#include <vector>
#include <hash_map>

#define DEFAULT_LOGGABLE_SERIALIZABLE_MESSAGE "serializable UNSPECIFIED"
#define DEFAULT_LOGGABLE_CLIENT_SYSTEM_MESSAGE "default network client system message"
#define DEFAULT_LOGGABLE_SERVER_SYSTEM_MESSAGE "default network server system message"

namespace netsystem {

class NS_Serializable : public common::ILogable {
public:
	NS_Serializable(){}
	virtual ~NS_Serializable(){}
	virtual NS_Serializable * clone() {return 0;}
	virtual void serialize( NS_SERIALIZE_STREAM * stream ){}
	virtual void deserialize( NS_SERIALIZE_STREAM * stream ){}
	virtual COMMON_STRING printMe() const {return DEFAULT_LOGGABLE_SERIALIZABLE_MESSAGE;};
};

// When sending NS_MESSAGE_TYPE type from here not used
struct NetMessage : public common::ILogable {
public:
	// For sending:
	NetMessage() : type(), data(0) {}
	// For receiving:
	NetMessage( NS_MESSAGE_TYPE _type ) : type(_type), data(0) {}
	NS_MESSAGE_TYPE type;
	NS_Serializable * data;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "NetMessage(client): type: " << type << ", contents: ";
		if (data!=0)
			ss << data->printMe();
		else
			ss << 0;
		return ss.str();
	};
};

// When sending NS_MESSAGE_TYPE type from here not used
struct NetServerMessage : public common::ILogable {
public:
	// For sending:
	NetServerMessage( NS_GUID _guid ) : guid(_guid), broadcast(false), data(0) {}
	// For receiving:
	NetServerMessage( NS_MESSAGE_TYPE _type, NS_GUID _guid ) : type(_type), guid(_guid), broadcast(false), data(0) {}
	NS_MESSAGE_TYPE type;
	bool broadcast;
	NS_GUID guid;
	NS_Serializable * data;
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "NetMessage(server): type: " << type << ", guid: " << guid.g << ", broadcast: " << broadcast << ", contents: ";
		if (data!=0)
			ss << data->printMe();
		else
			ss << 0;
		return ss.str();
	};
};

#define NS_CUSTOM_MESSAGE_START 113

#define NS_SYSTEM_CLIENT_MESSAGE_CONNECTED 1
#define NS_SYSTEM_CLIENT_MESSAGE_CONNECTION_FAILED 2
#define NS_SYSTEM_CLIENT_MESSAGE_DISCONNECTED 3
class NetSystemMessage : public NS_Serializable {
public:
	NetSystemMessage() : mess(""), NS_Serializable() {}
	NetSystemMessage( NS_STRING _mess ) : mess(_mess), NS_Serializable() {}
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << DEFAULT_LOGGABLE_CLIENT_SYSTEM_MESSAGE << ": " << mess;
		return ss.str();
	};
	NS_STRING mess;
};

#define NS_SYSTEM_SERVER_MESSAGE_CONNECTED 1
#define NS_SYSTEM_SERVER_MESSAGE_DISCONNECTED 2
class NetSystemServerMessage : public NS_Serializable {
public:
	NetSystemServerMessage() : NS_Serializable() {}
	virtual COMMON_STRING printMe() const {return DEFAULT_LOGGABLE_SERVER_SYSTEM_MESSAGE;};
};


#define NS_MESSAGES_LIST std::vector<NetMessage>
#define NS_SERVER_MESSAGES_LIST std::vector<NetServerMessage>

class NSSerializablePrototypesContainer {
public:
	NSSerializablePrototypesContainer(){};
	virtual NS_Serializable * create( NS_MESSAGE_TYPE type ) = 0;
	virtual ~NSSerializablePrototypesContainer(){}

};


// Client Dispatchers:
class NSIClientCustomMessageProcessor {
public:
	NSIClientCustomMessageProcessor(){}
	virtual ~NSIClientCustomMessageProcessor(){};
	virtual void process( NS_Serializable * data ) = 0;
	virtual NS_MESSAGE_TYPE getType() = 0;
};

class NSIClientSystemMessageProcessor {
public:
	NSIClientSystemMessageProcessor(){}
	virtual ~NSIClientSystemMessageProcessor(){};
	virtual void process( NS_Serializable * data ) = 0;
	virtual NS_MESSAGE_TYPE getType() = 0;
};

class NSAbstractClientMessagesDispatcher {
public:
	NSAbstractClientMessagesDispatcher();
	virtual ~NSAbstractClientMessagesDispatcher();

	virtual void dispatch( NS_MESSAGES_LIST & messages );
	virtual void registerCustomProcessor( NSIClientCustomMessageProcessor * );
	virtual void registerCustomDefaultProcessor( NSIClientCustomMessageProcessor * );
	virtual void registerSystemProcessor( NSIClientSystemMessageProcessor * );
	virtual void registerSystemDefaultProcessor( NSIClientSystemMessageProcessor * );
private:
	std::hash_map<NS_MESSAGE_TYPE, NSIClientCustomMessageProcessor*> regCustom;
	std::hash_map<NS_MESSAGE_TYPE, NSIClientSystemMessageProcessor*> regSystem;
	NSIClientCustomMessageProcessor * defaultCustomProcessor;
	NSIClientSystemMessageProcessor * defaultSystemProcessor;
};

// Server Dispatchers:
class NSIServerCustomMessageProcessor {
public:
	NSIServerCustomMessageProcessor(){}
	virtual ~NSIServerCustomMessageProcessor(){};
	virtual void process( NetServerMessage & mess ) = 0;
	virtual NS_MESSAGE_TYPE getType() = 0;
};

class NSIServerSystemMessageProcessor {
public:
	NSIServerSystemMessageProcessor(){}
	virtual ~NSIServerSystemMessageProcessor(){};
	virtual void process( NetServerMessage & mess ) = 0;
	virtual NS_MESSAGE_TYPE getType() = 0;
};

class NSAbstractServerMessagesDispatcher {
public:
	NSAbstractServerMessagesDispatcher();
	virtual ~NSAbstractServerMessagesDispatcher();

	virtual void dispatch( NS_SERVER_MESSAGES_LIST & messages );
	virtual void registerCustomProcessor( NSIServerCustomMessageProcessor * );
	virtual void registerCustomDefaultProcessor( NSIServerCustomMessageProcessor * );
	virtual void registerSystemProcessor( NSIServerSystemMessageProcessor * );
	virtual void registerSystemDefaultProcessor( NSIServerSystemMessageProcessor * );
private:
	std::hash_map<NS_MESSAGE_TYPE, NSIServerCustomMessageProcessor*> regCustom;
	std::hash_map<NS_MESSAGE_TYPE, NSIServerSystemMessageProcessor*> regSystem;
	NSIServerCustomMessageProcessor * defaultCustomProcessor;
	NSIServerSystemMessageProcessor * defaultSystemProcessor;
};

}