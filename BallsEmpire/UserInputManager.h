#pragma once

class IUserInputSysCommandListener {
public:
	virtual void notifyExit() = 0;
};

class IUserInputNavigationListener {
public:
	virtual void notifyMoveScreen( int byX, int byY ) = 0;
};

class UserInputManager {
public:
	UserInputManager();
	~UserInputManager();
	void iterate();

	void setSysCommandListener( IUserInputSysCommandListener * );
	void setNavigationListener( IUserInputNavigationListener * );
	void removeSysCommandListener();
	void removeNavigationListener();
private:
	IUserInputSysCommandListener * sysCommandlistener;
	IUserInputNavigationListener * navigationListener;
};