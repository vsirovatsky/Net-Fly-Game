#include "NetSystemServerManager.h"
#include <iostream>

namespace netsystem {

using namespace RakNet;

NetSystemServerManager::NetSystemServerManager(void)
{
	prototypesContainer = 0;
	messageDispatcher = 0;
	rPeer = 0;
}

NetSystemServerManager::~NetSystemServerManager(void)
{
	RakNet::RakPeerInterface::DestroyInstance(rPeer);
}

void NetSystemServerManager::startUp( NS_INT port, NS_INT numberOfConnections, NS_INT numberOfAllowedConnections )
{
	try {
		//if ( this->rPeer == 0 ) {
		rPeer = RakNet::RakPeerInterface::GetInstance();
		//}
		if (this->rPeer->IsActive()) {
			throw new NetSystemException("Allready connected, disconnect first");
		}
		RakNet::SocketDescriptor socketDescriptor( port,0 );
		rPeer->SetIncomingPassword("5432112345",10);
		RakNet::StartupResult res = rPeer->Startup( numberOfConnections, &socketDescriptor, 1 );
		rPeer->SetMaximumIncomingConnections(numberOfAllowedConnections); 
		if ( res != RakNet::RAKNET_STARTED ) {
			NS_STRING mess("Cannot start server on port: ");
			mess.append( ""+port );
			throw new NetSystemException( mess );
		}
	} catch (NetSystemException * ex) {
		throw ex;
	} catch (...) {
		throw new NetSystemException("Unknown exception in connecting to server");
	}
}

void NetSystemServerManager::shutDown()
{
	//How many to wait to receive all messages (0 - not wait)
	rPeer->Shutdown(0);
}


void NetSystemServerManager::sendReliable( NetServerMessage & message )
{
	PRINTDEBUG( "sendReliable called: ", &message );
	BitStream * bs = new BitStream();
	message.data->serialize( bs );
	this->rPeer->Send(bs, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, 0, message.guid, message.broadcast);
}

void NetSystemServerManager::sendFast( NetServerMessage & message )
{
	PRINTDEBUG( "sendFast called: ", &message );
	BitStream * bs = new BitStream();
	message.data->serialize( bs );
	this->rPeer->Send(bs, PacketPriority::MEDIUM_PRIORITY, PacketReliability::UNRELIABLE, 0, message.guid, message.broadcast);
}

void NetSystemServerManager::obtain()
{
	NS_SERVER_MESSAGES_LIST result = NS_SERVER_MESSAGES_LIST();
	Packet *packet;
	for (packet=rPeer->Receive(); packet; rPeer->DeallocatePacket(packet), packet=rPeer->Receive()){
		unsigned char type = getPacketIdentifier( packet );
		switch (type) {
		case ID_NEW_INCOMING_CONNECTION:
			{
			NetServerMessage mess( NS_SYSTEM_SERVER_MESSAGE_CONNECTED, packet->guid );
			PRINTDEBUG( "obained: ", &mess );
			result.push_back( mess );
			break;
			}
		case ID_CONNECTION_LOST:
		case ID_DISCONNECTION_NOTIFICATION:
			{
			NetServerMessage mess( NS_SYSTEM_SERVER_MESSAGE_DISCONNECTED, packet->guid );
			PRINTDEBUG( "obained: ", &mess );
			result.push_back( mess );
			break;
			}
		default:
			if ( type >= ID_USER_PACKET_ENUM ) {
				BitStream stream(packet->data, packet->length, false);
				NetServerMessage mess( type, packet->guid );
				mess.data = prototypesContainer->create( type );
				mess.data->deserialize( &stream );
				PRINTDEBUG( "obained: ", &mess );
				result.push_back( mess );
			}
		}
	}
	messageDispatcher->dispatch( result );
}

unsigned char NetSystemServerManager::getPacketIdentifier(Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	else
		return (unsigned char) p->data[0];
}

}