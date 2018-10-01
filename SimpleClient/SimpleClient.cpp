// SimpleClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleMainComponent.h"
#include "SimpleVideoManager.h"
#include "Logger.h"

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "../Debug/common.lib")
#pragma comment(lib, "../Debug/PostComponent.lib")
#pragma comment(lib, "../Debug/FileSystemComponent.lib")
#pragma comment(lib, "../Debug/NetSystemComponent.lib")
#pragma comment(lib, "../Debug/VideoSystemComponent.lib")
#pragma comment(lib, "../Debug/SoundSystemComponent.lib")
#endif
#ifdef NDEBUG
#pragma comment(lib, "../Release/common.lib")
#pragma comment(lib, "../Release/PostComponent.lib")
#pragma comment(lib, "../Release/FileSystemComponent.lib")
#pragma comment(lib, "../Release/NetSystemComponent.lib")
#pragma comment(lib, "../Release/VideoSystemComponent.lib")
#pragma comment(lib, "../Release/SoundSystemComponent.lib")
#endif
#endif

using namespace simpleclient;

int _tmain(int argc, _TCHAR* argv[])
{
	PRINT("Client Started");
	SimpleMainComponent smc = SimpleMainComponent();
	smc.activate();

	SimpleVideoManager * videoMan = new SimpleVideoManager( smc.context->mSimpleVideoManagerContext );
	std::cout << "starting video..." << std::endl;
	videoMan->run();
	
/*	while ( true ) {
		Sleep( 1000 );
		std::cin.get();

		// TODO:
		//InnerPingMessage * ipm = new InnerPingMessage();
		//postOffice->send( ipm, communications::NET_COMPONENT_ID);
	}*/

	return 0;
}

