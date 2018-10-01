#pragma once

#include "IMain.h"
#include "UserInputManager.h"
#include "GameWorld.h"

class Main : public IMain, public IUserInputSysCommandListener {
public:
	Main( hgeCallback, hgeCallback );
	~Main();
	bool FrameFunc();
	bool RenderFunc();
	void run();

	//from IMain
	virtual LivingObjectsRegister * getLivingObjectsRegister(){return livingObjectsRegister;}
	virtual NonLivingObjectsRegister * getNonLivingObjectsRegister(){return nonlivingObjectsRegister;}
	virtual SoundManager * getSoundManager(){return soundManager;}

	//from IUserInputSysCommandListener
	virtual void notifyExit();
private:
	LivingObjectsRegister * livingObjectsRegister;
	NonLivingObjectsRegister * nonlivingObjectsRegister;
	SoundManager * soundManager;
	UserInputManager * inputManager;
	GameWorld * gameWorld;
	bool exitRequest;
};