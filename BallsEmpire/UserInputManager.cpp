#include "UserInputManager.h"
#include "System.h"

UserInputManager::UserInputManager()
{
}

UserInputManager::~UserInputManager()
{
}

void UserInputManager::setSysCommandListener( IUserInputSysCommandListener * _sysCommandlistener )
{
	sysCommandlistener = _sysCommandlistener;
}

void UserInputManager::setNavigationListener( IUserInputNavigationListener * _navigationListener )
{
	navigationListener = _navigationListener;
}

void UserInputManager::removeSysCommandListener()
{
	sysCommandlistener = 0;
}

void UserInputManager::removeNavigationListener()
{
	navigationListener = 0;
}

void UserInputManager::iterate()
{
	if ( sysCommandlistener ) {
		if (SYSTEMCORE->Input_GetKeyState(HGEK_ESCAPE)) sysCommandlistener->notifyExit();
	}
		
	if ( navigationListener ) {
		int byX = 0;
		int byY = 0;
		if (SYSTEMCORE->Input_GetKeyState(HGEK_LEFT)) byX++;
		if (SYSTEMCORE->Input_GetKeyState(HGEK_RIGHT)) byX--;
		if (SYSTEMCORE->Input_GetKeyState(HGEK_UP)) byY++;
		if (SYSTEMCORE->Input_GetKeyState(HGEK_DOWN)) byY--;
		navigationListener->notifyMoveScreen(byX, byY);
	}
}