#pragma once

#include <hash_map>
#include "SimpleClientTypeDefs.h"
#include "GameObjectSoundView.h"
#include "SoundSystemFacade.h"
#include "SimpleSoundMessage.h"

namespace simpleclient {

class GameObjectSoundViewsRegister
{
public:
	GameObjectSoundViewsRegister( soundsystem::SoundSystemFacade *, SimpleSoundResolvedResourcesContainer * );
	~GameObjectSoundViewsRegister(void);

	void addObject( OBJECT_IDENTITY );
	void removeObject( OBJECT_IDENTITY );
	void setCurrentPos( vector3df & );

	void iterate();
	void processSoundData( SoundInformation & );
private:
	std::hash_map<OBJECT_IDENTITY, GameObjectSoundView *> soundObjects;
	soundsystem::SoundSystemFacade * sysSound;
	SimpleSoundResolvedResourcesContainer * resourcesContainer;
	vector3df currentUserPos;
};

}