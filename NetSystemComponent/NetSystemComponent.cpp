// NetSystemComponent.cpp : Defines the entry point for the console application.
//

#include "MessageIdentifiers.h"

#include "RakPeerInterface.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"
#include "GetTime.h"
#include "BitStream.h"
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include "Gets.h"
#include <map>

#include "NetMessage.h"
#include "NetSystemException.h"

#include "NetSystemServerFacade.h"
#include "NetSystemClientFacade.h"

#ifdef WIN32
#include "Kbhit.h"
#else
#include "Kbhit.h"
#endif

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "../Debug/common.lib")
#endif
#ifdef NDEBUG
#pragma comment(lib, "../Release/common.lib")
#endif
#endif

using namespace netsystem;

class TestSerial : public NS_Serializable {
public:
	TestSerial(){}
	TestSerial(NS_MESSAGE_TYPE nType) : type(nType) {}
	TestSerial(NS_MESSAGE_TYPE nType, NS_INT nx, NS_INT ny, NS_INT nz ) : type(nType), x(nx), y(ny), z(nz) {}
	virtual ~TestSerial(){}
	void serialize( NS_SERIALIZE_STREAM * stream ){
		NS_WRITE(stream, type);
		NS_WRITE(stream, x);
		NS_WRITE(stream, y);
		NS_WRITE(stream, z);
	}
	void deserialize( NS_SERIALIZE_STREAM * stream ) {
		NS_READ(stream, type);
		NS_READ(stream, x);
		NS_READ(stream, y);
		NS_READ(stream, z);
	}
	virtual NS_Serializable * clone()
	{
		return new TestSerial();
	}
public:
	NS_MESSAGE_TYPE type;
	NS_INT x;
	NS_INT y;
	NS_INT z;
};

class NSSerializablePrototypesConcreteContainer : public NSSerializablePrototypesContainer
{
private:
	std::map<NS_MESSAGE_TYPE, NS_Serializable*> reg;
public:
	NSSerializablePrototypesConcreteContainer()
	{
		std::pair<NS_MESSAGE_TYPE, NS_Serializable *> p = std::pair<NS_MESSAGE_TYPE, NS_Serializable *>(121,new TestSerial());
		reg.insert( p );
	}
	virtual NS_Serializable * create( NS_MESSAGE_TYPE type )
	{
		return reg.find(type)->second->clone();
	}
};

class NSTestClientCustomMessageProcessor : public NSIClientCustomMessageProcessor
{
public:
	NSTestClientCustomMessageProcessor() : NSIClientCustomMessageProcessor() {};
	virtual void process( NS_Serializable * data )
	{
		TestSerial * t = (TestSerial *) data;
		std::cout << "RES:" << t->type << ", " << t->x << ", " << t->y << ", " << t->z << "\n";
	}
	virtual NS_MESSAGE_TYPE getType() {return 121;};
};

class NSTestClientMessagesDispatcher : public NSAbstractClientMessagesDispatcher
{
public:
	NSTestClientMessagesDispatcher() : NSAbstractClientMessagesDispatcher()
	{
		registerCustomProcessor( new NSTestClientCustomMessageProcessor() );
	}
};


class NSTestServerCustomMessageProcessor : public NSIServerCustomMessageProcessor
{
public:
	NSTestServerCustomMessageProcessor() : NSIServerCustomMessageProcessor() {};
	virtual void process( NetServerMessage & mess )
	{
		TestSerial * t = (TestSerial *) mess.data;
		std::cout << "ON SERVER:" << t->type << ", " << t->x << ", " << t->y << ", " << t->z << "\n";

		NetServerMessage nm(121,mess.guid);
		nm.data = new TestSerial(121, 21, 77, 112);
		NetSystemServerFacade::INSTANCE()->sendReliable( nm );
	}
	virtual NS_MESSAGE_TYPE getType() {return 121;};
};

class NSTestServerMessagesDispatcher : public NSAbstractServerMessagesDispatcher
{
public:
	NSTestServerMessagesDispatcher() : NSAbstractServerMessagesDispatcher()
	{
		registerCustomProcessor( new NSTestServerCustomMessageProcessor() );
	}
};

/*
struct TestStruct1
  : Struct<code,
    Struct<x,
    Struct<y,
    Struct<z
    > > > >
{
};

void TestStruct()
{
  TestStruct1 ts, q;
  ts.set<code>(10);
  ts.set<x>(15.0f);
  ts.set<y>(20.0f);
  ts.set<z>(-100);
  q = ts;
  std::string v;
  bool b = ts.visit<out>(v);
  assert(b == true);
  //bool b1 = q.visit<in>(v);
  //assert(b1 == true);
  assert( v.compare( ":10:15:20:-100\n" ) == 0 );
  assert(ts.get<code>() == q.get<code>());
  assert(ts.get<z>() == q.get<z>());
}

*/
void startClient();
void startServer();

