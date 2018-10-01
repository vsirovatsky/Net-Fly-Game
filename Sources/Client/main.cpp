#include <ClanLib/core.h>
#include <ClanLib/network.h>

#include "client.h"
#include "VideoSystem.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#ifdef WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main(int, char**)
#endif
{
	try
	{
		CL_SetupCore setup_core;
		CL_SetupNetwork setup_network;

		CL_ConsoleWindow console("Console", 160, 1000);
		CL_ConsoleLogger logger;

		Client * client = new Client();
		CL_Thread thread;
		thread.start(client, &Client::listenLoop);
        thread.set_thread_name("Listen Loop");
		CL_Thread thread1;
		thread1.start(client, &Client::speakLoop);
        thread1.set_thread_name("Speak Loop");
		//thread.join(); - blocks current thread until client finished
		VideoSystem * vs = new VideoSystem();
		if ( !vs->isValid() ) {
			return 1;
		}
		client->setUser( vs->getUser() );
		client->setVideoSystem( vs );
		client->connect_to_server();
		vs->run();
		client->disconnect_of_server();
		delete client;
		delete (vs);
		return 0;
	}
	catch (CL_Exception e)
	{
#ifdef WIN32
		MessageBox(0, e.get_message_and_stack_trace().c_str(), TEXT("Unhandled Exception"), MB_OK);	
#else
		CL_Console::write_line("Unhandled exception: %1", e.get_message_and_stack_trace());
#endif

		return 1;
	}
}
