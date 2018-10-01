// PostComponent.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "CommunicationsFacade.h"

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "../Debug/common.lib")
#endif
#ifdef NDEBUG
#pragma comment(lib, "../Release/common.lib")
#endif
#endif

using namespace communications;

class TestPostMessageProcessor : public IPostMessageProcessor
{
	virtual void process( Envelope * en )
	{
		std::cout << "message: " << en->message->getType() << " : " << ((TextMessage *) en->message)->getMessage().c_str();
	}
	virtual PC_MESSAGE_TYPE getType()
	{
		return MESSAGE_TYPE_TEXT;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	PRINT( "Hello " );

	AbstractPostOffice * comm = CommunicationsFacade::INSTANCE()->registerPostOffice( COMMUNICATIONS_COMPONENT_ID );
	AbstractPostOffice * master = CommunicationsFacade::INSTANCE()->registerPostOffice( MASTER_COMPONENT_ID );
	master->registerDefaultProcessor( new TestPostMessageProcessor() );

	CommunicationsFacade::INSTANCE()->activate( 10 );
	while (true) {
		std::cin.get();
		TextMessage * mes = new TextMessage("First one");
		comm->send( mes, MASTER_COMPONENT_ID );
		comm->flush();
		Sleep(10);

		PC_ENVELOPES_LIST envelopes = PC_ENVELOPES_LIST();
		master->obtain();
	}
	return 0;
}