int main(void)
{
	printf("Select: 1 - server, 2 - client, other - exit\n");
	char buff[256];
	bool client = true;
	while (1) {
		if (kbhit()) {
			if ( gets(buff) ) {
				if ( (buff[0]=='1') ) {
					client = false;
					break;
				}
				if ( (buff[0]=='2') ) {
					client = true;
					break;
				}
				printf("exiting\n");
				exit(0);
			}
		}
	}
	
	try {
	if ( client ) {
		startClient();
	} else {
		startServer();
	}
	} catch ( NetSystemException * ex ) {
		printf(ex->getMessage().c_str());
	}
	char ch;
	printf("Enter any key...");
	std::cin >> ch;
	return 0;
}

void startServer(){
	printf("Starting server\n");
	NetSystemServerFacade * f = NetSystemServerFacade::INSTANCE();
	f->setNSSerializablePrototypesContainer( new NSSerializablePrototypesConcreteContainer() );
	f->setNSServerMessagesDispatcher( new NSTestServerMessagesDispatcher() );
	f->startUp(60000, 10, 10);
	while (1) {
		Sleep(10);
		f->obtain();
		/*for(NS_SERVER_MESSAGES_LIST::iterator it = d->begin(); it != d->end(); ++it ){
			if ( it->type < NS_CUSTOM_MESSAGE_START ) {
				continue;
			}
			std::cout << "TYPE: " << it->type << "\n";
			TestSerial * t = (TestSerial *)it->data;
			std::cout << t->type << ", " << t->x << ", " << t->y << ", " << t->z << "\n";
			delete t;

			NetServerMessage nm(121,it->guid);
			nm.data = new TestSerial(121, 21, 77, 112);
			f->sendReliable( nm );
			//std::cout << "Type received: [" << it->type << "], data: [" << it->rawData << "]\n";
			//NetMessageData data = NetMessageData();
			//memcpy( data, it->rawData, it->rawDataSize );
			//data.type = it->rawData[0];
			//std::cout << data.type << "," << data.x << "," << data.y << "," << data.z << "\n";
			//printf("\n");
			//printf( it->rawData );
			//if ( it->rawData ) 
			//delete (it->rawData);
		}
		delete d;*/
	}
}

void startClient(){
	printf("Starting client\n");
	NetSystemClientFacade * f = NetSystemClientFacade::INSTANCE();
	f->setNSSerializablePrototypesContainer( new NSSerializablePrototypesConcreteContainer() );
	f->setNSClientMessagesDispatcher( new NSTestClientMessagesDispatcher() );
	f->connect("127.0.0.1", 60000);
	char buff[256];
	while (1) {
		Sleep(100);
		if (kbhit()) {
			if ( gets(buff) ) {
				/*NetMessageData data = NetMessageData();
				data.type = 121;
				data.x = -18;
				data.y = 105;
				data.z = 27;
				//std::string str("ydata simple");
				char buff[sizeof(data)];
				memcpy( buff, &data, sizeof(data));*/
				NetMessage nm(121);
				nm.data = new TestSerial(121, 21, 77, 112);
				//nm.rawData = buff;
				//nm.rawDataSize = sizeof(data);
				//nm.rawData = (char *)str.c_str();
				//nm.rawDataSize = str.length();
				f->sendReliable( nm );
				delete nm.data;
			}
		}

		f->obtain();

		/*for(NS_MESSAGES_LIST::iterator it = d->begin(); it != d->end(); ++it ){
			if ( it->type < NS_CUSTOM_MESSAGE_START ) {
				continue;
			}

			std::cout << "TYPE: " << it->type << "\n";
			TestSerial * t = (TestSerial *)it->data;
			std::cout << t->type << ", " << t->x << ", " << t->y << ", " << t->z << "\n";
			delete t;
			//if ( it->rawData ) 
			//	delete (it->rawData);
		}*/
	}
}

