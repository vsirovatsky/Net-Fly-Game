#pragma once;
#include "Logger.h"
#include "communicationsTypeDefs.h"

#define DEFAULT_LOGGABLE_INNER_MESSAGE "inner message UNSPECIFIED"

namespace communications {

// Interface for all communications messages
class IMessage : public common::ILogable {
public:
	IMessage(void){};
	virtual ~IMessage(void){};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_BLANK;};
	virtual COMMON_STRING printMe() const {return DEFAULT_LOGGABLE_INNER_MESSAGE;};
};

// Simple base message
class TextMessage : public IMessage
{
public:
	TextMessage( PC_STRING mesV ) : IMessage(), mes(mesV) {};
	virtual ~TextMessage(void){};
	PC_STRING getMessage(){return mes;};
	virtual PC_MESSAGE_TYPE getType(){return MESSAGE_TYPE_TEXT;};
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "TextMessage: " << mes;
		return ss.str();
	};
private:
	PC_STRING mes;
};

class Envelope : public common::ILogable {
public:
	COMPONENT_IDS sender;
	COMPONENT_IDS receiver;
	IMessage * message;
	bool deleteMessage; // Explicitly specify FALSE if message should not be deleted
	Envelope( COMPONENT_IDS senderV, COMPONENT_IDS receiverV, IMessage * messageV) : sender(senderV), receiver(receiverV), message(messageV), deleteMessage(true) {}
	~Envelope()
	{
		if (deleteMessage)
			delete message;
	}
	virtual COMMON_STRING printMe() const {
		std::stringstream ss;
		ss << "Envelope: (" << sender << "->" << receiver << ") contents: ";
		if (message!=0)
			ss << message->printMe();
		else
			ss << 0;
		return ss.str();
	};
};

#define PC_ENVELOPES_LIST std::vector<Envelope *>
#define PC_MESSAGES_LIST std::vector<IMessage *>

}