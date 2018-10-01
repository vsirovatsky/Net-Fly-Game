// SoundSystemComponent.cpp : Defines the entry point for the console application.
//
#if defined(WIN32)
#include <windows.h>
#include <conio.h>
#else
#include "../common/conio.h"
#endif




#include "stdafx.h"
#include "SoundSystemFacade.h"
#include "SoundSystemTypeDefs.h"
#include "SoundSystemException.h"
#include <stdio.h>
#include <irrKlang.h>

using namespace soundsystem;

int _tmain(int argc, _TCHAR* argv[])
{
	SoundSystemFacade * s = SoundSystemFacade::INSTANCE();
	s->init();
	/*SoundData sd = SoundData("1", "wolftribes.ogg");
	sd.track = true;
	sd.volume = 1.0f;
	s->play2D( sd );*/

	soundsystem::SoundData3D sd = soundsystem::SoundData3D();
	sd.id = "1";
	sd.address = "apheremove1.wav";
	sd.looped = true;
	sd.maxDis = 2000;
	sd.minDis = 0;
	sd.volume = 0.5f;
	sd.track = true;
	sd.x = 0;
	sd.y = 0;
	sd.z = 0;
	s->play3D( sd );
	
	while(true){
		Sleep(100);
		try {
		// Handle user input: Every time the user presses a key in the console,
		// play a random sound or exit the application if he pressed ESCAPE.

		if (kbhit())
		{
			int key = getch();

			if (key == 27)
				break; // user pressed ESCAPE key
			else
			{
				
			}
		}
		}catch(SoundSystemException * ex){
			std::cout << ex->getMessage() << "\n";
		}catch(...){
			std::cout << "unknown\n";
		}
	}
	s->stopAllSound();
	delete s;
	return 0;
}

