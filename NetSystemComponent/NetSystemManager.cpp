#include "NetSystemManager.h"

namespace netsystem {

using namespace RakNet;

NetSystemManager::NetSystemManager(void)
{
	prototypesContainer = 0;
	messageDispatcher = 0;
	rPeer = 0;
}

NetSystemManager::~NetSystemManager(void)
{
	RakNet::RakPeerInterface::DestroyInstance(rPeer);
}

void NetSystemManager::connect( NS_STRING ip, NS_INT port )
{
	try {
		rPeer = RakNet::RakPeerInterface::GetInstance();
		if (this->rPeer->IsActive()) {
			throw new NetSystemException("Allready connected, disconnect first");
		}
		RakNet::StartupResult res = rPeer->Startup(1,&SocketDescriptor(), 1);
		if ( res != RakNet::RAKNET_STARTED ) {
			NS_STRING mess("Cannot connect to ");
			mess.append( ip );
			throw new NetSystemException( mess );
		}
		ConnectionAttemptResult cRes = rPeer->Connect(ip.c_str(), port, "5432112345", 10);
		if ( (cRes == CONNECTION_ATTEMPT_STARTED) ) {

		} else if (cRes == ALREADY_CONNECTED_TO_ENDPOINT) {
			throw new NetSystemException("Allready connected, disconnect first");
		} else if (cRes == INVALID_PARAMETER) {
			throw new NetSystemException("Invalid parameters");
		} else if (cRes == CANNOT_RESOLVE_DOMAIN_NAME) {
			NS_STRING mess("Cannot resolve domain name");
			mess.append( ip );
			throw new NetSystemException( mess );
		} else if (cRes == CONNECTION_ATTEMPT_ALREADY_IN_PROGRESS) {

		} else if (cRes == SECURITY_INITIALIZATION_FAILED) {
			throw new NetSystemException("SECURITY_INITIALIZATION_FAILED");
		}
	} catch (NetSystemException * ex) {
		throw ex;
	} catch (NetSystemException ex) {
		throw ex;
	} catch (...) {
		throw new NetSystemException("Unknown exception in connecting to server");
	}
}

void NetSystemManager::disconnect()
{
	//How many to wait to receive all messages (0 - not wait)
	rPeer->Shutdown(0);
}

bool NetSystemManager::isConnected()
{
	if ( rPeer == 0 ) {
		return false;
	}
	RakNet::ConnectionState st = rPeer->GetConnectionState( RakNet::UNASSIGNED_SYSTEM_ADDRESS );
	return ( st!=RakNet::IS_NOT_CONNECTED ) && ( st!=RakNet::IS_DISCONNECTED ) && ( st!=RakNet::IS_DISCONNECTING ) && ( st!=RakNet::IS_SILENTLY_DISCONNECTING );
}

void NetSystemManager::sendReliable( NetMessage & message )
{
	BitStream * bs = new BitStream();
	message.data->serialize( bs );
	PRINTDEBUG( "sendReliable: ", &message );
	this->rPeer->Send(bs, PacketPriority::HIGH_PRIORITY, RELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
}

void NetSystemManager::sendFast( NetMessage & message )
{
	BitStream * bs = new BitStream();
	message.data->serialize( bs );
	PRINTDEBUG( "sendFast: ", &message );
	this->rPeer->Send(bs, PacketPriority::MEDIUM_PRIORITY, PacketReliability::UNRELIABLE, 0, RakNet::UNASSIGNED_RAKNET_GUID, true);
}

void NetSystemManager::obtain()
{
	NS_MESSAGES_LIST result = NS_MESSAGES_LIST();
	Packet *packet;
	for (packet=rPeer->Receive(); packet; rPeer->DeallocatePacket(packet), packet=rPeer->Receive()){
		unsigned char type = getPacketIdentifier( packet );
		switch (type) {
		case ID_CONNECTION_REQUEST_ACCEPTED:
			{
			NetMessage mess( NS_SYSTEM_CLIENT_MESSAGE_CONNECTED );
			mess.data = new NetSystemMessage("CONNECTION_REQUEST_ACCEPTED");
			PRINTDEBUG( "obtained: ", &mess );
			result.push_back( mess );
			}
			break;
		case ID_CONNECTION_ATTEMPT_FAILED:
		case ID_NO_FREE_INCOMING_CONNECTIONS:
		case ID_INVALID_PASSWORD:
			{
			NetMessage mess( NS_SYSTEM_CLIENT_MESSAGE_CONNECTION_FAILED );
			mess.data = new NetSystemMessage("CONNECTION_ATTEMPT_FAILED");
			PRINTDEBUG( "obtained: ", &mess );
			result.push_back( mess );
			}
			break;
		case ID_CONNECTION_LOST:
		case ID_DISCONNECTION_NOTIFICATION:
			{
			NetMessage mess( NS_SYSTEM_CLIENT_MESSAGE_DISCONNECTED );
			mess.data = new NetSystemMessage("CONNECTION_LOST");
			PRINTDEBUG( "obtained: ", &mess );
			result.push_back( mess );
			}
			break;
		default:
			if ( type >= ID_USER_PACKET_ENUM ) {
				BitStream stream(packet->data, packet->length, false);
				NetMessage mess( type );
				mess.data = prototypesContainer->create( type );
				mess.data->deserialize( &stream );
				PRINTDEBUG( "obtained: ", &mess );
				result.push_back( mess );
			}
		}
	}
	messageDispatcher->dispatch( result );
}

unsigned char NetSystemManager::getPacketIdentifier(Packet *p)
{
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
		return (unsigned char) p->data[sizeof(unsigned char) + sizeof(unsigned long)];
	else
		return (unsigned char) p->data[0];
}

void NetSystemManager::setDebug( bool debug )
{
	m_debug = debug;
}

}