#include "Main.h"

#ifdef  NDEBUG
	#pragma comment(lib, "../Release/common.lib")
#endif
#ifdef  _DEBUG
	#pragma comment(lib, "../Debug/common.lib")
#endif

Main * mainClass;


bool FrameFunc()
{
	return mainClass->FrameFunc();
}


bool RenderFunc()
{
	return mainClass->RenderFunc();
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	mainClass = new Main( FrameFunc, RenderFunc );
	mainClass->run();
	delete mainClass;
	return 0;
}