/*
int main(void)
{
	// Pointers to the interfaces of our server and client.
	// Note we can easily have both in the same program
	RakNet::RakPeerInterface *client=RakNet::RakPeerInterface::GetInstance();
	RakNet::RakPeerInterface *server=RakNet::RakPeerInterface::GetInstance();

	int i = server->GetNumberOfAddresses();

	// Holds packets
	RakNet::Packet* p;

	// Record the first client that connects to us so we can pass it to the ping function
	RakNet::SystemAddress clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
	bool packetFromServer;
	char portstring[30];

	printf("This is a sample of how to send offline pings and get offline ping\n");
	printf("responses.\n");
	printf("Difficulty: Beginner\n\n");

	// A server
	puts("Enter the server port to listen on");
	gets(portstring);
	if (portstring[0]==0)
		strcpy(portstring,"60000");

	// Enumeration data
	puts("Enter offline ping response data (for return by a LAN discovery for example)");
	puts("Hit enter for none.");
	char enumData[512];
	gets(enumData);
	if (enumData[0])
		server->SetOfflinePingResponse(enumData, (const unsigned int) strlen(enumData)+1);

	puts("Starting server.");

	// The server has to be started to respond to pings.
	RakNet::SocketDescriptor socketDescriptor(atoi(portstring),0);
	bool b = server->Startup(2, &socketDescriptor, 1)==RakNet::RAKNET_STARTED;
	server->SetMaximumIncomingConnections(2);
	if (b)
		puts("Server started, waiting for connections.");
	else
	{ 
		puts("Server failed to start.  Terminating.");
		exit(1);
	}

	socketDescriptor.port=0;
	client->Startup(1,&socketDescriptor, 1);

	puts("'q' to quit, any other key to send a ping from the client.");
	char buff[256];

	// Loop for input
	while (1)
	{
		if (kbhit())
		{
			// Holds user data
			char ip[30], serverPort[30], clientPort[30];

			if (gets(buff)&&(buff[0]=='q'))
				break;
			else
			{

				// Get our input
				puts("Enter the client port to listen on, or 0");
				gets(clientPort);
				if (clientPort[0]==0)
					strcpy(clientPort, "0");
				puts("Enter IP to ping");
				Gets(ip, sizeof(ip));
				if (ip[0]==0)
					strcpy(ip, "127.0.0.1");
				puts("Enter the port to ping");
				gets(serverPort);
				if (serverPort[0]==0)
					strcpy(serverPort, "60000");

				client->Ping(ip, atoi(serverPort), false);

				puts("Pinging");
			}
		}

		// Get a packet from either the server or the client
		p = server->Receive();

		if (p==0)
		{
			packetFromServer=false;
			p = client->Receive();
		}
		else
			packetFromServer=true;

		if (p==0)
			continue;


		// Check if this is a network message packet
		switch (p->data[0])
		{
			case ID_UNCONNECTED_PONG:
				unsigned int dataLength;
				RakNet::TimeMS time;
				RakNet::BitStream bsIn(p->data,p->length,false);
				bsIn.IgnoreBytes(1);
				bsIn.Read(time);
				dataLength = p->length - sizeof(unsigned char) - sizeof(RakNet::TimeMS);
				printf("ID_UNCONNECTED_PONG from SystemAddress:%u:%u.\n", p->systemAddress.binaryAddress, p->systemAddress.port);
				printf("Time is %i\n",time);
				printf("Ping is %i\n", (unsigned int)(RakNet::GetTimeMS()-time));
				printf("Data is %i bytes long.\n", dataLength);
				if (dataLength > 0)
					printf("Data is %s\n", p->data+sizeof(unsigned char)+sizeof(RakNet::TimeMS));
				break;
			
			// In this sample since the client is not running a game we can save CPU cycles by
			// Stopping the network threads after receiving the pong.
			client->Shutdown(100);
		}

		// We're done with the packet
		if (packetFromServer)
			server->DeallocatePacket(p);
		else
			client->DeallocatePacket(p);
	}

	// We're done with the network
	RakNet::RakPeerInterface::DestroyInstance(server);
	RakNet::RakPeerInterface::DestroyInstance(client);

	return 0;
}
*/






