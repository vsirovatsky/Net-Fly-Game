#pragma once

#include "netSystemTypeDefs.h"
#include "NetSystemException.h"
#include "RakPeerInterface.h"
#include "NetSystemAbstractManager.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"

namespace netsystem {

class NetSystemManager : public NetSystemAbstractManager
{
public:
	NetSystemManager(void);
	virtual ~NetSystemManager(void);

	virtual void connect(NS_STRING ip, NS_INT port);
	virtual void disconnect();
	virtual bool isConnected();

	virtual void sendReliable( NetMessage & message );
	virtual void sendFast( NetMessage & message );

	virtual void obtain();

	virtual void setNSSerializablePrototypesContainer( NSSerializablePrototypesContainer * prototypesContainer ){this->prototypesContainer = prototypesContainer;}
	virtual void setNSClientMessagesDispatcher( NSAbstractClientMessagesDispatcher * dispatcher ){this->messageDispatcher = dispatcher;}

	virtual void setDebug( bool debug );
private:
	bool m_debug;
	RakNet::RakPeerInterface * rPeer;
	NSSerializablePrototypesContainer * prototypesContainer;
	NSAbstractClientMessagesDispatcher * messageDispatcher;
	inline unsigned char getPacketIdentifier(RakNet::Packet *p);
};

}