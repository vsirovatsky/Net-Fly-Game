#pragma once

#include "ThreadWrapper.h"
#include "ISimpleSoundManagerPanel.h"

namespace simpleclient {

class SimpleSoundManager : public common::thread, public ISimpleSoundManagerPanel
{
public:
	SimpleSoundManager( SimpleSoundManagerContext * );
	virtual ~SimpleSoundManager(void);

	virtual void run();
	void activate();

	// from ISimpleSoundManagerPanel
	virtual SimpleSoundManagerContext * getContext(){return context;}
	virtual ISimpleSoundState * getState(){return soundState;}
	virtual soundsystem::SoundSystemFacade * getSysSound(){return sysSound;}
	virtual communications::AbstractPostOffice * getPostOffice(){return postOffice;}
	virtual SimpleSoundResolvedResourcesContainer * getResolvedResourcesContainer(){return resolvedResourcesContainer;}
	virtual GameObjectSoundViewsRegister * getGameObjectSoundViewsRegister(){return soundObjectsRegister;}
private:
	SimpleSoundManagerContext * context;
	soundsystem::SoundSystemFacade * sysSound;
	communications::AbstractPostOffice * postOffice;
	SimpleSoundResolvedResourcesContainer * resolvedResourcesContainer;
	GameObjectSoundViewsRegister * soundObjectsRegister;

	void runImpl();

	ISimpleSoundState * soundState;
};

}