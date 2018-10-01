// SimpleServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleNetManager.h"
#include "FileSystemFacade.h"
#include "LogicFacade.h"


#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "../Debug/common.lib")
#pragma comment(lib, "../Debug/FileSystemComponent.lib")
#pragma comment(lib, "../Debug/NetSystemComponent.lib")
#endif
#ifdef NDEBUG
#pragma comment(lib, "../Release/common.lib")
#pragma comment(lib, "../Release/FileSystemComponent.lib")
#pragma comment(lib, "../Release/NetSystemComponent.lib")
#endif
#endif

#define SERVERSETTINGS "serversettings.txt"

using namespace simpleserver;

int _tmain(int argc, _TCHAR* argv[])
{
	netsystem::NetSystemServerFacade * nf = netsystem::NetSystemServerFacade::INSTANCE();
	filesystem::FileSystemFacade * ff = filesystem::FileSystemFacade::INSTANCE();

	ff->addToRegisterFile( SERVERSETTINGS );
	int mainSleapType = ff->getIntInFile( SERVERSETTINGS, "mainthreadsleeptime" );

	int netSleapType = ff->getIntInFile( SERVERSETTINGS, "networkthreadsleeptime" );
	int serverPort = ff->getIntInFile( SERVERSETTINGS, "serverport" );
	int numberOfAllowedConnections = ff->getIntInFile( SERVERSETTINGS, "numberOfAllowedConnections" );
	int numberOfConnections = ff->getIntInFile( SERVERSETTINGS, "numberOfConnections" );

	std::cout << mainSleapType << std::endl;
	std::cout << netSleapType << std::endl;

	SimpleNetManagerContext * netContext = new SimpleNetManagerContext();
	netContext->netSleapType = netSleapType;
	netContext->port = serverPort;
	netContext->numberOfAllowedConnections = numberOfAllowedConnections;
	netContext->numberOfConnections = numberOfConnections;

	SimpleNetManager * man = new SimpleNetManager( netContext );
	man->activate();

	//Main thread
	while ( true ) {
		Sleep( mainSleapType );
		man->iterate();
		LogicFacade::INSTANCE()->iterate();
		LogicFacade::INSTANCE()->sendUpdates(man, man->getUserManagementProvider());
	}

	std::cin.get();
	man->terminate();
	delete man;

	return 0;
}