/*

#pragma pack(push, 1)
struct NetMessageData {
	NS_MESSAGE_TYPE type;
	int x;
	int y;
	int z;
};
#pragma pack(pop)

//	unsigned char chInputBuffer[ sizeof(message.data) ];
//	memcpy( chInputBuffer , &(message.data), sizeof(message.data) );

#pragma warning(push)
#pragma warning(disable:4996)

//! \internal base declaration
template <typename T> struct StructInfo;

//! USHORT_BITS(name,bits) declares a structure field that will 
//! store unsigned integer values up to 'bits' bits in size, as 
//! an unsigned short within the struct. You reference the given 
//! 'name' in your structure declaration (Struct<name, ...>).
//! \param name The name to give the field; must be a valid C 
//! identifier name.
//! \param bits The number of bits to use for storage (only used 
//! by some marshalling visitors).
#define USHORT_BITS(name,bits) struct name; template<> struct StructInfo<name> { typedef name Name; typedef unsigned short Type; static inline int getBits() { return bits; } static inline Type init() { return 0; }  }


//! FLOAT_RES_LIMIT(name,res,limit) declares a structure field that will 
//! store float values with a given resolution ('res') extending out to 
//! a positive and negative limit from the origin ('limit').
//!  You reference the given 
//! 'name' in your structure declaration (Struct<name, ...>).
//! \param name The name to give the field; must be a valid C 
//! identifier name.
//! \param res The minimum step size to represent.
//! \param limit The maximum magnitude to represent.
//! \note Res and limit may be used by some marshalling visitors to 
//! encode the float as a fixed-resolution number.
#define FLOAT_RES_LIMIT(name,rez,limit) struct name; template<> struct StructInfo<name> { typedef name Name; typedef float Type; static inline float getRez() { return rez; } static inline float getLimit() { return limit; } static inline Type init() { return 0; } }


#pragma warning(push)
#pragma warning(disable:4584) // already a base

// Declare helpers in the system
//! Operations for inputting into a struct
struct in;
//! Operations for outputting from a struct
struct out;
//! \internal An actual struct member (used to disambiguate access)
template<typename N> struct StructMember {
  typename StructInfo<N>::Type _memb;
  StructMember() { _memb = StructInfo<N>::init(); }
};
//! You implement a partial specialization on StructOp::visit() 
//! to perform visitation (such as serializing or validating data).
template<typename operation, typename type, typename container> struct StructOp {
};
//! You implement a partial specialization on StructInitialize::initialize() 
//! to start out visitation.
template<typename operation, typename type, typename container> struct StructInitialize {
};
//! You implement a partial specialization on StructTerminate::terminate() 
//! to finalize visitation.
template<typename operation, typename type, typename container> struct StructTerminate {
};
//! \internal Base is used to terminate the declaration of a user compound type.
struct Base {
  template<typename operation, typename topmost, typename data> bool visit_internal(data & o) {
    return StructTerminate<operation, topmost, data>().terminate(o);
  }
};

//! You use template struct to construct structures out of data types 
//! that you have defined with USHORT_BITS, FLOAT_RES_LIMIT and other 
//! such macros that define "struct member" names/types.
//! The first parameter is a name/type; the second is another Struct 
//! (for what comes after the first member), or empty (default) to 
//! finish the struct.
template<typename N, typename B = Base>
struct Struct : StructMember<N>, B {

  //! Call get<name>() to read the value of the member 'name'.
  template<typename T> typename StructInfo<T>::Type const & get() const {
    return StructMember<T>::_memb;
  }

  //! Call set<name>() to set the value of the member 'name'.
  template<typename T> void set(typename StructInfo<T>::Type const & t) {
    StructMember<T>::_memb = t;
  }

  //! Call visit() to visit all the members of the struct in order, 
  //! based on your StructInitialize, StructOp and StructTerminate 
  //! visitor class implementations.
  template<typename operation, typename data> bool visit(data & o) {
    return StructInitialize<operation, Struct, data>().initialize(o, *this)
        && visit_internal<operation, Struct, data>(o);
  }

protected:
  //! \internal get the visitation in the right order
  template<typename operation, typename topmost, typename data> bool visit_internal(data & o) {
    return StructOp<operation, topmost, data>().visit(o, StructMember<N>::_memb)
        && B::visit_internal<operation, topmost, data>(o) ;
  }
};


#pragma warning(pop)

//! \internal marshal to strings (do not use resolution information)
template<typename T>
struct StructInitialize<out, T, std::string> {
  bool initialize(std::string & out, T const & t) {
    return true;
  }
};
//! \internal marshal to strings (do not use resolution information)
template<typename T>
struct StructTerminate<out, T, std::string> {
  bool terminate(std::string & out) {
    out += "\n";
    return true;
  }
};
//! \internal marshal to strings (do not use resolution information)
template<typename T>
struct StructOp<out, T, std::string> {
  //! \internal Put floats into the string
  bool visit(std::string & out, float f) {
    char buf[30];
    sprintf(buf, ":%g", f);
    out += buf;
    return true;
  }
  //! \internal Put ushorts into the string
  bool visit(std::string & out, unsigned short us) {
    char buf[30];
    sprintf(buf, ":%d", us);
    out += buf;
    return true;
  }
};

#pragma warning(pop)


USHORT_BITS(code, 10);
FLOAT_RES_LIMIT(x, 0.001f, 5000);
FLOAT_RES_LIMIT(y, 0.001f, 5000);
FLOAT_RES_LIMIT(z, 0.001f, 5000);

*/